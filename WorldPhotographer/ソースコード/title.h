//=============================================================================
//enemy.h
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================



struct TITLE
{
	int select_title;

	float w, h;     //boxサイズ
	float texno;    //テクスチャインデックス
	float texlogo;    //テクスチャインデックス
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};
//====================================
//プロトタイプ宣言
//====================================
HRESULT InitTitle();
void    UnInitTitle();
void    DrawTitle();
void    UpdateTitle();
TITLE* GetTitle(); //TITLE構造体の先頭ポインタを取得



