//=============================================================================
// gameOver.cpp
// 作成者：髙木歩夢　作成日：2022/12/04
//=============================================================================

#include "gameOver.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "io_ex.h"
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

static GameOver g_gameover;

//===================================
//初期化
//===================================
HRESULT InitGameOver()
{
	g_gameover.select_gameover = 0;
	g_gameover.pos.x = 0;
	g_gameover.pos.y = 0;
	g_gameover.Size.x = SCREEN_WIDTH;
	g_gameover.Size.y = SCREEN_HEIGHT;

	g_gameover.texGameOver = LoadTexture(g_TextureGameOver);
	g_gameover.texGameOverBG = LoadTexture(g_TextureGameOverBG);
	PlaySE(SE_BOOING);

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitGameOver()
{
	//全サウンドの停止
	StopSoundAll();	
}


//===================================
//描画
//===================================
void    DrawGameOver()
{
	// GameOver背景
	{
		// テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gameover.texGameOverBG));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_gameover.Size.x, g_gameover.Size.y, 0, g_gameover.BGColor, 0, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}

	// GameOver
	{
		// テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gameover.texGameOver));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT *2/ 5, g_gameover.Size.x*6/7, g_gameover.Size.y/3, 0, g_gameover.Color, 0, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
}


//===================================
//更新
//===================================
void    UpdateGameOver()
{
	if (IsButton(L_RIGHT, TRIGGER))
	{
		if (g_gameover.select_gameover <= 1)
		{
			g_gameover.select_gameover += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_LEFT, TRIGGER))
	{
		if (g_gameover.select_gameover >= 1)
		{
			g_gameover.select_gameover -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		switch (g_gameover.select_gameover)
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

GameOver* GetGameOver()
{
	return &g_gameover;
}
