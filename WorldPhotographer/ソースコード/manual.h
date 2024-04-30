//=============================================================================
// manual.h
// 作成者：髙木歩夢　作成日：2023/01/25
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================

static	ID3D11ShaderResourceView* g_TextureManualBG;//画像1枚で1つの変数が必要
static	char* g_Texture_ManualBG = (char*)"data\\texture\\fade_white.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualKeyboard;//画像1枚で1つの変数が必要
static	char* g_Texture_ManualKeyboard = (char*)"data\\texture\\keyboard_manual.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualPad;//画像1枚で1つの変数が必要
static	char* g_Texture_ManualPad = (char*)"data\\texture\\Pad_manual.png";//テクスチャファイルパス JPG BMP PNG


struct MANUAL
{
	int select_manual;
	int temp_select_manual;

	float w, h;     //boxサイズ
	float texbg;    //テクスチャインデックス
	float texkeyboard;    //テクスチャインデックス
	float texpad;    //テクスチャインデックス
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ShadowColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);
};
//====================================
//プロトタイプ宣言
//====================================
HRESULT InitManual();
void    UnInitManual();
void    DrawManual();
void    UpdateManual();
MANUAL* GetManual(); // MANUAL構造体の先頭ポインタを取得



