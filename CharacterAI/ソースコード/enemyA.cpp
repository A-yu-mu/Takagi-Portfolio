#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "enemyA.h"
#include "enemyB.h"

#include "enemyAState.h"


#define BUFSIZE (1024)	// 1�s�ɍő�1024 


void EnemyA::Init()
{
	// �t�@�C���ǂݍ���
	FILE* fp;	// FILE�^�\����
	char buffer[1024];
	char line[BUFSIZE];
	// �ǂݍ��݃t�@�C�����J��
	fp = fopen("enemyA.txt", "r");

	// �ǂݍ��ݎ��s������
	if (fp == NULL)
	{
		// �Q�[���I�����邩�^�C�g���ɖ߂�
		int a = 0;
	}

	for (int i = 0; i <= 17; i++)
	{
		if (fgets(buffer, sizeof(buffer), fp) == NULL)
		{
			int a = 0;
		}
		switch (i)
		{
		case 1:
			// �q�b�g�|�C���g
			sscanf(buffer, "%*[^:]:%f", &m_HP);
			m_MaxHP = m_HP;
			break;

		case 2:
			// �}�W�b�N�|�C���g
			sscanf(buffer, "%*[^:]:%f", &m_MP);
			m_MaxMP = m_MP;
			break;

		case 3:
			// �����񕜗�
			sscanf(buffer, "%*[^:]:%f", &m_AutoRecoveryAmount);
			break;

		case 4:
			// �񕜗�
			sscanf(buffer, "%*[^:]:%f", &m_RecoveryPoint);
			break;

		case 5:
			// �ߐڍU���\�͈�
			sscanf(buffer, "%*[^:]:%f", &m_MeleeRange);
			break;

		case 6:
			// �������U���\�͈�
			sscanf(buffer, "%*[^:]:%f", &m_LongAttackRange);
			break;

		case 7:
			// �U�����[�g
			sscanf(buffer, "%*[^:]:%f", &m_AttackRate);
			break;

		case 8:
			// �U����
			sscanf(buffer, "%*[^:]:%f", &m_AttackPoint);
			break;

		case 9:
			// ���G�͈�(�x�����)
			sscanf(buffer, "%*[^:]:%f", &m_DiscoveryAreaA);
			break;

		case 10:
			// ���G�͈�(������)
			sscanf(buffer, "%*[^:]:%f", &m_DiscoveryAreaB);
			break;

		case 11:
			// ����������
			sscanf(buffer, "%*[^:]:%f", &m_UnDiscoveryArea);
			break;

		case 12:
			// �v�l�d������
			sscanf(buffer, "%*[^:]:%d", &m_ThinkingTime);
			m_ThinkingTimeCount = m_ThinkingTime;
			break;

		case 13:
			// ���s���x
			sscanf(buffer, "%*[^:]:%f", &m_WalkSp);
			m_WalkSp /= 1000;
			break;

		case 14:
			// ���s���x
			sscanf(buffer, "%*[^:]:%f", &m_RunSp);
			m_RunSp /= 1000;
			break;

		case 16:
			// �q�b�g�|�C���g�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomHP);
			m_HP = m_MaxHP += (m_RandomHP * (rand() / (float)RAND_MAX));	// �Œ�l�{0�`num �̊Ԃ̃����_���Ȓl
			break;

		case 17:
			// �}�W�b�N�|�C���g�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomMP);
			m_MP = m_MaxMP += (m_RandomMP * (rand() / (float)RAND_MAX));	// �Œ�l�{0�`num �̊Ԃ̃����_���Ȓl
			break;

		case 18:
			// �}�W�b�N�|�C���g�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomAttackPoint);
			m_AttackPoint += (m_RandomAttackPoint * (rand() / (float)RAND_MAX));	// �Œ�l�{0�`num �̊Ԃ̃����_���Ȓl
			break;

		case 19:
			// �U�����[�g�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomAttackRate);
			m_AttackRate += (m_RandomAttackRate * (rand() / (float)RAND_MAX))/* * 60*/;	// �Œ�l�{0�`num �̊Ԃ̃����_���Ȓl
			m_AttackRate *= 60;	// �t���[�����ɍ��킹��
			break;

		case 20:
			// �v�l�d�����Ԃ̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%d", &m_RandomThinkingTime);
			m_ThinkingTimeCount = m_ThinkingTime += (rand() % m_RandomThinkingTime);	// �Œ�l�{0�`num �̊Ԃ̃����_���Ȓl
			break;

		case 21:
			// ���s���x�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomWalkSp);
			m_WalkSp += ((m_RandomWalkSp / 1000) * (rand() / (float)RAND_MAX));
			break;

		case 22:
			// ���s���x�̒ǉ������_���l
			sscanf(buffer, "%*[^:]:%f", &m_RandomRunSp);
			m_RunSp += ((m_RandomRunSp / 1000) * (rand() / (float)RAND_MAX));
			break;

		default:
			break;
		}
	}


	m_Scale = D3DXVECTOR3(0.02f, 0.02f, 0.02f);

	m_SearchCircle = 2.0f;		// ����g���ĂȂ�

	m_Alive = true;

	m_HandednessR = true;
	if (rand() % 2 == 0)
	{
		m_HandednessR = false;
	}

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EndMovement = false;

	m_Model = new AnimationModel();
	m_Model->Load("model\\Mutant.fbx");
	m_Model->LoadAnimation("model\\Mutant_Attack.fbx", "Attack");
	m_Model->LoadAnimation("model\\Mutant_LongAttack.fbx", "LongAttack");
	m_Model->LoadAnimation("model\\Mutant_Recovery.fbx", "Recovery");
	m_Model->LoadAnimation("model\\Mutant_Walk.fbx", "Walk");
	m_Model->LoadAnimation("model\\Mutant_Run.fbx", "Run");
	m_Model->LoadAnimation("model\\Mutant_Survey.fbx", "Survey");
	m_Model->LoadAnimation("model\\Mutant_Threat.fbx", "Threat");
	m_Model->LoadAnimation("model\\Mutant_Lose.fbx", "Lose");
	m_Model->LoadAnimation("model\\Mutant_Idle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");
}

