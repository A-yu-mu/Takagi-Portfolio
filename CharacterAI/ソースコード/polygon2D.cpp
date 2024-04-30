#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"

void Polygon2D::Init()
{

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,"shader\\unlitTexturePS.cso");


	/*AddComponent<Sprite>();*/
	/*Sprite* sprite = AddComponent<Sprite>();
	sprite->Init(100.0f, 100.0f, 300.0f, 200.0f, "texture\\aaa.jpg");*/

	//AddComponent<Sprite>()->Init(20.0f,20.0f, 220.0f, 220.0f, "texture\\aaa.jpg");
	//AddComponent<Sprite>()->Init(50.0f, 50.0f, 100.0f, 200.0f, "texture\\aaa.jpg");
}

void Polygon2D::Uninit()
{
	
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Polygon2D::Update()
{
	GameObject::Update();

}

void Polygon2D::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	GameObject::Draw();

}

void Polygon2D::Title()
{
	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, "texture\\title_logo.jpg");
	
}

void Polygon2D::Result()
{
	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, "texture\\result_logo.jpg");

}

void Polygon2D::Select()
{

}

void Polygon2D::MiniMap()
{
	AddComponent<Sprite>()->Init(85.0f, 35.0f, 200.0f, 80.0f, 0.0f, 1.0f, "texture\\black.png");
}

void Polygon2D::SelectStage(int n)
{
	if (n == 1)
	{
		AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, "texture\\select_0.png");
	}
	else if (n == 2)
	{
		AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, "texture\\select_1.png");
	}
	else if (n == 3)
	{
		AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, "texture\\select_2.png");
	}
}
