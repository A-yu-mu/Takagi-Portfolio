#pragma once
#include "gameObject.h"
class EnemyAState : public GameObject
{	// 敵A の ステートの表示
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture0{};
	ID3D11ShaderResourceView* m_Texture1{};
	ID3D11ShaderResourceView* m_Texture2{};
	ID3D11ShaderResourceView* m_Texture3{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_EnemyAState{};

	const char* m_TextureName = "texture\\transmission.png";

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddEnemyAState(int EnemyAState) { m_EnemyAState = EnemyAState; }
	int GetEnemyAState() { return m_EnemyAState; }

	void SetTexture(const char* Texture)
	{
		m_TextureName = Texture;
	}
};