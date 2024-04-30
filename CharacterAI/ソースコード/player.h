#pragma once
// #include "model.h"
#include "gameObject.h"
#include "animationModel.h"
#include <string>

enum PLAYER_STATE
{
	PLAYER_STATE_GROUND,
	PLAYER_STATE_JUMP
};

class Player : public GameObject
{
private:
	PLAYER_STATE m_PlayerState = PLAYER_STATE_GROUND;

	float m_HP;				// ヒットポイント
	float m_MaxHP;			// Maxヒットポイント
	float m_MP;				// マジックポイント
	float m_MaxMP;			// Maxマジックポイント
	float m_AutoRecoveryAmount;	// 自動回復量

	bool m_IsGround{};

	int m_Operate = 2;

	bool  m_IsJumping;
	float m_JumpForce;
	float m_JumpHeight;
	float m_JumpStartHeight;
	float m_GravitySpeed;
	float m_GroundHeight;

	D3DXVECTOR3 m_OldPosition;

	//Model* m_Model{};
	AnimationModel* m_Model{};
	
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Velocity{};

	class Audio* m_ShotSE{};
	class Shadow* m_Shadow{};

	D3DXMATRIX m_Matrix;

	int m_time{};
	float m_BlendRate{};
	std::string m_NextAnimationName;
	std::string m_AnimationName;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// プレイヤーの状況に合わせて更新を行う
	void UpdateGround();
	void UpdateJump();
	
	D3DXMATRIX GetMatrix() { return m_Matrix; }

	int GetOperate() { return m_Operate; }
	D3DXVECTOR3 GetOldPosition() { return m_OldPosition; }

	void AddDamage(float Damage);	// ダメージ
};