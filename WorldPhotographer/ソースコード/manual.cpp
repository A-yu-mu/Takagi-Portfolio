//=============================================================================
// manual.cpp
// 作成者：髙木歩夢　作成日：2023/01/25
//=============================================================================

#include "manual.h"
#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
#include "UI.h"
#include "fade.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================

static MANUAL g_manual;

float pattern_num_manual = 0;
float yoko_num_manual = 10;
float tate_num_manual = 6;
int   pattern_size_manual = 60;


//===================================
//初期化
//===================================
HRESULT InitManual()
{
	g_manual.select_manual = 0;
	g_manual.temp_select_manual = 0;

	g_manual.h = SCREEN_HEIGHT;
	g_manual.w = SCREEN_WIDTH;
	g_manual.texbg = LoadTexture(g_Texture_ManualBG);
	g_manual.texkeyboard = LoadTexture(g_Texture_ManualKeyboard);
	g_manual.texpad = LoadTexture(g_Texture_ManualPad);

	// PlayBGM(BGM_01);
	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitManual()
{
	StopSoundAll();
}


//===================================
//描画
//===================================
void    DrawManual()
{
	// 背景画像
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texbg));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_manual.w, g_manual.h, 0, g_manual.BGColor, 0, 1.0f, 1.0f, 1.0f);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}

	switch (g_manual.select_manual)
	{
	case 0:
	// パッド操作画像
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texpad));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH /2, SCREEN_HEIGHT *3/ 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
	break;

	case 1:
	// キーボード操作画像
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texkeyboard));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
	break;

	case 2:
		switch (g_manual.temp_select_manual)
		{
		case 0:
			// パッド操作画像
		{
			//テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texpad));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		break;

		case 1:
			// キーボード操作画像
		{
			//テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texkeyboard));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		break;
		}
		// 未選択時 影
		{
			//テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texbg));

			//スプライト表示
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_manual.w, g_manual.h, 0, g_manual.ShadowColor, 0, 1.0f, 1.0f, 1.0f);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		break;
	}
}


//===================================
//更新
//===================================
void    UpdateManual()
{
	if (IsButton(L_RIGHT, TRIGGER))
	{
		if (g_manual.select_manual == 0)
		{
			g_manual.select_manual += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_LEFT, TRIGGER))
	{
		if (g_manual.select_manual == 1)
		{
			g_manual.select_manual -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_DOWN, TRIGGER))
	{
		if (g_manual.select_manual <= 1)
		{
			g_manual.temp_select_manual = g_manual.select_manual;
			g_manual.select_manual = 2;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_UP, TRIGGER))
	{
		if (g_manual.select_manual == 2)
		{
			g_manual.select_manual = g_manual.temp_select_manual;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		if (g_manual.select_manual == 2)
		{
			// ステージセレクト
			SetFade(FADE_OUT_TITLE);
		}
		PlaySE(SE_OK);
	}
}

MANUAL* GetManual()
{
	return &g_manual;
}

