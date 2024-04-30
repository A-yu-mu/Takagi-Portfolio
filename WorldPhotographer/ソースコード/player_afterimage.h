//=============================================================================
//player.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"

//====================================
//�}�N����`
//====================================

//static	ID3D11ShaderResourceView* g_Texture;//�摜1����1�̕ϐ����K�v
//static	char* g_TextureName = (char*)"data\\texture\\player_Idling.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
//
//static	ID3D11ShaderResourceView* g_Texture2;//�摜1����1�̕ϐ����K�v
//static	char* g_TextureName2 = (char*)"data\\texture\\player_walk.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
//
//static	ID3D11ShaderResourceView* g_Texture3;//�摜1����1�̕ϐ����K�v
//static	char* g_TextureName3 = (char*)"data\\texture\\player_jump.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct AfterImage
{
	bool use;		//�\���̗��p���t���O

	D3DXVECTOR2		size;		//�|���S���̃T�C�Y			
	D3DXVECTOR2 pos;//�\�����W
	D3DXVECTOR2 oldpos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	bool col;

	D3DXVECTOR2 scrpos;

	float ysp;

	float pattern_num;


};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitAfterImage();
void    UnInitAfterImage();
void    DrawAfterImage();
void    UpdateAfterImage();
AfterImage* GetAfterImage(); //PLAYER�\���̂̐擪�|�C���^���擾
void AfterImageReset();



