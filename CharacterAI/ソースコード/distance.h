#pragma once
#include "gameObject.h"
class Distance : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture0{};
	ID3D11ShaderResourceView* m_Texture1{};
	ID3D11ShaderResourceView* m_Texture2{};
	ID3D11ShaderResourceView* m_Texture3{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Distance{};
	
	const char* m_TextureName = "texture\\transmission.png";

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddDistance(int Distance) { m_Distance = Distance; }
	int GetDistance() { return m_Distance; }

	void SetTexture(const char* Texture) 
	{
		m_TextureName = Texture;
	}
};