#pragma once
#include "gameObject.h"
class Death : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool m_Death{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddDeath(bool Death) { m_Death = Death; }

	int GetDeath() { return m_Death; }
};