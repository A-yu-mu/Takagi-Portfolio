//=============================================================================
//result.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/11/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================

// �^�C�����~�b�g�\���ʒu
#define TIMELIMIT_R_POS_X (SCREEN_WIDTH/2)
#define	TIMELIMIT_R_POS_Y (SCREEN_HEIGHT/5)

static	ID3D11ShaderResourceView* g_Textureresult;//�摜1����1�̕ϐ����K�v
static	char* g_TextureResultName = (char*)"data\\texture\\fade_white.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRank = (char*)"data\\texture\\RANK.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_S;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRank_S = (char*)"data\\texture\\UOWs_S.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_A;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRank_A = (char*)"data\\texture\\UOWs_A.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_B;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRank_B = (char*)"data\\texture\\UOWs_B.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_C;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRank_C = (char*)"data\\texture\\UOWs_C.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


struct RESULT
{
	D3DXVECTOR2	Size;	//�|���S���̃T�C�Y
	D3DXVECTOR2 pos;	//�\�����W
	float texno;    //�e�N�X�`���C���f�b�N�X
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texRank;
	float texRank_S;
	float texRank_A;
	float texRank_B;
	float texRank_C;

	int limit_0;
	int limit_rank;
	int select_result = 0;
};

//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitResult();
void    UnInitResult();
void    DrawResult();
void    UpdateResult();
RESULT* GetResult(); //RESULT�\���̂̐擪�|�C���^���擾



