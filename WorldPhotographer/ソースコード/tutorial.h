#pragma once
//=============================================================================
// tutorial.h
// 作成者：髙木歩夢　作成日：2023/01/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================


static	ID3D11ShaderResourceView* g_Texture_Tutorial_01_01;//画像1枚で1つの変数が必要
static	char* g_TextureTutorial_01_01 = (char*)"data\\texture\\tutorial_01_01.png";//テクスチャファイルパス JPG BMP PNG


struct TUTORIAL
{
	bool use;		//構造体利用中フラグ

	D3DXVECTOR2		Size;		//ポリゴンのサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texlife;    //テクスチャインデックス
	float textutorial_01_01;
};

//====================================
//プロトタイプ宣言
//====================================
HRESULT InitTutorial();
void    UnInitTutorial();
void    DrawTutorial();
void    UpdateTutorial();