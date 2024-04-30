//=============================================================================
//cursor_A.h
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================


#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define CURSOR_A_SIZE_W (80)
#define	CURSOR_A_SIZE_H (80)

static	ID3D11ShaderResourceView* g_Texture_A;//画像1枚で1つの変数が必要
static	char* g_TextureName_A = (char*)"data\\texture\\fokasu_5.jpeg";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_B;//画像1枚で1つの変数が必要
static	char* g_TextureName_B = (char*)"data\\texture\\haikei.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T1;//画像1枚で1つの変数が必要
static	char* g_TextureName_T1 = (char*)"data\\texture\\1.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T2;//画像1枚で1つの変数が必要
static	char* g_TextureName_T2 = (char*)"data\\texture\\2.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T3;//画像1枚で1つの変数が必要
static	char* g_TextureName_T3 = (char*)"data\\texture\\3.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T4;//画像1枚で1つの変数が必要
static	char* g_TextureName_T4 = (char*)"data\\texture\\4.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_T5;//画像1枚で1つの変数が必要
static	char* g_TextureName_T5 = (char*)"data\\texture\\5.png";//テクスチャファイルパス JPG BMP PNG


struct CURSOR_A
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス

	float texno_B;
	bool camera_use;

	float texno_T1;
	float texno_T2;
	float texno_T3;
	float texno_T4;
	float texno_T5;
	int zoom;

	int a = 10;
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitCursor_A();
void    UnInitCursor_A();
void    DrawCursor_A();
void    UpdateCursor_A();
CURSOR_A* GetCursor_A(); //CURSOR_A構造体の先頭ポインタを取得



