/*==============================================================================

   ���_�Ǘ� [polygon.cpp]								Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "sprite.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX_LINESTRIP (64)	//���C���X�g���b�v���_�ő吔

#define	BOX_W	(80)	//�l�p�`�̉��̃T�C�Y
#define	BOX_H	(80)	//�l�p�`�̏c�̃T�C�Y

#define FIELD_W (SCREEN_WIDTH)
#define FIELD_H (SCREEN_HEIGHT / 2 + 120)



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void	SetVertexLineStrip(int);							//���C���X�g���b�v���_�i�[����
void	SetVertexLine(float, float, float, float,float);			//�����p���_�i�[����
void	SetVertexCircle(float, float, float, int, D3DXCOLOR);	//���p�`�̕\��


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static	ID3D11Buffer		*g_VertexBufferLineStrip = NULL;//���C���X�g���b�v�p
static	ID3D11Buffer		*g_VertexBufferLine = NULL;		//�����p

static	ID3D11Buffer		*g_VertexBufferCircle = NULL;	//���p�`�p



float	PositionX = SCREEN_WIDTH / 2;//��ʒ������W
float	PositionY = SCREEN_HEIGHT / 2;
float	Kakudo = 0; //�l�p�`�̉�]�p�x

float	StartPositionX = 0;				//�����̃X�^�[�g���W
float	StartPositionY = 0;
float	EndPositionX = SCREEN_WIDTH;	//�����̏I�����W
float	EndPositionY = SCREEN_HEIGHT;


//�e�N�X�`�����̕ۑ��ϐ�


static	ID3D11ShaderResourceView* g_TextureBG;//�摜1����1�̕ϐ����K�v
static	char    * g_TextureNameBG = BG_01;//�e�N�X�`���t�@�C���p�X JPG BMP PNG


D3DXVECTOR3 Goal = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
D3DXVECTOR3 Speed;
D3DXVECTOR3 Start;


//�L�����N�^�[�\����

typedef struct
{
	D3DXVECTOR3 Position; //�\�����W
	D3DXCOLOR   Color;    //�\���F
	float       Rotation; //�p�x
	D3DXVECTOR2 size;	  //�|���S���̃T�C�Y

}PLAYER;

PLAYER mario;//�v���C���[�L�����N�^�[�\����

typedef struct
{
	D3DXVECTOR3 Position; //�\�����W
	D3DXCOLOR   Color;    //�\���F
	float       Rotation; //�p�x
	D3DXVECTOR2 size;	  //�|���S���̃T�C�Y
}BG;

BG *Bg;//�w�i�\���̂̃|�C���^�ϐ�

//texture�̃C���f�b�N�X

static int g_textureNo = 0;
static int g_textureNoBG = 0;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitPolygon(void)
{
	//�����̏�����
	srand(timeGetTime());
	//�|���S���̕\�����W�������_���Ɍ���
	PositionX = rand() % SCREEN_WIDTH;
	PositionY = rand() % SCREEN_HEIGHT;
	
	Start.x = PositionX;
	Start.y = PositionY;
	Start.z = 0.0f;

	//�ړI�n�܂ł̃x�N�g�������
	Speed = Goal - Start;
	//���K�����Ē������P�ɂ���
	D3DXVec3Normalize(&Speed, &Speed);
	//�x�N�g����C�ӂ̒����ɂ���
	Speed *= 10.0f;


	ID3D11Device *pDevice = GetDevice();

	//texture�̃��[�h
	g_textureNoBG = LoadTexture(g_TextureNameBG);
	if (g_textureNo == -1)
	{//���[�h�G���[
		exit(999);//�����I��
	}
	



	// ���_�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX_LINESTRIP;//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLineStrip);
		// ���_�o�b�t�@�X�V
		SetVertexLineStrip(4);
	}
	
	{//�����p
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 2;			//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLine);
		//�����p���_�i�[����
		SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY,30.0f);
	}
	{//���p�`�p
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 64;	//���_1�����_���̃T�C�Y�ō��
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferCircle);

		//���p�`�p���_�i�[����
		D3DXCOLOR	col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		SetVertexCircle(300.0f, 500.0f, 100.0f, 32, col);

	}

	InitSprite();

	//�w�i�̏�����
	Bg = new BG;//�w�i�̃C���X�^���X�쐬
	Bg->Position.x = SCREEN_WIDTH / 2;
	Bg->Position.y = SCREEN_HEIGHT / 2;
	Bg->Position.z = 0;

	Bg->size.x = SCREEN_WIDTH;
	Bg->size.y = SCREEN_HEIGHT;

	Bg->Rotation = 0.0f;

	Bg->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̉��
	if (g_VertexBufferLineStrip)
	{
		g_VertexBufferLineStrip->Release();//�g���I������̂ŉ������
		g_VertexBufferLineStrip = NULL;
	}

	if (g_VertexBufferLine)
	{
		g_VertexBufferLine->Release();//�g���I������̂ŉ������
		g_VertexBufferLine = NULL;
	}

	if (g_VertexBufferCircle)
	{
		g_VertexBufferCircle->Release();//�g���I������̂ŉ������
		g_VertexBufferCircle = NULL;
	}

	////�e�N�X�`���̉��
	//if (g_Texture)
	//{
	//	g_Texture->Release();
	//	g_Texture = NULL;
	//}

	//if (g_TextureBG)
	//{
	//	g_TextureBG->Release();
	//	g_TextureBG = NULL;
	//}

	UninitTexture();

	UninitSprite();

	//BG�\���̂̊J��
	if (Bg)
	{
		delete Bg;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{
	Start += Speed;//�ړ�����

	PositionX = Start.x;
	PositionY = Start.y;

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	// �Q�c�\�������邽�߂̃}�g���N�X��ݒ�
	SetWorldViewProjection2D();	
	
	{   //�w�i�̕`��

		GetDeviceContext()->PSSetShaderResources(0, 1,GetTexture(g_textureNoBG));
		D3DXCOLOR col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		//�O�p�`�̒��_�f�[�^���i�[
		DrawSpriteColorRotation(Bg->Position.x, Bg->Position.y, Bg->size.x, Bg->size.y, Bg->Rotation, Bg->Color,1,0.5f,1,1);

	}


}
//=============================================================================
// ���_�f�[�^�ݒ�
//=============================================================================
void SetVertexLineStrip(int	NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferLineStrip, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[0].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//��{�ڂ̒����̒��_���Z�b�g
	vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 50.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	GetDeviceContext()->Unmap(g_VertexBufferLineStrip, 0);
}
//===============================
//�����̒��_���i�[
//in
//  �J�n���WX, �J�n���WY, �I�����WX, �I�����WY
//
void	SetVertexLine(float StartX, float StartY, float EndX, float EndY,float kakudo)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//���_ V0���Z�b�g
	vertex[0].Position = D3DXVECTOR3(StartX, StartY, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//���_ V1���Z�b�g
	vertex[1].Position = D3DXVECTOR3(EndX, EndY, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//�p�x�����W�A���ɕύX����
	float rad = D3DXToRadian(kakudo);
	float x, y;

	x = vertex[1].Position.x * cosf(rad);
	y = vertex[1].Position.x * sinf(rad);

	vertex[1].Position.x += x + StartX;
	vertex[1].Position.y += y + StartY;


	GetDeviceContext()->Unmap(g_VertexBufferLine, 0);//�������ݏI��

}

//==============================
//���C���ő��p�`�̕\��
//in
//�@�\�����WX, �\�����WY, ���a, ���_��, �F
//
void	SetVertexCircle(float PosX, float PosY, float Rad, int NumVertex, D3DXCOLOR col)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	//���_�o�b�t�@�ւ̏������݋������炤
	GetDeviceContext()->Map(g_VertexBufferCircle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//���_�\���̂̌^�Ƀ|�C���^�[�^��ϊ�������
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float	kakudo = 0;
	for (int i = 0; i < NumVertex; i++)
	{
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + PosX;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + PosY;
		vertex[i].Position.z = 0.0f;
		vertex[i].Diffuse = col;
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		kakudo += (360.0f / NumVertex);
	}
	//�Ō�̒��_�ɍŏ��̒��_���R�s�[���Đ}�`�����
	vertex[NumVertex].Position = vertex[0].Position;
	vertex[NumVertex].Diffuse = vertex[0].Diffuse;
	vertex[NumVertex].TexCoord = vertex[0].TexCoord;

	GetDeviceContext()->Unmap(g_VertexBufferCircle, 0);//�������ݏI��
}


//�w�i�̃Z�b�g
void SetBGTexture(char* name)
{
	//texture�̃��[�h
	g_textureNoBG = LoadTexture(name);
	if (g_textureNo == -1)
	{//���[�h�G���[
		exit(999);//�����I��
	}
}