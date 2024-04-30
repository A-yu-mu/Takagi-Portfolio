#pragma once
//=============================================================================
// tutorial.h
// �쐬�ҁF���ؕ����@�쐬���F2023/01/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================


static	ID3D11ShaderResourceView* g_Texture_Tutorial_01_01;//�摜1����1�̕ϐ����K�v
static	char* g_TextureTutorial_01_01 = (char*)"data\\texture\\tutorial_01_01.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


struct TUTORIAL
{
	bool use;		//�\���̗��p���t���O

	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texlife;    //�e�N�X�`���C���f�b�N�X
	float textutorial_01_01;
};

//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitTutorial();
void    UnInitTutorial();
void    DrawTutorial();
void    UpdateTutorial();