#pragma once
#include "animationModel.h"
#include "gameObject.h"


enum ENEMY_B_STATE
{
	ENEMY_B_STATE_ROUND,	// 巡回ステート
	ENEMY_B_STATE_CAUTION,	// 警戒ステート
	ENEMY_B_STATE_BATTLE	// 戦闘ステート
};

class EnemyB : public GameObject
{
private:
	ENEMY_B_STATE m_EnemyBState = ENEMY_B_STATE_ROUND;	// 現在のステート
	int m_KillCount = 0;	// 倒した数
	bool m_Alive;		// 生きているか
	bool m_HandednessR;	// 利き手は右か (移動中に触れたオブジェクトを避ける方向)

	float m_HP;				// ヒットポイント
	float m_MaxHP;			// Maxヒットポイント
	float m_AutoRecoveryAmount;	// 自動回復量
	float m_MeleeRange;		// 近接攻撃可能範囲
	float m_AttackRate;		// 攻撃レート	// 値秒間隔で攻撃する
	float m_RandomAttackRate;		// 攻撃レート +ランダム値

	float m_AttackPoint;	// 攻撃力
	float m_RandomAttackPoint;	// 攻撃力 +ランダム値
	int m_AttackRateCount = 0;		// 攻撃レートカウント
	int m_AttackAnimationCount = 0;	// 攻撃アニメーションを正常に表示させる為のカウント

	// bool m_Discovery;		// 発見したかどうかのフラグ		// エネミーBでは使わない

	float m_DiscoveryAreaA;	// 視認範囲
	float m_DiscoveryAreaB;	// 視認範囲
	float m_UnDiscoveryArea;// 未 視認範囲	// 見失う距離
	float m_SearchCircle;	// 探索サークル		// いずれ扇状の索敵範囲として使いたい
	int m_ThinkingTime;		// 思考硬直
	int m_RandomThinkingTime;	// 思考硬直の +ランダム値
	int m_ThinkingTimeCount;	// 思考硬直カウント
	int m_SurveyCount = 0;	// 視認確認 秒数カウント

	int kakunin = 0;

	D3DXVECTOR3 m_TravelDirection;	// 移動方向
	D3DXVECTOR3 m_ObjectivePoint;	// 目標地点


	D3DXVECTOR3 m_Move;		// 移動量
	float m_WalkSp;	// 歩行 速度
	float m_RandomWalkSp;	// 歩行 速度 +ランダム値
	float m_RunSp;	// 走行 速度
	float m_RandomRunSp;	// 走行 速度 +ランダム値
	bool m_EndMovement;	// 移動完了フラグ

	// モデル・アニメーション
	AnimationModel* m_Model{};
	int m_time{};
	float m_BlendRate{};
	std::string m_NextAnimationName;
	std::string m_AnimationName;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool m_Virgin = false;	// 最初のみに動く

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// ステートの遷移
	void SetChangeState(ENEMY_B_STATE ChangeState)
	{
		m_ThinkingTimeCount = 0;
		m_EnemyBState = ChangeState;
	}

	// プレイヤーの状況に合わせて更新を行う
	void UpdateRound();			// 巡回ステート
	void UpdateCaution();		// 警戒ステート
	void UpdateBattle();		// 戦闘ステート

	void AddDamage(float Damage);	// ダメージ

	// ビヘイビアで使用する関数
	void Move(D3DXVECTOR3 ObjectivePoint,bool Run);	// 移動
	void Attack();	// 攻撃
	void Approach();// 近づく
	void Round();	// 巡回
	void Survey(int VigilantTime/*見渡し時間*/);	// 見渡す
	void AutoRecovery();	// 自動回復
	void VisualSearch(float DiscoveryArea);	// 視認検索
	void ThinkingTime();	// 思考硬直時間
	// void Pathfinding();		// 経路探索
	bool AttackAllowed();	// 攻撃行動 可否
	bool GetAlive();		// 生きているかどうか
	void SetKillCount() { m_KillCount++; };
};