//=============================================================================
//explosion.h
// 作成者：岸直哉　作成日：2022/07/11
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define EXPLOSION_SIZE_W (80)
#define	EXPLOSION_SIZE_H (40)
#define EXPLOSION_MAX    (10)
#define EXPLOSION_SPEED  (10.0f)
#define EXPLOSION_ANIME_MAX (7)//アニメーション最大数

static	ID3D11ShaderResourceView* g_TexturePlayerJumpEffect;//画像1枚で1つの変数が必要
static	char* g_TextureNamePlayerJumpEffect = (char*)"data\\texture\\player_jump_effect.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_TexturePlayerLandingEffect;//画像1枚で1つの変数が必要
static	char* g_TextureNamePlayerLandingEffect = (char*)"data\\texture\\player_landing_effect.png";//テクスチャファイルパス JPG BMP PNG

struct PLAYER_EFFECT
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
HRESULT InitPlayerEffect();
void    UnInitPlayerEffect();
void    DrawPlayerEffect();
void    UpdatePlayerEffect();
PLAYER_EFFECT* GetPlayerEffect(); //BULLET構造体の先頭ポインタを取得
void SetPlayerJumpEffect(float x, float y, float animeSpeed);
void SetPlayerLandingEffect(float x, float y, float animeSpeed);


