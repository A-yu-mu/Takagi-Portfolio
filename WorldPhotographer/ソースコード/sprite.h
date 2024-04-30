//*********************************************************
// sprite.h
// 作成者：岸直哉　作成日2022/06/13
//*********************************************************
#pragma once

#include "main.h"

//*********************************************************
//マクロ定義
//*********************************************************




//*********************************************************
//プロトタイプ宣言
//*********************************************************

//static	float	PaternNo = 0;	//パターン番号
//float	uv_w = 0.5f;			//横サイズ
//float	uv_h = 0.5f;			//縦サイズ
//int		NumPatern = 2;			//横枚数

void DrawSpriteColorRotation(float, float, int, int, float, D3DXCOLOR,float PaternNo,float uv_w,float uv_h,int NumPatern);	//三角形用頂点格納処理
void DrawSpritePhoto(float, float, int, int, D3DXCOLOR, D3DXVECTOR2);	//フォトの描画専用処理 by舘崎
void InitSprite(); //スプライト初期化
void UninitSprite();//スプライト終了処理








