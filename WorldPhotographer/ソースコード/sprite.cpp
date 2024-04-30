//*********************************************************
// sprite.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬��2022/06/13
//*********************************************************

#include "renderer.h"
#include "sprite.h"


//=================================================
//�}�N����`
//=================================================
#define	NUM_VERTEX	(4)		//�X�v���C�g�̒��_��


#define	BOX_W	(400)	//�l�p�`�̉��̃T�C�Y
#define	BOX_H	(400)	//�l�p�`�̏c�̃T�C�Y

//=================================================
//�v���g�^�C�v�錾
//=================================================


//=================================================
//�O���[�o���ϐ�
//=================================================
static	ID3D11Buffer* g_VertexBufferTriangle = NULL;	//�l�p�`�p

//float	PositionX = SCREEN_WIDTH / 2;//��ʒ������W
//float	PositionY = SCREEN_HEIGHT / 2;
//float	Kakudo = 0; //�l�p�`�̉�]�p�x



//=================================================
//�O�p�`�p���_�i�[����
//=================================================
void DrawSpriteColorRotation(float PosX, float PosY, int Size_W, int Size_H, float Kakudo,D3DXCOLOR col, float PaternNo, float uv_w, float uv_h, int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	static	float offset = 0.0f;
	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f+offset, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f + offset, 0.0f);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f + offset, 1.0);
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f + offset, 1.0f);
	//offset += 1.0f / 200.0f;


	//UV�A�j���[�V����
	//�{���͈����Ŏw�肷��p�����[�^�[
	//static	float	PaternNo = 0;	//�p�^�[���ԍ�
	//float	uv_w = 0.5f;			//���T�C�Y
	//float	uv_h = 0.5f;			//�c�T�C�Y
	//int		NumPatern = 2;			//������

	//UV���W�̌v�Z
	int no = PaternNo;	//�p�^�[���ԍ��𐮐��l�ɂ��� �����_�ȉ����̂Ă�
	float	u = (no % NumPatern) * uv_w;
	float	v = (no / NumPatern) * uv_h;

	//UV���W�̏�������
	vertex[0].TexCoord = D3DXVECTOR2(u, v);				//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);		//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);		//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);	//RIGHT-BOTTOM

	/*PaternNo += 0.005f;
	if (PaternNo >= 4.0f) { PaternNo -= 4.0f; }*/

	//�x�����W�A���֕ϊ�����
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		//���@�藝		
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + PosX;	//���s�ړ��i���S�����炷�j
		vertex[i].Position.y = y + PosY;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//�������ݏI��


	//�`��ݒ�
	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=================================================
//�t�H�g�̕`���p���� by�ڍ�
// PosX, PosY, Size_W, Size_H, col
// �����X���̃��C���[�ɂ��������
// os
// ���`�悵�������W
//=================================================
void DrawSpritePhoto(float PosX, float PosY, int Size_W, int Size_H, D3DXCOLOR col, D3DXVECTOR2 pos)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(-Size_W / 2, -Size_H / 2, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(+Size_W / 2, -Size_H / 2, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	//���_ V2���Z�b�g
	vertex[2].Position = D3DXVECTOR3(-Size_W / 2, +Size_H / 2, 0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0);
	//���_ V3���Z�b�g
	vertex[3].Position = D3DXVECTOR3(+Size_W / 2, +Size_H / 2, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	//offset += 1.0f / 200.0f;

	//�����ł�����Ă���Pos��Size������TexCoord���v�Z����
	float LineLeft = (PosX - (Size_W / 2)) / SCREEN_WIDTH;
	float LineRight = (PosX + (Size_W / 2)) / SCREEN_WIDTH;
	float LineTop = (PosY - (Size_H / 2)) / SCREEN_HEIGHT;
	float LineBottom = (PosY + (Size_H / 2)) / SCREEN_HEIGHT;



	//UV���W�̏�������
	vertex[0].TexCoord = D3DXVECTOR2(LineLeft, LineTop);//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(LineRight, LineTop);//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(LineLeft, LineBottom);//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(LineRight, LineBottom);//RIGHT-BOTTOM


	for (int i = 0; i < 4; i++)
	{
		vertex[i].Position.x += pos.x;	//���s�ړ��i���S�����炷�j
		vertex[i].Position.y += pos.y;
	}
	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//�������ݏI��


	//�`��ݒ�
	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// �|���S���`��
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
//*********************************************************
//����������
//*********************************************************

void InitSprite()
{
	{//�O�p�`�p�̒��_����������
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		//�O�p�`�p���_�i�[����
		//SetVertexTringle(PositionX, PositionY, BOX_W, BOX_H, 0);
	}
}
//*********************************************************
//�I������
//*********************************************************

void UninitSprite()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//�g���I������̂ŉ������
		g_VertexBufferTriangle = NULL;
	}
}


//�����������������������������������������������������������������������������[
