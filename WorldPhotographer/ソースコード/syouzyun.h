//=============================================================================
//cursor_A.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================


#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define CURSOR_A_SIZE_W (80)
#define	CURSOR_A_SIZE_H (80)

static	ID3D11ShaderResourceView* g_Texture_A;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_A = (char*)"data\\texture\\fokasu_5.jpeg";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_B;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_B = (char*)"data\\texture\\haikei.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T1;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_T1 = (char*)"data\\texture\\1.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T2;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_T2 = (char*)"data\\texture\\2.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T3;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_T3 = (char*)"data\\texture\\3.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T4;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_T4 = (char*)"data\\texture\\4.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T5;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName_T5 = (char*)"data\\texture\\5.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


struct CURSOR_A
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X

	float texno_B;
	bool camera_use;

	float texno_T1;
	float texno_T2;
	float texno_T3;
	float texno_T4;
	float texno_T5;
	int zoom;

	int a = 10;
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitCursor_A();
void    UnInitCursor_A();
void    DrawCursor_A();
void    UpdateCursor_A();
CURSOR_A* GetCursor_A(); //CURSOR_A�\���̂̐擪�|�C���^���擾



