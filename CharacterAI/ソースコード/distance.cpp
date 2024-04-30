// �S�[���ƃv���C���[�Ƃ̋�����UI�ł������

#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "goal.h"
#include "distance.h"
#include "sprite.h"

void Distance::Init()
{
	VERTEX_3D vertex[4];


	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "texture\\transmission.png", NULL, NULL, &m_Texture0, NULL);
	assert(m_Texture0);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "texture\\EnemyB_Round.png", NULL, NULL, &m_Texture1, NULL);
	assert(m_Texture1);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "texture\\EnemyB_Caution.png", NULL, NULL, &m_Texture2, NULL);
	assert(m_Texture2);
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "texture\\EnemyB_Battle.png", NULL, NULL, &m_Texture3, NULL);
	assert(m_Texture3);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");
}

void Distance::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture0->Release();
	m_Texture1->Release();
	m_Texture2->Release();
	m_Texture3->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Distance::Update()
{
	GameObject::Update();

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Goal* goal = scene->GetGameObject<Goal>();

	D3DXVECTOR3 PlayerPosition = player->GetPosition();
	D3DXVECTOR3 GoalPosition = goal->GetPosition();

	/*
	if ((PlayerPosition.x - GoalPosition.x)*(PlayerPosition.x - GoalPosition.x) + (PlayerPosition.z - GoalPosition.z)*(PlayerPosition.z - GoalPosition.z) <= 10 * 10)
	{
		if (GetDistance() != 1)
		{
			// ������10�ȓ�
			AddDistance(1);
		}
	}
	else if ((PlayerPosition.x - GoalPosition.x) * (PlayerPosition.x - GoalPosition.x) + (PlayerPosition.z - GoalPosition.z) * (PlayerPosition.z - GoalPosition.z) <= 20 * 20)
	{
		if (GetDistance() != 2)
		{
			// ������20�ȓ�
			AddDistance(2);
		}
	}
	else if ((PlayerPosition.x - GoalPosition.x) * (PlayerPosition.x - GoalPosition.x) + (PlayerPosition.z - GoalPosition.z) * (PlayerPosition.z - GoalPosition.z) <= 40 * 40)
	{
		if (GetDistance() != 3)
		{
			// ������40�ȓ�
			AddDistance(3);
		}
	}
	else
	{
		if (GetDistance() != 0)
		{
			// ���������Ȃ藣��Ă��� (��L�ȏ㗣��Ă���)
			AddDistance(0);
		}
	}*/
	if (GetDistance() == 1)
	{
		AddDistance(1);
	}
	else if (GetDistance() == 2)
	{
		AddDistance(2);
	}
	else if (GetDistance() == 3)
	{
		AddDistance(3);
	}
	else
	{
		AddDistance(0);
	}

}

void Distance::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();


	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	//�e�N�X�`���ݒ�
	switch (GetDistance())
	{
	case 0:
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture0);
		break;

	case 1:
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture1);
		break;

	case 2:
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture2);
		break;

	case 3:
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture3);
		break;

	default:
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture0);
		break;
	}

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);



	// ���_���W�̎Z�o
	float vx = 500 * 40.0f;
	float vy = 20;
	float height = 200;
	float width = 400;



	// ���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(0.0f + 10.0f, SCREEN_HEIGHT - height - 5.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0, 0);

	vertex[1].Position = D3DXVECTOR3(width + 10.0f, SCREEN_HEIGHT - height - 5.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1, 0);

	vertex[2].Position = D3DXVECTOR3(0 + 10.0f, SCREEN_HEIGHT - 5.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0, 1.0f);

	vertex[3].Position = D3DXVECTOR3(width + 10.0f, SCREEN_HEIGHT - 5.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


	//�|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}