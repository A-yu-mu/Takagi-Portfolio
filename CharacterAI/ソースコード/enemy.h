#pragma once
#include "model.h"
#include "gameObject.h"
class Enemy : public GameObject
{
private:
	float m_discoveryArea; 
	float m_undiscoveryArea;
	float m_searchCircle;
	bool m_discovery;	// �����������ǂ����̃t���O
	bool m_undiscovery;	// �ǐՃt���O
	int m_discoveryCount;	// ������̍d���J�E���g
	D3DXVECTOR3 m_move;	// ���������̈ړ����x
	D3DXVECTOR3 m_undiscoveryPosition;	// ���������̈ړ����x
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

	// void AddDamage(float Damage);	// �_���[�W
};