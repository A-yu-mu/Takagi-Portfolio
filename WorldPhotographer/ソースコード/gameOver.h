//=============================================================================
// gameOver.h
// 作成者：髙木歩夢　作成日：2022/12/04
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================

static	ID3D11ShaderResourceView* g_Texture_GameOver;//画像1枚で1つの変数が必要
static	ID3D11ShaderResourceView* g_Texture_GameOverBG;//画像1枚で1つの変数が必要

static	char* g_TextureGameOver = (char*)"data\\texture\\game_over.png";//テクスチャファイルパス JPG BMP PNG
static	char* g_TextureGameOverBG = (char*)"data\\texture\\fade_white.png";//テクスチャファイルパス JPG BMP PNG

struct GameOver
{
	D3DXVECTOR2	Size;	//ポリゴンのサイズ
	D3DXVECTOR2 pos;	//表示座標
	float rot;			//回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.6f);
	
	float texGameOver;		//テクスチャインデックス
	float texGameOverBG;	//テクスチャインデックス

	int select_gameover = 0;
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitGameOver();
void    UnInitGameOver();
void    DrawGameOver();
void    UpdateGameOver();

GameOver* GetGameOver();	//GameOver構造体の先頭ポインタを取得

