//=============================================================================
//photoeffect.h
// 作成者：有郷 拓海　作成日：2022/11/15
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define PHOTOEFFECT_SIZE_W (280)
#define	PHOTOEFFECT_SIZE_H (280)
#define PHOTOEFFECT_MAX    (10)
#define PHOTOEFFECT_SPEED  (10.0f)
#define PHOTOEFFECT_ANIME_MAX (7)//アニメーション最大数

static	ID3D11ShaderResourceView* g_TexturePhotoEffect;//画像1枚で1つの変数が必要
static	char* g_TextureNamePhotoEffect = (char*)"data\\texture\\PhotoEffect.png";//テクスチャファイルパス JPG BMP PNG
struct PHOTOEFFECT
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス
	float m_animeSpeed;
	float pattern_num_explosion;

};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitPhotoEffect();
void    UnInitPhotoEffect();
void    DrawPhotoEffect();
void    UpdatePhotoEffect();
PHOTOEFFECT* GetPhotoEffect(); //BULLET構造体の先頭ポインタを取得
void SetPhotoEffect(float x, float y,float animeSpeed);


