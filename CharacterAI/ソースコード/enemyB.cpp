#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "enemyA.h"
#include "enemyB.h"
#include "scene.h"
#include "explosion.h"

#include "distance.h"


#define BUFSIZE (1024)	// 1行に最大1024


void EnemyB::Init()
{
	// ファイル読み込み
	FILE* fp;	// FILE型構造体
	char buffer[1024];

	// 読み込みファイルを開く
	fp = fopen("enemyB.txt", "r");

	// 読み込み失敗時処理
	if (fp == NULL)
	{
		// ゲーム終了するかタイトルに戻す
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
			// ヒットポイント
			sscanf(buffer, "%*[^:]:%f", &m_HP);
			m_MaxHP = m_HP;
			break;

		case 2:
			// 自動回復量
			sscanf(buffer, "%*[^:]:%f", &m_AutoRecoveryAmount);
			break;

		case 3:
			// 近接攻撃可能範囲
			sscanf(buffer, "%*[^:]:%f", &m_MeleeRange);
			break;

		case 4:
			// 攻撃レート
			sscanf(buffer, "%*[^:]:%f", &m_AttackRate);
			break;

		case 5:
			// 攻撃力
			sscanf(buffer, "%*[^:]:%f", &m_AttackPoint);
			break;

		case 6:
			// 索敵範囲(警戒状態)
			sscanf(buffer, "%*[^:]:%f", &m_DiscoveryAreaA);
			break;

		case 7:
			// 索敵範囲(巡回状態)
			sscanf(buffer, "%*[^:]:%f", &m_DiscoveryAreaB);
			break;

		case 8:
			// 見失う距離
			sscanf(buffer, "%*[^:]:%f", &m_UnDiscoveryArea);
			break;

		case 9:
			// 思考硬直時間
			sscanf(buffer, "%*[^:]:%d", &m_ThinkingTime);
			m_ThinkingTimeCount = m_ThinkingTime;
			break;

		case 10:
			// 歩行速度
			sscanf(buffer, "%*[^:]:%f", &m_WalkSp);
			m_WalkSp /= 1000;
			break;

		case 11:
			// 走行速度
			sscanf(buffer, "%*[^:]:%f", &m_RunSp);
			m_RunSp /= 1000;
			break;

		case 13:
			// ヒットポイントの追加ランダム値
			sscanf(buffer, "%*[^:]:%f", &m_RandomAttackPoint);
			m_HP = m_MaxHP += (m_RandomAttackPoint * (rand() / (float)RAND_MAX));	// 固定値＋0～num の間のランダムな値
			break;

		case 14:
			// 攻撃レートの追加ランダム値
			sscanf(buffer, "%*[^:]:%f", &m_RandomAttackRate);
			m_AttackRate += (m_RandomAttackRate * (rand() / (float)RAND_MAX))/* * 60*/;	// 固定値＋0～num の間のランダムな値
			m_AttackRate *= 60;	// フレーム数に合わせる
			break;

		case 15:
			// 思考硬直時間の追加ランダム値
			sscanf(buffer, "%*[^:]:%d", &m_RandomThinkingTime);
			m_ThinkingTimeCount = m_ThinkingTime += (rand() % m_RandomThinkingTime);	// 固定値＋0～num の間のランダムな値
			break;

		case 16:
			// 歩行速度の追加ランダム値
			sscanf(buffer, "%*[^:]:%f", &m_RandomWalkSp);
			m_WalkSp += ((m_RandomWalkSp / 1000) * (rand() / (float)RAND_MAX));
			break;

		case 17:
			// 走行速度の追加ランダム値
			sscanf(buffer, "%*[^:]:%f", &m_RandomRunSp);
			m_RunSp += ((m_RandomRunSp / 1000) * (rand() / (float)RAND_MAX));
			break;

		default:
			break;
		}
	}


	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	m_SearchCircle = 2.0f;		// これ使ってない

	m_Alive = true;

	m_HandednessR = true;
	if (rand() % 2 == 0)
	{
		m_HandednessR = false;
	}

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EndMovement = false;

	m_Model = new AnimationModel();
	m_Model->Load("model\\Zombie.fbx");
	m_Model->LoadAnimation("model\\Zombie_Attack.fbx", "Attack");
	m_Model->LoadAnimation("model\\Zombie_Walk.fbx", "Walk");
	m_Model->LoadAnimation("model\\Zombie_Run.fbx", "Run");
	m_Model->LoadAnimation("model\\Zombie_Survey.fbx", "Survey");
	m_Model->LoadAnimation("model\\Zombie_Threat.fbx", "Threat");
	m_Model->LoadAnimation("model\\Zombie_Lose.fbx", "Lose");
	m_Model->LoadAnimation("model\\Zombie_Idle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");
}

