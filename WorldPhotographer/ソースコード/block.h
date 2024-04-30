//=============================================================================
//block.h
// �쐬�ҁF�ݒ���/���їǑ��@�쐬���F2022/10/21
//=============================================================================

#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define BLOCK_MAX 10
static	ID3D11ShaderResourceView* g_TextureBlock;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNameBlock = (char*)"data\\texture\\GrassBlock.jpg";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
//====================================
//�\����
//====================================

struct BLOCK
{
	bool use;		//�\���̗��p���t���O
	D3DXVECTOR2 size;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;

};



//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT   InitBlock();
void    UnInitBlock();
void    DrawBlock();
void    UpdateBlock();

void SetBlock(float x, float y, float px, float py);
BLOCK* GetBlock();



#endif // !BLOCK_H_
