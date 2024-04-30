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
#define PLAYER_SIZE_W (60)
#define	PLAYER_SIZE_H (60)
#define FRAME_RATE (60)	// フレームレート
const int TEX_MAX = 4;

static	ID3D11ShaderResourceView* g_Texture;//画像1枚で1つの変数が必要
static	char* g_TextureName = (char*)"data\\texture\\player_Idling.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture2;//画像1枚で1つの変数が必要
static	char* g_TextureName2 = (char*)"data\\texture\\player_walk.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture3;//画像1枚で1つの変数が必要
static	char* g_TextureName3 = (char*)"data\\texture\\player_jump.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture4;//画像1枚で1つの変数が必要
static	char* g_TextureName4 = (char*)"data\\texture\\player_mode.png";//テクスチャファイルパス JPG BMP PNG


struct PLAYER
{
	D3DXVECTOR2		size;		//ポリゴンのサイズ			
	//float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	D3DXVECTOR2 oldpos;//更新前座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno[TEX_MAX];    //テクスチャインデックス
	float pattern_num;

	int texSelect;

	float move;
	float player_ysp;
	int life = 0;			//プレイヤーのライフポイント
	int count;

	bool use;		//構造体利用中フラグ

	int texLorR;


	bool isDamage;
	bool invincible;
	bool DeathFlag;			//プレイヤーが死んだときにtrueにする死亡フラグ

	bool controlrock;
	bool PressRight;
	bool PressLeft;

	//プレイヤーの状態使用フラグ
	bool PlayerWalk;	//歩き
	bool PlayerCamera;	//カメラモード移行中
	bool PlayerGoal;	//ゴール時のモーション

	bool PlayerJumpEffect;		//ジャンプエフェクト使用フラグ
	bool PlayerLandingEffect;	//着地エフェクト使用フラグ

	bool keyuse;
	bool keyuse_next;//消す予定かどうかのフラグ(作り方きもくてゴメン！)
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitPlayer();
void    UnInitPlayer();
void    DrawPlayer();
void    UpdatePlayer();
PLAYER* GetPlayer(); //PLAYER構造体の先頭ポインタを取得
void SetaNum(int num);

int		GerLR();		//プレイヤーの向いてる方向を返す