void EnemyB::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void EnemyB::Update()
{
	if (!m_Virgin)
	{
		m_Virgin = true;
	}
	Scene* scene = Manager::GetScene();
	Distance* distance = scene->GetGameObject<Distance>();

	// ステートからアップデート選択
	switch (m_EnemyBState)
	{
	case ENEMY_B_STATE_ROUND:
		distance->AddDistance(1);
		UpdateRound();
		break;

	case ENEMY_B_STATE_CAUTION:
		distance->AddDistance(2);
		UpdateCaution();
		break;

	case ENEMY_B_STATE_BATTLE:
		distance->AddDistance(3);
		UpdateBattle();
		break;

	default:
		break;
	}
}

void EnemyB::Draw()
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


	m_Model->Update(m_AnimationName.c_str(), m_time, m_NextAnimationName.c_str(), m_time, m_BlendRate);
	m_time++;

	m_BlendRate += 0.05f;
	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}


	m_Model->Draw();
}

// ステート アップデート
void EnemyB::UpdateRound()			// 巡回ステート
{
	if (m_ThinkingTimeCount < m_ThinkingTime)
	{
		// 思考硬直
		ThinkingTime();
	}
	else
	{
		if (m_EndMovement)
		{
			Survey(3);	// 3秒見渡し
		}
		else
		{
			Round();	// 巡回
		}
	}
	AutoRecovery();	// 自動回復
}
void EnemyB::UpdateCaution()		// 警戒ステート
{
	if (m_EndMovement)
	{
		Survey(6);	// 6秒見渡し
	}
	else
	{
		SetChangeState(ENEMY_B_STATE_ROUND);	// 巡回状態へ移行
	}
	AutoRecovery();	// 自動回復
}
void EnemyB::UpdateBattle()			// 戦闘ステート
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	// 倒されていた場合
	if (!enemyA->GetAlive())
	{
		SetChangeState(ENEMY_B_STATE_ROUND);	// 巡回状態へ移行
	}

	// 目線追跡
	{
		D3DXVECTOR3 diff, enemyAPos = enemyA->GetPosition();
		diff.x = m_Position.x - enemyAPos.x;
		diff.y = m_Position.y - enemyAPos.y;
		diff.z = m_Position.z - enemyAPos.z;
	}

	if (m_ThinkingTimeCount < m_ThinkingTime)
	{
		// 思考硬直
		ThinkingTime();
	}
	else
	{
		if (!AttackAllowed() && m_AttackAnimationCount == 0)
		{
			Approach();
		}
		else
		{
			Attack();
		}
	}
}

void EnemyB::AddDamage(float Damage)
{
	m_HP -= Damage;
	if (m_HP <= 0.0f)
	{
		// 倒された
		Scene* scene = Manager::GetScene();
		Explosion* explosion = scene->AddGameObject<Explosion>(1);
		explosion->SetPosition(m_Position);
		m_Alive = false;
	}
}


