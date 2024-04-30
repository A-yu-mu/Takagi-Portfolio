//=============================================================================
// timelimit.h
// 作成者：髙木歩夢　作成日：2022/11/16
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
#include "player.h"
//====================================
//マクロ定義
//====================================

#define FRAME_RATE (60)

#define TIMELIMIT_POS_X (SCREEN_WIDTH/10)
#define	TIMELIMIT_POS_Y (SCREEN_HEIGHT/10)

#define TIMELIMIT_SIZE_W (50)
#define	TIMELIMIT_SIZE_H (50)

#define TIMELIMIT_NUM (3)		// 桁数

#define TIMELIMIT_STAGE_01 (250*FRAME_RATE)
#define TIMELIMIT_STAGE_02 (280*FRAME_RATE)
#define TIMELIMIT_STAGE_03 (300*FRAME_RATE)
#define TIMELIMIT_STAGE_04 (360*FRAME_RATE)
#define TIMELIMIT_STAGE_05 (380*FRAME_RATE)
#define TIMELIMIT_STAGE_06 (400*FRAME_RATE)
#define TIMELIMIT_STAGE_07 (500*FRAME_RATE)
#define TIMELIMIT_STAGE_08 (550*FRAME_RATE)
#define TIMELIMIT_STAGE_09 (600*FRAME_RATE)

static	ID3D11ShaderResourceView* g_Texture_Number;//画像1枚で1つの変数が必要
static	char* g_TextureNumber = (char*)"data\\texture\\number.png";//テクスチャファイルパス JPG BMP PNG

struct TimeLimit
{
	bool use;		//構造体利用中フラグ
	bool PlayerGoal;

	int Limit;

	D3DXVECTOR2		Size;		//ポリゴンのサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitTimeLimit();
void    UnInitTimeLimit();
void    DrawTimeLimit();
void    UpdateTimeLimit();

int GetTimeLimit(void);
TimeLimit*	GetTimeLimit2(void);

