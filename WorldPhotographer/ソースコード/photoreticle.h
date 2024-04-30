//=============================================================================
//photoreticle.h
// 作成者：舘崎　作成日：2022/10/22
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//サイズをマップチップのサイズに連動させる
#include "mapchip.h"
//====================================
//マクロ定義
//====================================
#define PHOTORETICLE_SIZE_W (PHOTO_SIZE_W)
#define	PHOTORETICLE_SIZE_H (PHOTO_SIZE_H)

static	ID3D11ShaderResourceView* g_PhotoreticleTexture;//画像1枚で1つの変数が必要
static	char* g_PhotoreticleTextureName = (char*)"data\\texture\\UI_Cam02.png";//テクスチャファイルパス JPG BMP PNG
struct PHOTORETICLE
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス

};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitPhotoreticle();
void    UnInitPhotoreticle();
void    DrawPhotoreticle();
void    UpdatePhotoreticle();
PHOTORETICLE* GetPhotoreticle(); //PHOTORETICLE構造体の先頭ポインタを取得

