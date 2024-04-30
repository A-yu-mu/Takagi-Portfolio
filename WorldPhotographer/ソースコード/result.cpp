//=============================================================================
//result.cpp
// 作成者：岸直哉　作成日：2022/11/02
//=============================================================================

#include "result.h"
#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
#include "fade.h"

#include "timelimit.h"
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

static RESULT g_result;
TimeLimit g_r_timelimit;

float pattern_num_result = 0;
float yoko_num_result = 1;
float tate_num_result = 1;
int   pattern_size_result = 1;

// 現在のステージ
int result_stage_num;

//===================================
//初期化
//===================================
HRESULT InitResult()
{
	g_result.Size.x = SCREEN_WIDTH;
	g_result.Size.y = SCREEN_HEIGHT;
	g_result.pos.x = 0;
	g_result.pos.y = 0;
	g_result.texno = LoadTexture(g_TextureResultName);
	g_result.texRank = LoadTexture(g_TextureRank);
	g_result.texRank_S = LoadTexture(g_TextureRank_S);
	g_result.texRank_A = LoadTexture(g_TextureRank_A);
	g_result.texRank_B = LoadTexture(g_TextureRank_B);
	g_result.texRank_C = LoadTexture(g_TextureRank_C);

	g_result.limit_0 = GetTimeLimit();

	g_result.select_result = 0;

	g_r_timelimit.texno = LoadTexture(g_TextureNumber);

	result_stage_num = GetStageNum();

	switch (result_stage_num)
	{
		// ステージ 1-1
	case 0:
		if (GetStageNum() <= 1)
		{
			SetStageOpen(1);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_01;
		break;

		// ステージ 1-2
	case 1:
		if (GetStageNum() <= 2)
		{
			SetStageOpen(2);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_02;
		break;

		// ステージ 1-3
	case 2:
		if (GetStageNum() <= 3)
		{
			SetStageOpen(3);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_03;
		break;

		// ステージ 2-1
	case 3:
		if (GetStageNum() <= 4)
		{
			SetStageOpen(4);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_04;
	default:

		// ステージ 2-2
	case 4:
		if (GetStageNum() <= 5)
		{
			SetStageOpen(5);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_05;
		break;

		// ステージ 2-3
	case 5:
		if (GetStageNum() <= 6)
		{
			SetStageOpen(6);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_06;
		break;

		// ステージ 3-1
	case 6:
		if (GetStageNum() <= 7)
		{
			SetStageOpen(7);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_07;
		break;

		// ステージ 3-2
	case 7:
		if (GetStageNum() <= 8)
		{
			SetStageOpen(8);
		}
		g_result.limit_rank = TIMELIMIT_STAGE_08;
		break;

		// ステージ 3-3
	case 8:
		SetStageOpen(8);
		g_result.limit_rank = TIMELIMIT_STAGE_09;
		break;
	}

	PlaySE(SE_FANFARE);
	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitResult()
{
	StopSoundAll();
	//UninitTexture();
}


//===================================
//描画
//===================================
void    DrawResult()
{
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texno));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_result.Size.x, g_result.Size.y, 0, /*g_result.Color*/D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.4f) , pattern_num_result, tate_num_result / pattern_size_result, tate_num_result, pattern_size_result);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}

	

	// 制限時間表示
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_r_timelimit.texno));
		
		int limit = g_result.limit_0 / 60;

		for (int tl = 0; tl < TIMELIMIT_NUM; tl++)
		{
			int n;
			float tx, ty;

			n = limit % 10;

			tx = (n % 10) /** 0.1*/;
			// ty = 1;// (n / 5) * 0.2;

			limit /= 10;

			float sx, sy;
			sx = TIMELIMIT_R_POS_X + 55.0f * (TIMELIMIT_NUM - 1 - tl);
			sy = TIMELIMIT_R_POS_Y;

			DrawSpriteColorRotation(sx, sy, 85 ,85, 0, g_r_timelimit.Color, tx, 1.0f / 10, 1, 10);
		}
	}

	// ランク
	{
		// テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texRank));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH * 1 / 3, SCREEN_HEIGHT * 1 / 2, g_result.Size.x / 3, g_result.Size.y / 6, 0, g_result.Color, 0, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}

	// 評価ランク
	{
		// Sランク
		if (g_result.limit_0 > g_result.limit_rank * 3 / 5)
		{
			// テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texRank_S));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 1 / 2, g_result.Size.x / 4.5, g_result.Size.y / 3, 0, g_result.Color, 0, 1, 1, 1);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		// Aランク
		else if (g_result.limit_0 > g_result.limit_rank * 2 / 5)
		{
			// テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texRank_A));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 1 / 2, g_result.Size.x / 4.5, g_result.Size.y / 3, 0, g_result.Color, 0, 1, 1, 1);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		// Bランク
		else if (g_result.limit_0 > g_result.limit_rank * 1 / 5)
		{
			// テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texRank_B));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 1 / 2, g_result.Size.x / 4.5, g_result.Size.y / 3, 0, g_result.Color, 0, 1, 1, 1);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		// Cランク
		else
		{
			// テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_result.texRank_C));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT * 1 / 2, g_result.Size.x / 4.5, g_result.Size.y / 3, 0, g_result.Color, 0, 1, 1, 1);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
	}
}


//===================================
//更新
//===================================
void    UpdateResult()
{

	if (IsButton(L_RIGHT, TRIGGER))
	{
		if (g_result.select_result <= 1)
		{
			g_result.select_result += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_LEFT, TRIGGER))
	{
		if (g_result.select_result >= 1)
		{
			g_result.select_result -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		switch (g_result.select_result)
		{
		case 0:
			SetFade(FADE_OUT_TITLE);
			break;

		case 1:
			SetFade(FADE_OUT_GAME);
			break;

		case 2:
			// ステージセレクト
			 SetFade(FADE_OUT_STAGESELECT);
			break;
		}
		PlaySE(SE_OK);
	}
}

RESULT* GetResult()
{
	return &g_result;
}