//=============================================================================
//photoreticle.h
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//�T�C�Y���}�b�v�`�b�v�̃T�C�Y�ɘA��������
#include "mapchip.h"
//====================================
//�}�N����`
//====================================
#define PHOTORETICLE_SIZE_W (PHOTO_SIZE_W)
#define	PHOTORETICLE_SIZE_H (PHOTO_SIZE_H)

static	ID3D11ShaderResourceView* g_PhotoreticleTexture;//�摜1����1�̕ϐ����K�v
static	char* g_PhotoreticleTextureName = (char*)"data\\texture\\UI_Cam02.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct PHOTORETICLE
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X

};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPhotoreticle();
void    UnInitPhotoreticle();
void    DrawPhotoreticle();
void    UpdatePhotoreticle();
PHOTORETICLE* GetPhotoreticle(); //PHOTORETICLE�\���̂̐擪�|�C���^���擾

