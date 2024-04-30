//=============================================================================
// timelimit.h
// �쐬�ҁF���ؕ����@�쐬���F2022/11/16
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
#include "player.h"
//====================================
//�}�N����`
//====================================

#define FRAME_RATE (60)

#define TIMELIMIT_POS_X (SCREEN_WIDTH/10)
#define	TIMELIMIT_POS_Y (SCREEN_HEIGHT/10)

#define TIMELIMIT_SIZE_W (50)
#define	TIMELIMIT_SIZE_H (50)

#define TIMELIMIT_NUM (3)		// ����

#define TIMELIMIT_STAGE_01 (250*FRAME_RATE)
#define TIMELIMIT_STAGE_02 (280*FRAME_RATE)
#define TIMELIMIT_STAGE_03 (300*FRAME_RATE)
#define TIMELIMIT_STAGE_04 (360*FRAME_RATE)
#define TIMELIMIT_STAGE_05 (380*FRAME_RATE)
#define TIMELIMIT_STAGE_06 (400*FRAME_RATE)
#define TIMELIMIT_STAGE_07 (500*FRAME_RATE)
#define TIMELIMIT_STAGE_08 (550*FRAME_RATE)
#define TIMELIMIT_STAGE_09 (600*FRAME_RATE)

static	ID3D11ShaderResourceView* g_Texture_Number;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNumber = (char*)"data\\texture\\number.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct TimeLimit
{
	bool use;		//�\���̗��p���t���O
	bool PlayerGoal;

	int Limit;

	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitTimeLimit();
void    UnInitTimeLimit();
void    DrawTimeLimit();
void    UpdateTimeLimit();

int GetTimeLimit(void);
TimeLimit*	GetTimeLimit2(void);

