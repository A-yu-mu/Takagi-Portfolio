#include "main.h"
#include "renderer.h"
#include "goal.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "score.h"

void Goal::Init()
{
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Model = new Model();
	m_Model->Load("model\\porsion.obj");

	m_Goal = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");
}

void Goal::Uninit()
{

	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Goal::Update()
{
	Scene* scene = Manager::GetScene();
	Score* score = scene->GetGameObject<Score>();
	Player* player = scene->GetGameObject<Player>();


	// スコア(時間)の更新
	if (m_Goal == false)
	{
		score->AddCount(1);
	}

	float groundHeight = 0.0f;
	//円柱
	std::vector<Player*> cylinders = scene->GetGameObjects<Player>();
	D3DXVECTOR3 position = player->GetPosition();
	D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	D3DXVECTOR3 direction = m_Position - position;
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	if (length < scale.x)
	{
			// ゴール
			m_Goal = true;
	}
}

void Goal::Draw()
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

	m_Model->Draw();
}