void EnemyA::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void EnemyA::Update()
{
	if (!m_Virgin)
	{
		m_Virgin = true;
	}
	Scene* scene = Manager::GetScene();
	EnemyAState* enemyAState = scene->GetGameObject<EnemyAState>();

	// �X�e�[�g����A�b�v�f�[�g�I��
	switch (m_EnemyAState)
	{
	case ENEMY_A_STATE_ROUND:
		enemyAState->AddEnemyAState(1);
		UpdateRound();
		break;

	case ENEMY_A_STATE_CAUTION:
		enemyAState->AddEnemyAState(2);
		UpdateCaution();
		break;

	case ENEMY_A_STATE_BATTLE:
		enemyAState->AddEnemyAState(3);
		UpdateBattle();
		break;

	default:
		break;
	}
}

void EnemyA::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Update(m_AnimationName.c_str(), m_time, m_NextAnimationName.c_str(), m_time, m_BlendRate);
	m_time++;

	m_BlendRate += 0.05f;
	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}


	m_Model->Draw();
}

// �X�e�[�g �A�b�v�f�[�g
void EnemyA::UpdateRound()			// ����X�e�[�g
{
	if (m_ThinkingTimeCount < m_ThinkingTime)
	{
		// �v�l�d��
		ThinkingTime();
	}
	else
	{
		if (m_EndMovement)
		{
			Survey(3);	// 3�b���n��
		}
		else
		{
			Round();	// ����
		}
	}
	AutoRecovery();	// ������
}
void EnemyA::UpdateCaution()		// �x���X�e�[�g
{
	if (m_EndMovement)
	{
		Survey(6);	// 6�b���n��
	}
	else
	{
		SetChangeState(ENEMY_A_STATE_ROUND);	// �����Ԃֈڍs
	}
	AutoRecovery();	// ������
}
void EnemyA::UpdateBattle()			// �퓬�X�e�[�g
{
	// �|����Ă����ꍇ
	if (!m_NearestEnemy->GetAlive())
	{
		Survey(2);
	}

	// �ڐ��ǐ�
	{
		D3DXVECTOR3 diff, enemyBPos = m_NearestEnemy->GetPosition();
		diff.x = m_Position.x - enemyBPos.x;
		diff.y = m_Position.y - enemyBPos.y;
		diff.z = m_Position.z - enemyBPos.z;
	}

	if (m_ThinkingTimeCount < m_ThinkingTime)
	{
		// �v�l�d��
		ThinkingTime();
	}
	else
	{
		if (m_AttackAnimationCount == 0)
		{
			if (AttackAllowed() && LongAttackAllowed())
			{
				// �������Ƌߋ����U�����\
				Attack();
			}
			else if (AttackAllowed())
			{
				// �ߋ����U���̂݉\
				Attack();
			}
			else if (LongAttackAllowed())
			{
				// �������̂݉\
				LongAttack();
			}
			else
			{
				// �U���s�̈� �߂Â�
				Approach();
			}
		}
	}
}

