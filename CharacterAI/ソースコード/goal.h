#pragma once
#include "model.h"
#include "gameObject.h"
class Goal : public GameObject
{
private:
	bool m_Goal;
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	bool GetGoal() { return m_Goal; }
	
};