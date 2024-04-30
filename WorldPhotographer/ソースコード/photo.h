//=============================================================================
//photo.h
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
#define PHOTO_MAPCHIP_WIDTH_NUM (6)		//写真の横のマップチップの個数
#define PHOTO_MAPCHIP_HEIGHT_NUM (6)		//写真の横のマップチップの個数
#define PHOTO_MAPCHIP_NUM (PHOTO_MAPCHIP_WIDTH_NUM * PHOTO_MAPCHIP_HEIGHT_NUM)			//写真の縦横のマップチップの合計個数

#define PHOTO_SIZE_W (MAPCHIP_WIDTH * PHOTO_MAPCHIP_WIDTH_NUM)
#define	PHOTO_SIZE_H (MAPCHIP_HEIGHT * PHOTO_MAPCHIP_WIDTH_NUM)

static	ID3D11ShaderResourceView* g_PhotoTexture;//画像1枚で1つの変数が必要
static	char* g_PhotoTextureName = (char*)"data\\texture\\TSM.png";//テクスチャファイルパス JPG BMP PNG
struct PHOTO
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 old_pos;//元のレイヤーの表示座標
	D3DXVECTOR2 pos;//現在の表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(0.97f, 0.5f, 0.44f, 1.0f);
	float texno;    //テクスチャインデックス

		//マップチップ情報も持つ
	CHIP chip[PHOTO_MAPCHIP_NUM];		//縦横の合計個数分のチップ情報を持つ

};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitPhoto();
void    UnInitPhoto();
void    DrawPhoto();
void    UpdatePhoto();

//フォトにはストックとプットの二種類があるので
//ゲッターを分ける
PHOTO*	GetPhotoStock(); //PHOTO構造体の先頭ポインタを取得
PHOTO*	GetPhotoPut(); //PHOTO構造体の先頭ポインタを取得

//セッター
void	SetPhotoStock(float w, float h, D3DXVECTOR2 pos, D3DXCOLOR Color, float texno, CHIP* chip);
void	SetPhotoPut(float w, float h, D3DXVECTOR2 old_pos, D3DXCOLOR Color, float texno, D3DXVECTOR2 pos, CHIP* chip);
