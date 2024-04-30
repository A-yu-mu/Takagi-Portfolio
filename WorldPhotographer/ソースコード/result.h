//=============================================================================
//result.h
// 作成者：岸直哉　作成日：2022/11/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================

// タイムリミット表示位置
#define TIMELIMIT_R_POS_X (SCREEN_WIDTH/2)
#define	TIMELIMIT_R_POS_Y (SCREEN_HEIGHT/5)

static	ID3D11ShaderResourceView* g_Textureresult;//画像1枚で1つの変数が必要
static	char* g_TextureResultName = (char*)"data\\texture\\fade_white.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank;//画像1枚で1つの変数が必要
static	char* g_TextureRank = (char*)"data\\texture\\RANK.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_S;//画像1枚で1つの変数が必要
static	char* g_TextureRank_S = (char*)"data\\texture\\UOWs_S.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_A;//画像1枚で1つの変数が必要
static	char* g_TextureRank_A = (char*)"data\\texture\\UOWs_A.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_B;//画像1枚で1つの変数が必要
static	char* g_TextureRank_B = (char*)"data\\texture\\UOWs_B.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Rank_C;//画像1枚で1つの変数が必要
static	char* g_TextureRank_C = (char*)"data\\texture\\UOWs_C.png";//テクスチャファイルパス JPG BMP PNG


struct RESULT
{
	D3DXVECTOR2	Size;	//ポリゴンのサイズ
	D3DXVECTOR2 pos;	//表示座標
	float texno;    //テクスチャインデックス
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texRank;
	float texRank_S;
	float texRank_A;
	float texRank_B;
	float texRank_C;

	int limit_0;
	int limit_rank;
	int select_result = 0;
};

//====================================
//プロトタイプ宣言
//====================================
HRESULT InitResult();
void    UnInitResult();
void    DrawResult();
void    UpdateResult();
RESULT* GetResult(); //RESULT構造体の先頭ポインタを取得



