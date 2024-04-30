#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "scene.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_isView = true;
}

void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	
	int operate = player->GetOperate();

	if (operate == 0)
	{
		// サードパーソンビュ
		m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		m_Position = m_Target - player->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
	else if (operate == 1)
	{
		// トップビュー
		m_Target = player->GetPosition();
		m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	}
	else
	{
		// ファーストパーソンビュー
		m_Position = player->GetPosition() + D3DXVECTOR3(0.0f, 2.5f, 0.0f);
		m_Target = m_Position + player->GetForward();
	}

	
}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

void Camera::SetFPSView()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	m_Position = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	m_Target = m_Position + player->GetForward();
}

void Camera::SetTPSView()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Position = m_Target - player->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}