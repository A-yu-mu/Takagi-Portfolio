#pragma once
//=============================================================================
//camera.h
// 作成者：岸直哉/小林良太　作成日：2022/10/21
// 変更者：舘崎礼音　変更日：2022/10/25
//=============================================================================

#ifndef  CAMERA_H_
#define  CAMERA_H_



#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define CAMERA_SIZE_W (150)
#define	CAMERA_SIZE_H (150)


static	ID3D11ShaderResourceView* g_TextureCamera;//画像1枚で1つの変数が必要
static	char* g_TextureNameCamera = (char*)"data\\texture\\UI_Cam01.png";//テクスチャファイルパス JPG BMP PNG
struct CAMERA
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス

};


//====================================
//プロトタイプ宣言
//====================================
HRESULT    InitCamera();
void    UnInitCamera();
void    DrawCamera();
void    UpdateCamera();
CAMERA* GetCamera();

//カメラパートを開始する関数と終了する関数
void    StartCamera();
void    EndCamera();

//今がカメラパートかどうかを返す関数
bool	NowCameraFlag();

#endif // ! CAMERA_H_