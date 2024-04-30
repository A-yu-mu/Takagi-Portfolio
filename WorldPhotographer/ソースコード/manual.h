//=============================================================================
// manual.h
// �쐬�ҁF���ؕ����@�쐬���F2023/01/25
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================

static	ID3D11ShaderResourceView* g_TextureManualBG;//�摜1����1�̕ϐ����K�v
static	char* g_Texture_ManualBG = (char*)"data\\texture\\fade_white.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualKeyboard;//�摜1����1�̕ϐ����K�v
static	char* g_Texture_ManualKeyboard = (char*)"data\\texture\\keyboard_manual.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualPad;//�摜1����1�̕ϐ����K�v
static	char* g_Texture_ManualPad = (char*)"data\\texture\\Pad_manual.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


struct MANUAL
{
	int select_manual;
	int temp_select_manual;

	float w, h;     //box�T�C�Y
	float texbg;    //�e�N�X�`���C���f�b�N�X
	float texkeyboard;    //�e�N�X�`���C���f�b�N�X
	float texpad;    //�e�N�X�`���C���f�b�N�X
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ShadowColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);
};
//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitManual();
void    UnInitManual();
void    DrawManual();
void    UpdateManual();
MANUAL* GetManual(); // MANUAL�\���̂̐擪�|�C���^���擾



