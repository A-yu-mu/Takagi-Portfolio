#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "input.h"
#include "cylinder.h"
#include "box.h"
#include "scene.h"
#include "audio.h"
#include "enemyA.h"
#include "enemyB.h"
#include "death.h"
#include "shadow.h"
#include "meshField.h"

const float GRAVITY = 0.05f;  // 重力の値

void Player::Init()
{
	m_IsJumping = false;
	m_JumpForce = 0.5f;
	m_JumpHeight = 3.0f;
	m_GravitySpeed = 0.0f;
	m_GroundHeight = 0.0f;

	// m_Model = new Model();
	// m_Model->Load("model\\torus.obj");

	m_Model = new AnimationModel();
	m_Model->Load("model\\Bot.fbx");
	m_Model->LoadAnimation("model\\Bot_Run.fbx", "Run");
	m_Model->LoadAnimation("model\\Bot_Idle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.0001f, 0.0001f, 0.0001f);
	// m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	m_ShotSE = AddComponent<Audio>();
	m_ShotSE -> Load("audio\\wan.wav");

	m_Shadow = AddComponent<Shadow>();
}

void Player::Uninit()
{
	GameObject::Uninit();
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	GameObject::Update();

	Scene* scene = Manager::GetScene(); 
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();
	EnemyB* enemyB = scene->GetGameObject<EnemyB>();
	Death* death = scene->GetGameObject<Death>();
	m_OldPosition = m_Position;


	/*
	if (Input::GetKeyTrigger(VK_LEFT))
	{
		m_Operate -= 1;
		if (m_Operate < 0)
		{
			m_Operate = 0;
		}
		
	}
	else if (Input::GetKeyTrigger(VK_RIGHT))
	{
		m_Operate += 1;
		if (m_Operate > 2)
		{
			m_Operate = 2;
		}
	}
	*/

	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;

	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;

	default:
		break;
	}


	//重力
	// m_Velocity.y -= 0.015f;

	//移動
	m_Position += m_Velocity;	// オイラー法

	// 地面の高さ取得
	float groundHeight;
	/*
	MeshField* meshField = scene->GetGameObject<MeshField>();
	groundHeight = meshField->GetHeight(m_Position);*/

	groundHeight = 0.0f;
	

	//障害物との衝突判定
	
	//円柱
	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();
		scale.x += 2.0f;

		D3DXVECTOR3 direction = m_Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < scale.x)
		{
			if (m_Position.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y;
			}
			break;
		}
	}

	// 敵
	std::vector<EnemyB*> enemys = scene->GetGameObjects<EnemyB>();

	for (EnemyB* enemy : enemys)
	{
		D3DXVECTOR3 position = enemy->GetPosition();
		D3DXVECTOR3 scale = enemy->GetScale();

		if (m_Position.z < position.z + scale.z + 1.0f)
		{
			if (m_Position.z > position.z - scale.z - 1.0f)
			{
				if (m_Position.x < position.x + scale.x + 1.0f)
				{
					if (m_Position.x > position.x - scale.x - 1.0f)
					{
						death->AddDeath(1);
					}
					else
					{
						death->AddDeath(0);
					}
				}
				else
				{
					death->AddDeath(0);
				}
			}
			else
			{
				death->AddDeath(0);
			}
		}
		else
		{
			death->AddDeath(0);
		}

		break;
	}

	//直方体
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)
	{
		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();

		if (position.x - scale.x - 1.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 1.5f &&
			position.z - scale.z - 1.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 1.5f )
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}
	}

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = true;	// 重力有ならここを　false
	}

	//影の移動
	D3DXVECTOR3 shadowPosition = m_Position;
	shadowPosition.y = groundHeight + 0.01f;
	m_Shadow->SetPosition(shadowPosition);
}

void Player::Draw()
{
	GameObject::Draw();

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);

	// m_Model->Update(m_AnimationName.c_str(), m_time);	// constchar型に変更する

	m_Model->Update(m_AnimationName.c_str(), m_time, m_NextAnimationName.c_str(), m_time, m_BlendRate);
	m_time++;

	m_BlendRate += 0.05f;
	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}

	m_Model->Draw();
}

void Player::UpdateGround()
{
	bool move = false;

	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();
	EnemyB* enemyB = scene->GetGameObject<EnemyB>();

	if (m_Operate == 0)
	{
		// サードパーソン
		if (Input::GetKeyPress('A'))
		{
			m_Position -= GetRight() * 0.1f;
			move = true;
		}
		if (Input::GetKeyPress('D'))
		{
			m_Position += GetRight() * 0.1f;
			move = true;
		}
		if (Input::GetKeyPress('W'))
		{
			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}

			m_Position += GetForward() * 0.1f;
			move = true;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position -= GetForward() * 0.1f;
			move = true;
		}

		if (Input::GetKeyPress('E'))
		{
			m_Rotation.y += 0.1f;
		}
		if (Input::GetKeyPress('Q'))
		{
			m_Rotation.y -= 0.1f;
		}

		if (move == false)
		{
			if (m_NextAnimationName != "Idle")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_BlendRate = 0.0f;
			}
		}
	}
	else if (m_Operate == 1)
	{
		// トップビュー
		if (Input::GetKeyPress('A'))
		{
			m_Position.x -= 0.1f;
		}
		if (Input::GetKeyPress('D'))
		{
			m_Position.x += 0.1f;
		}
		if (Input::GetKeyPress('W'))
		{
			m_Position.z += 0.1f;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position.z -= 0.1f;
		}
		if (Input::GetKeyPress('E'))
		{
			m_Rotation.y += 0.1f;
		}
		if (Input::GetKeyPress('Q'))
		{
			m_Rotation.y -= 0.1f;
		}
	}
	else
	{
		// ファーストパーソン
		if (Input::GetKeyPress('A'))
		{
			m_Position -= GetRight() * 0.1f;
		}
		if (Input::GetKeyPress('D'))
		{
			m_Position += GetRight() * 0.1f;
		}
		if (Input::GetKeyPress('W'))
		{
			m_Position += GetForward() * 0.1f;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position -= GetForward() * 0.1f;
		}
		if (Input::GetKeyPress(VK_SHIFT))
		{
			m_Position.y -= 0.1f;
		}
		if (Input::GetKeyPress(VK_SPACE))
		{
			m_Position.y += 0.1f;
		}

		if (Input::GetKeyPress(VK_RIGHT))
		{
			m_Rotation.y += 0.05f;
		}
		if (Input::GetKeyPress(VK_LEFT))
		{
			m_Rotation.y -= 0.05f;
		}
		if (Input::GetKeyPress(VK_DOWN))
		{
			m_Rotation.x += 0.05f;
			if (m_Rotation.x >= 1.0f)
			{
				m_Rotation.x = 1.0f;
			}
		}
		if (Input::GetKeyPress(VK_UP))
		{
			m_Rotation.x -= 0.05f;
			if (m_Rotation.x <= -1.0f)
			{
				m_Rotation.x = -1.0f;
			}
		}
	}

	/*
	//ジャンプ
	if (Input::GetKeyTrigger('J'))
	{
		m_Velocity.y = 0.35f;
		m_PlayerState = PLAYER_STATE_JUMP;
	}*/
}

void Player::UpdateJump()
{
	if (m_IsGround)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::AddDamage(float Damage)
{
	m_HP -= Damage;
	if (m_HP <= 0.0f)
	{
		// 死んだ
	}
}