void EnemyB::Move(D3DXVECTOR3 ObjectivePoint, bool Run)		// 移動
{
	// 目線追跡
	{
		D3DXVECTOR3 diff;
		diff.x = m_Position.x - ObjectivePoint.x;
		diff.y = m_Position.y - ObjectivePoint.y;
		diff.z = m_Position.z - ObjectivePoint.z;

		m_Rotation.y = atan2(diff.x, diff.z) + D3DX_PI;
	}

	// 目標への移動
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
			// 移動
			m_Position += m_Move;
		}
		// 視認確認
		if (m_SurveyCount % 30 == 0)	// 30秒に一度確認する
		{
			if (m_EnemyBState == ENEMY_B_STATE_BATTLE)
			{
				VisualSearch(m_DiscoveryAreaA);
			}
			else
			{
				// 移動中のため 狭い範囲で検索
				VisualSearch(m_DiscoveryAreaB);
			}
		}
	}
}
void EnemyB::Attack()	// 攻撃
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	// 目線追跡
	{
		D3DXVECTOR3 diff;
		diff.x = m_Position.x - enemyA->GetPosition().x;
		diff.y = m_Position.y - enemyA->GetPosition().y;
		diff.z = m_Position.z - enemyA->GetPosition().z;

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
			enemyA->AddDamage(m_AttackPoint);
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
void EnemyB::Approach()	// 近づく
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	Move(enemyA->GetPosition(), true);
}
void EnemyB::Round()	// 巡回
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
void EnemyB::Survey(int VigilantTime/*見渡し時間*/)		// 見渡す
{
	// ここに見渡す処理 or 視認検索
	if (m_NextAnimationName != "Survey")
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Survey";
		m_BlendRate = 0.0f;
	}

	m_SurveyCount++;

	// 視認検索確認
	if (m_SurveyCount % 30 == 0)	// 30秒に一度確認する
	{
		VisualSearch(m_DiscoveryAreaA);
	}

	// 見渡し終了判定
	if (m_SurveyCount >= VigilantTime * 60)
	{
		m_SurveyCount = 0;
		m_EndMovement = false;
		kakunin--;
	}
}
void EnemyB::AutoRecovery()	// 自動回復
{
	// ヒットポイント自動回復
	if (m_HP < m_MaxHP)
	{
		m_HP += m_AutoRecoveryAmount;
	}
	else
	{
		m_HP = m_MaxHP;
	}

	/*	エネミーB では使わない
	// マジックポイント自動回復
	if (m_MP < m_MaxMP)
	{
		m_MP += m_AutoRecoveryAmount;
	}
	else
	{
		m_MP = m_MaxMP;
	}
	*/
}
void EnemyB::VisualSearch(float DiscoveryArea)	// 視認検索
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	// 発見判定処理
	if (m_EnemyBState == ENEMY_B_STATE_ROUND)
	{
		D3DXVECTOR3 direction = m_Position - enemyA->GetPosition();
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < DiscoveryArea)
		{
			m_SurveyCount = 0;
			m_EndMovement = false;
			SetChangeState(ENEMY_B_STATE_BATTLE);	// 戦闘状態へ移行
		}
	}
	else
	{
		D3DXVECTOR3 direction = m_Position - enemyA->GetPosition();
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);

		if (length < m_UnDiscoveryArea)
		{
			if (m_EnemyBState == ENEMY_B_STATE_CAUTION)
			{
				m_SurveyCount = 0;
				m_EndMovement = false;
				SetChangeState(ENEMY_B_STATE_BATTLE);	// 戦闘状態へ移行
			}
		}
		else
		{
			if (m_EnemyBState == ENEMY_B_STATE_BATTLE)
			{
				m_EndMovement = true;
				m_SurveyCount = 0;
				SetChangeState(ENEMY_B_STATE_CAUTION);	// 警戒状態へ移行
			}
		}
	}
	/*
	// 敵A の視界内検索
	for (EnemyA* enemy : enemys)
	{

	}*/
}
void EnemyB::ThinkingTime()	// 思考硬直時間
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	m_ThinkingTimeCount++;
	if (m_ThinkingTimeCount > m_ThinkingTime / 2)
	{
		if (m_EnemyBState == ENEMY_B_STATE_ROUND)	// 巡回状態へ移行時
		{
			if (m_KillCount == 0)
			{
				if (enemyA->GetAlive())
				{
					// 見失って怒る
					if (m_NextAnimationName != "Lose")
					{
						m_AnimationName = m_NextAnimationName;
						m_NextAnimationName = "Lose";
						m_BlendRate = 0.0f;
					}
				}
			}
		}
		/*else if (m_EnemyBState == ENEMY_B_STATE_CAUTION)	// 警戒状態へ移行時
		{
		}*/
		else if (m_EnemyBState == ENEMY_B_STATE_BATTLE)		// 戦闘状態へ移行時
		{
			// 発見時 威嚇
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
bool EnemyB::AttackAllowed()	// 攻撃行動 可否
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();

	// 対象との距離が近い場合「true」を返す

	D3DXVECTOR3 direction = m_Position - enemyA->GetPosition();
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	if (length < m_MeleeRange)
	{
		return true;
	}
	return false;
}

bool EnemyB::GetAlive()
{
	Scene* scene = Manager::GetScene();
	EnemyA* enemyA = scene->GetGameObject<EnemyA>();
	
	if (!m_Alive)
	{
		enemyA->SetKillCount();
		SetDestroy();
	}
	return m_Alive;
}
