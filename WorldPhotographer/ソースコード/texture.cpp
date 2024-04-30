#include "texture.h"
//=============================================================================
//texture.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/13
//=============================================================================


//=================================================
//�}�N����`
//=================================================
#define MAX_TEXTURE_NUM (100)

//=================================================
//�v���g�^�C�v�錾
//=================================================


//=================================================
//�O���[�o���ϐ�
//=================================================
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];//���[�h�����e�N�X�`���̏��z��
static UINT  g_textureIndex = 0;//���[�h�����e�N�X�`���̖�����\��
static char  g_TextuerName[MAX_TEXTURE_NUM][256];//���[�h�����e�N�X�`���t�@�C�����̃o�b�t�@


//=================================================
//texture�̃��[�h
//=================================================
int LoadTexture(char* filename)
{

	//texture���̔�r
	for (int i = 0; i < g_textureIndex; i++)
	{
		if (strcmp(g_TextuerName[i], filename) == 0)

			return i;
	}

	if (g_textureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}


	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		filename,//�e�N�X�`���̃t�@�C����
		NULL,
		NULL,
		&g_pTexture[g_textureIndex],//���[�h�����e�N�X�`���̏��
		NULL
	);

	if (hr != S_OK)
	{
		return -1; //�G���[�Ƃ��ă}�C�i�X�l��Ԃ�
	}

	//texture���̓o�^
	strcpy_s(g_TextuerName[g_textureIndex], 256,filename);

	int retIndex = g_textureIndex;//���݂̐���ێ�

	g_textureIndex++;//�ǂݍ��񂾐����C���N�������g

	return retIndex;//�ǂݍ��񂾃e�N�X�`���̔ԍ���Ԃ�
}



//=================================================
//texture�̊J��
//=================================================
void UninitTexture()
{
	for (int i = 0; i < g_textureIndex; i++)
	{
		if (g_pTexture[i])
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}



//=================================================
//texture�̎擾
//=================================================
ID3D11ShaderResourceView** GetTexture(int index)
{
	if (index < 0)//�O�����̎�
	{
		return NULL;
	}
	if (index >= g_textureIndex)//�ǂݍ��ݐ��I�[�o�[
	{
		return NULL;
	}

	return &g_pTexture[index];//index���\���z��̃|�C���^

}
