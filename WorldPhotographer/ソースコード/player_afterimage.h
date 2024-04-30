//=============================================================================
//player.h
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"

//====================================
//マクロ定義
//====================================

//static	ID3D11ShaderResourceView* g_Texture;//画像1枚で1つの変数が必要
//static	char* g_TextureName = (char*)"data\\texture\\player_Idling.png";//テクスチャファイルパス JPG BMP PNG
//
//static	ID3D11ShaderResourceView* g_Texture2;//画像1枚で1つの変数が必要
//static	char* g_TextureName2 = (char*)"data\\texture\\player_walk.png";//テクスチャファイルパス JPG BMP PNG
//
//static	ID3D11ShaderResourceView* g_Texture3;//画像1枚で1つの変数が必要
//static	char* g_TextureName3 = (char*)"data\\texture\\player_jump.png";//テクスチャファイルパス JPG BMP PNG

struct AfterImage
{
	bool use;		//構造体利用中フラグ

	D3DXVECTOR2		size;		//ポリゴンのサイズ			
	D3DXVECTOR2 pos;//表示座標
	D3DXVECTOR2 oldpos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	bool col;

	D3DXVECTOR2 scrpos;

	float ysp;

	float pattern_num;


};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitAfterImage();
void    UnInitAfterImage();
void    DrawAfterImage();
void    UpdateAfterImage();
AfterImage* GetAfterImage(); //PLAYER構造体の先頭ポインタを取得
void AfterImageReset();



