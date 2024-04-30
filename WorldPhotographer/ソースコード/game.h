//=============================================================================
//game.h
// 作成者：岸直哉　作成日：2022/09/05
//=============================================================================

#pragma once



#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================


struct GAME
{
	bool GameUpdateFlag = false;
	bool GameCameraFlag = false;
	int select_game = 0;

	D3DXCOLOR BackTitelColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RetryColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texBackTitel_game;
	float texRetry_game;
	float texBack_game;
};

//====================================
//プロトタイプ宣言
//====================================
HRESULT InitGame();
void    UnInitGame();
void    DrawGame();
void    UpdateGame();

GAME* GetGame(); //GAME構造体の先頭ポインタを取得