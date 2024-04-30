#pragma once
#include "model.h"
#include "gameObject.h"
class Enemy : public GameObject
{
private:
	float m_discoveryArea; 
	float m_undiscoveryArea;
	float m_searchCircle;
	bool m_discovery;	// 発見したかどうかのフラグ
	bool m_undiscovery;	// 追跡フラグ
	int m_discoveryCount;	// 発見後の硬直カウント
	D3DXVECTOR3 m_move;	// 未発見時の移動速度
	D3DXVECTOR3 m_undiscoveryPosition;	// 未発見時の移動速度
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_StartPosition{};

	bool m_Virgin = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// void AddDamage(float Damage);	// ダメージ
};