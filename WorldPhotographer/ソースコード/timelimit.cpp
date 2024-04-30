//=============================================================================
// timilimit.cpp
// 作成者：髙木歩夢　作成日：2022/11/16
//=============================================================================

#include "timelimit.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "stage_select.h"

//===================================
//マクロ定義
//===================================


//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================


static TimeLimit g_timelimit;
static PLAYER* p_player;

int timelimit_stage_num;

//===================================
//初期化
//===================================
HRESULT InitTimeLimit()
{
	// 制限時間の初期化
	g_timelimit.pos.x = 0 + 80;
	g_timelimit.pos.y = 0 + 100;

	g_timelimit.Size = D3DXVECTOR2(TIMELIMIT_SIZE_W, TIMELIMIT_SIZE_H);

	g_timelimit.use = true;
	g_timelimit.PlayerGoal = false;

	g_timelimit.texno = LoadTexture(g_TextureNumber);

	//g_timelimit.Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)

	timelimit_stage_num = GetStageNum();

	switch (timelimit_stage_num)
	{
	// ステージ 1-1
	case 0:
		g_timelimit.Limit = TIMELIMIT_STAGE_01;
		break;

	// ステージ 1-2
	case 1:
		g_timelimit.Limit = TIMELIMIT_STAGE_02;
		break;

	// ステージ 1-3
	case 2:
		g_timelimit.Limit = TIMELIMIT_STAGE_03;
		break;

	// ステージ 2-1
	case 3:
		g_timelimit.Limit = TIMELIMIT_STAGE_04;
	default:

	// ステージ 2-2
	case 4:
		g_timelimit.Limit = TIMELIMIT_STAGE_05;
		break;

	// ステージ 2-3
	case 5:
		g_timelimit.Limit = TIMELIMIT_STAGE_06;
		break;

	// ステージ 3-1
	case 6:
		g_timelimit.Limit = TIMELIMIT_STAGE_07;
		break;

	// ステージ 3-2
	case 7:
		g_timelimit.Limit = TIMELIMIT_STAGE_08;
		break;

	// ステージ 3-3
	case 8:
		g_timelimit.Limit = TIMELIMIT_STAGE_09;
		break;
	}

	return S_OK;
}


//===================================
//更新
//===================================
void    UpdateTimeLimit()
{
	if (g_timelimit.PlayerGoal == false && g_timelimit.Limit > 0)
	{
		g_timelimit.Limit -= 1;
	}
}

//===================================
//終了
//===================================
void    UnInitTimeLimit()
{
	
}


//===================================
//描画
//===================================
void    DrawTimeLimit()
{
	// 制限時間表示
	if (g_timelimit.use)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_timelimit.texno));
		int limit = g_timelimit.Limit / 60;

		for (int tl = 0; tl < TIMELIMIT_NUM; tl++)
		{
			int n;
			float tx, ty;

			n = limit % 10; 
			
			tx = (n % 10) /** 0.1*/;
			// ty = 1;// (n / 5) * 0.2;

			limit /= 10;

			float sx, sy;
			sx = TIMELIMIT_POS_X + 30.0f * (TIMELIMIT_NUM - 1 - tl);
			sy = TIMELIMIT_POS_Y;

			DrawSpriteColorRotation(sx, sy, g_timelimit.Size.x, g_timelimit.Size.y, g_timelimit.rot, g_timelimit.Color, tx, 1.0f/10, 1, 10);
		}
	}
}

//===================================
// ゲット関数
//===================================
int GetTimeLimit(void)
{
	return g_timelimit.Limit;
}

TimeLimit* GetTimeLimit2(void)
{
	return &g_timelimit;
}