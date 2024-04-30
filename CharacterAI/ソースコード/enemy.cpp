#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"

#include "distance.h"

void Enemy::Init()
{
	m_Scale= D3DXVECTOR3(0.5f, 0.5f, 0.5f);	

	m_discoveryArea = 4.0f;
	m_undiscoveryArea = 5.0f;
	m_searchCircle = 2.0f;
	m_undiscovery = true;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.04f);
	m_Model = new Model();
	m_Model->Load("model\\robot.obj");


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");
}

void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	if (!m_Virgin)
	{
		m_StartPosition = m_Position;
		m_Virgin = true;
	}

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Distance* distance = scene->GetGameObject<Distance>();

	// プレイヤーを追う動き
	{
		// 移動
		m_Position -= m_move;

		// 未発見時の動き
		if (!m_discovery)
		{/*
			// 元の位置に戻る
			if (!m_undiscovery)
			{
				float A = m_undiscoveryPosition.x - m_Position.x;
				float B = m_undiscoveryPosition.z - m_Position.z;

				float C = sqrt(A * A + B * B);

				float dx = A / C;
				float dz = B / C;

				m_move.x = dx * -0.05f;
				m_move.z = dz * -0.05f;

				if (player->GetPosition().z < m_Position.z + m_Scale.z + 1.5f)
				{
					if (player->GetPosition().z > m_Position.z - m_Scale.z - 1.5f)
					{
						if (player->GetPosition().x < m_Position.x + m_Scale.x + 1.5f)
						{
							if (player->GetPosition().x > m_Position.x - m_Scale.x - 1.5f)
							{
								m_Position.x = m_undiscoveryPosition.x;
								m_Position.z = m_undiscoveryPosition.z;
								m_move = D3DXVECTOR3(0.0f, 0.0f, 0.04f);
								m_undiscovery = true;
							}
						}
					}
				}
			}
			else*/
			{
				// 巡回の向き切り替え
				if (m_StartPosition.z - 14.0f > m_Position.z)
				{
					m_move *= -1.0f;
				}
				else if (m_StartPosition.z + 4.0f < m_Position.z)
				{
					m_move *= -1.0f;
				}
			}
		}
		// 発見時の動き
		else
		{
			// 目線追跡
			D3DXVECTOR3 diff, playerPos = player->GetPosition();
			diff.x = m_Position.x - playerPos.x;
			diff.y = m_Position.y - playerPos.y;
			diff.z = m_Position.z - playerPos.z;

			m_Rotation.y = atan2(diff.x, diff.z) + D3DX_PI;

			// m_Position += GetForward() * 0.025f;


			if (m_discoveryCount == 0)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				if (!m_undiscovery)
				{
					m_undiscoveryPosition = m_Position;
				}
			}

			// 発見硬直カウント
			m_discoveryCount++;

			if (m_discoveryCount > 2 * 60)
			{
				// m_discovery = false;
				// m_discoveryCount = 0;
				m_undiscovery = false;

				float A = player->GetPosition().x - m_Position.x;
				float B = player->GetPosition().z - m_Position.z;

				float C = sqrt(A * A + B * B);

				float dx = A / C;
				float dz = B / C;

				m_move.x = dx * -0.05f;
				m_move.z = dz * -0.05f;

				if (player->GetPosition().z < m_Position.z + m_Scale.z + m_undiscoveryArea)
				{
					if (player->GetPosition().z > m_Position.z - m_Scale.z - m_undiscoveryArea)
					{
						if (player->GetPosition().x < m_Position.x + m_Scale.x + m_undiscoveryArea)
						{
							if (player->GetPosition().x > m_Position.x - m_Scale.x - m_undiscoveryArea)
							{
								//m_discoveryCount = 0;
								//m_discovery = false;
							}
						}
					}
				}
			}
		}
	}

	if (!m_discovery)
	{
		if (player->GetPosition().z < m_Position.z + m_Scale.z + m_discoveryArea)
		{
			if (player->GetPosition().z > m_Position.z - m_Scale.z - m_discoveryArea)
			{
				if (player->GetPosition().x < m_Position.x + m_Scale.x + m_discoveryArea)
				{
					if (player->GetPosition().x > m_Position.x - m_Scale.x - m_discoveryArea)
					{
						m_discovery = true;
					}
				}
			}
		}
	}
}

void Enemy::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
