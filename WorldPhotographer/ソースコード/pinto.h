#pragma once

#include "main.h"
#include "renderer.h"

//====================================
//マクロ定義
//====================================

#define PINTO_MOVE_01	(1.0f)		//ピントの一度に動かす量
#define PINTO_MOVE_02	(1.0f)		//ピントの一度に動かす量
#define PINTO_OKLINE	(10.0f)		//ピントがあっている判定にする許容範囲


static	ID3D11ShaderResourceView* g_PintoTexture;//画像1枚で1つの変数が必要
static	char* g_PintoTextureName1 = (char*)"data\\texture\\UI_Focus01.png";//テクスチャファイルパス JPG BMP PNG
static	char* g_PintoTextureName2 = (char*)"data\\texture\\UI_Focus02.png";//テクスチャファイルパス JPG BMP PNG

struct PINTO
{
	bool use;			//構造体利用中フラグ
	float maxpos;		//ピントの最大値
	float nowpos;		//ピントの現在位置
	float change1pos;	//レイヤー１とレイヤー２の切り替わりのピントの位置
	float change2pos;	//レイヤー２とレイヤー３の切り替わりのピントの現在位置
	float texno1;		//テクスチャインデックス
	float texno2;		//テクスチャインデックス


};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitPinto();
void    UnInitPinto();
void    DrawPinto();
void    UpdatePinto();
PINTO*	GetPinto(); //PINTO構造体の先頭ポインタを取得

void    SetLimit(int limit);