void EnemyA::AddDamage(float Damage)
{
	m_HP -= Damage;
	if (m_HP <= 0.0f)
	{
		// �|���ꂽ
		m_Alive = false;
	}
}


void EnemyA::Move(D3DXVECTOR3 ObjectivePoint, bool Run)		// �ړ�
{
	// �ڐ��ǐ�
	{
		D3DXVECTOR3 diff;
		diff.x = m_Position.x - ObjectivePoint.x;
		diff.y = m_Position.y - ObjectivePoint.y;
		diff.z = m_Position.z - ObjectivePoint.z;

		m_Rotation.y = atan2(diff.x, diff.z) + D3DX_PI;
	}

	// �ڕW�ւ̈ړ�
	{
		float MoveSp;
		if (Run)
		{
			MoveSp = m_RunSp;
			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}
		}
		else
		{
			MoveSp = m_WalkSp;
			if (m_NextAnimationName != "Walk")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Walk";
				m_BlendRate = 0.0f;
			}
		}

		float A = ObjectivePoint.x - m_Position.x;
		float B = ObjectivePoint.z - m_Position.z;

		float C = sqrt(A * A + B * B);

		float dx = A / C;
		float dz = B / C;

		m_Move.x = dx * MoveSp/*-0.05f*/;
		m_Move.z = dz * MoveSp/*-0.05f*/;


		D3DXVECTOR3 direction = m_Position - ObjectivePoint;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < m_MeleeRange)
		{
			m_SurveyCount = 0;
			m_EndMovement = true;
		}
		else
		{
			// �ړ�
			m_Position += m_Move;
		}
		// ���F�m�F
		if (m_SurveyCount % 30 == 0)	// 30�b�Ɉ�x�m�F����
		{
			if (m_EnemyAState == ENEMY_A_STATE_BATTLE)
			{
				VisualSearch(m_DiscoveryAreaA);
			}
			else
			{
				// �ړ����̂��� �����͈͂Ō���
				VisualSearch(m_DiscoveryAreaB);
			}
		}
	}
}
void EnemyA::Attack()	// �U��
{
	// �ڐ��ǐ�
	{
		D3DXVECTOR3 diff;
		diff.x = m_Position.x - m_NearestEnemy->GetPosition().x;
		diff.y = m_Position.y - m_NearestEnemy->GetPosition().y;
		diff.z = m_Position.z - m_NearestEnemy->GetPosition().z;

		m_Rotation.y = atan2(diff.x, diff.z) + D3DX_PI;
	}

	m_AttackRateCount++;
	if (m_AttackRateCount > m_AttackRate)
	{
		m_AttackAnimationCount++;
		if (m_AttackAnimationCount > m_AttackRate * 0.5)
		{
			m_AttackRateCount -= m_AttackRate;
			m_AttackAnimationCount = 0;
			m_NearestEnemy->AddDamage(m_AttackPoint);
		}
		else
		{
			if (m_NextAnimationName != "Attack")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Attack";
				m_BlendRate = 0.0f;
			}
		}
	}
	else
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}
}
void EnemyA::LongAttack()	// �������U��
{
	// �ڐ��ǐ�
	{
		D3DXVECTOR3 diff;
		diff.x = m_Position.x - m_NearestEnemy->GetPosition().x;
		diff.y = m_Position.y - m_NearestEnemy->GetPosition().y;
		diff.z = m_Position.z - m_NearestEnemy->GetPosition().z;

		m_Rotation.y = atan2(diff.x, diff.z) + D3DX_PI;
	}

	m_AttackRateCount++;
	if (m_AttackRateCount > m_AttackRate)
	{
		m_AttackAnimationCount++;
		if (m_AttackAnimationCount > m_AttackRate * 0.5)
		{
			m_AttackRateCount -= m_AttackRate;
			m_AttackAnimationCount = 0;
			m_NearestEnemy->AddDamage(m_AttackPoint);
		}
		else
		{
			if (m_NextAnimationName != "LongAttack")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "LongAttack";
				m_BlendRate = 0.0f;
			}
		}
	}
	else
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}
}
void EnemyA::Approach()	// �߂Â�
{

	Move(m_NearestEnemy->GetPosition(), true);
}
void EnemyA::Round()	// ����
{
	if (kakunin != 0)
	{
		Move(m_ObjectivePoint, false);
	}
	else
	{
		m_ObjectivePoint = D3DXVECTOR3(0.0f + (50.0f * (rand() / (float)RAND_MAX)), 0.0f, 0.0f + (50.0f * (rand() / (float)RAND_MAX)));
		kakunin++;
	}
}
void EnemyA::Survey(int VigilantTime/*���n������*/)		// ���n��
{
	// �����Ɍ��n������ or ���F����
	if (m_NextAnimationName != "Survey")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Survey";
		m_BlendRate = 0.0f;
	}

	m_SurveyCount++;

	// ���F�����m�F
	if (m_SurveyCount % 30 == 0)	// 30�b�Ɉ�x�m�F����
	{
		VisualSearch(m_DiscoveryAreaA);
	}

	// ���n���I������
	if (m_SurveyCount >= VigilantTime * 60)
	{
		m_SurveyCount = 0;
		m_EndMovement = false;
		kakunin--;
	}
}
void EnemyA::AutoRecovery()	// ������
{
	// �q�b�g�|�C���g������
	if (m_HP < m_MaxHP)
	{
		m_HP += m_AutoRecoveryAmount;
	}
	else
	{
		m_HP = m_MaxHP;
	}

	// �}�W�b�N�|�C���g������
	if (m_MP < m_MaxMP)
	{
		m_MP += m_AutoRecoveryAmount;
	}
	else
	{
		m_MP = m_MaxMP;
	}
}
void EnemyA::VisualSearch(float DiscoveryArea)	// ���F����
{
	Scene* scene = Manager::GetScene();
	std::vector<EnemyB*> enemyBs = scene->GetGameObjects<EnemyB>();

	float minDistance = std::numeric_limits<float>::max();
	D3DXVECTOR3 nearestEnemyBPosition;
	EnemyB* nearesEnemy = nullptr;

	for (EnemyB* enemyB : enemyBs)
	{
		// �������菈��
		if (m_EnemyAState == ENEMY_A_STATE_ROUND)
		{
			D3DXVECTOR3 direction = m_Position - enemyB->GetPosition();
			direction.y = 0.0f;
			float length = D3DXVec3Length(&direction);

			m_NearestEnemy = GetNearestEnemy();

			if (length < DiscoveryArea)
			{
				m_SurveyCount = 0;
				m_EndMovement = false;
				SetChangeState(ENEMY_A_STATE_BATTLE);	// �퓬��Ԃֈڍs
			}
		}
		else
		{
			D3DXVECTOR3 direction = m_Position - enemyB->GetPosition();
			direction.y = 0.0f;
			float length = D3DXVec3Length(&direction);

			m_NearestEnemy = GetNearestEnemy();

			if (length < m_UnDiscoveryArea)
			{
				if (m_EnemyAState == ENEMY_A_STATE_CAUTION)
				{
					m_SurveyCount = 0;
					m_EndMovement = false;
					SetChangeState(ENEMY_A_STATE_BATTLE);	// �퓬��Ԃֈڍs
				}
			}
			else
			{
				if (m_EnemyAState == ENEMY_A_STATE_BATTLE)
				{
					m_EndMovement = true;
					m_SurveyCount = 0;
					SetChangeState(ENEMY_A_STATE_CAUTION);	// �x����Ԃֈڍs
				}
			}
		}
	}
	/*
	// �GA �̎��E������
	for (EnemyA* enemy : enemys)
	{

	}*/
}
void EnemyA::ThinkingTime()	// �v�l�d������
{
	Scene* scene = Manager::GetScene();
	EnemyB* enemyB = scene->GetGameObject<EnemyB>();

	m_ThinkingTimeCount++;
	if (m_ThinkingTimeCount > m_ThinkingTime / 2)
	{
		if (m_EnemyAState == ENEMY_A_STATE_ROUND)	// �����Ԃֈڍs��
		{
			if (m_KillCount == 0)
			{
				if (enemyB->GetAlive())
				{
					// �������ē{��
					if (m_NextAnimationName != "Lose")
					{
						m_AnimationName = m_NextAnimationName;
						m_NextAnimationName = "Lose";
						m_BlendRate = 0.0f;
					}
				}
			}
		}
		/*else if (m_EnemyAState == ENEMY_A_STATE_CAUTION)	// �x����Ԃֈڍs��
		{
		}*/
		else if (m_EnemyAState == ENEMY_A_STATE_BATTLE)		// �퓬��Ԃֈڍs��
		{
			// ������ �Њd
			if (m_NextAnimationName != "Threat")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Threat";
				m_BlendRate = 0.0f;
			}
		}
		else {}
	}
	else
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}


}
bool EnemyA::AttackAllowed()	// �ߐڍU���s�� ��
{
	// �ΏۂƂ̋������߂��ꍇ�utrue�v��Ԃ�

	D3DXVECTOR3 direction = m_Position - m_NearestEnemy->GetPosition();
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	if (length < m_MeleeRange)
	{
		return true;
	}
	return false;
}
bool EnemyA::LongAttackAllowed()	// �������U���s�� ��
{
	// �ΏۂƂ̋������߂��ꍇ�utrue�v��Ԃ�

	D3DXVECTOR3 direction = m_Position - m_NearestEnemy->GetPosition();
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	if (length < m_LongAttackRange && m_MP <= 50)
	{
		return true;
	}
	return false;
}

bool EnemyA::GetAlive()
{
	Scene* scene = Manager::GetScene();
	EnemyB* enemyB = scene->GetGameObject<EnemyB>();

	if (!m_Alive)
	{
		enemyB->SetKillCount();
		SetDestroy();
	}
	return m_Alive;
}

EnemyB* EnemyA::GetNearestEnemy()
{
	Scene* scene = Manager::GetScene();
	std::vector<EnemyB*> enemyBs = scene->GetGameObjects<EnemyB>();

	float minDistance = std::numeric_limits<float>::max();
	EnemyB* nearestAliveEnemy = nullptr;

	for (EnemyB* enemyB : enemyBs)
	{
		if (enemyB->GetAlive())
		{
			D3DXVECTOR3 direction = m_Position - enemyB->GetPosition();
			direction.y = 0.0f;
			float length = D3DXVec3Length(&direction);

			if (length < minDistance)
			{
				minDistance = length;
				nearestAliveEnemy = enemyB;
			}
		}
	}

	// �ł��߂������Ă���G�̏���Ԃ�
	return nearestAliveEnemy;
}
