//=============================================================================
// stage_slect.h
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================

static  ID3D11ShaderResourceView* g_TextureStage1_1;
static  ID3D11ShaderResourceView* g_TextureStage1_2;
static  ID3D11ShaderResourceView* g_TextureStage1_3;
static  ID3D11ShaderResourceView* g_TextureStage2_1;
static  ID3D11ShaderResourceView* g_TextureStage2_2;
static  ID3D11ShaderResourceView* g_TextureStage2_3;
static  ID3D11ShaderResourceView* g_TextureStage3_1;
static  ID3D11ShaderResourceView* g_TextureStage3_2;
static  ID3D11ShaderResourceView* g_TextureStage3_3;
static	ID3D11ShaderResourceView* g_TextureStageSelsectBG;

static	char* g_TextureStageSelectBG = (char*)"data\\texture\\fade_white.png";//テクスチャファイルパス JPG BMP PNG

static	char* g_TexturesStage1_1 = (char*)"data\\texture\\StageSelect\\select_1-1.png";//テクスチャファイルパス JPG BMP PNG
static	char* g_TexturesStage1_2 = (char*)"data\\texture\\StageSelect\\select_1-2.png";
static	char* g_TexturesStage1_3 = (char*)"data\\texture\\StageSelect\\select_1-3.png";
static	char* g_TexturesStage2_1 = (char*)"data\\texture\\StageSelect\\select_2-1.png";
static	char* g_TexturesStage2_2 = (char*)"data\\texture\\StageSelect\\select_2-2.png";
static	char* g_TexturesStage2_3 = (char*)"data\\texture\\StageSelect\\select_2-3.png";
static	char* g_TexturesStage3_1 = (char*)"data\\texture\\StageSelect\\select_3-1.png";
static	char* g_TexturesStage3_2 = (char*)"data\\texture\\StageSelect\\select_3-2.png";
static	char* g_TexturesStage3_3 = (char*)"data\\texture\\StageSelect\\select_3-3.png";

const int STAGE_MAX = 9;
struct STAGE_SELECT
{
	float w, h;     //boxサイズ
	float texno;    //テクスチャインデックス
	D3DXCOLOR Color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	D3DXCOLOR StageListColor = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	D3DXCOLOR TitleBackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	int select;
};
//====================================
//プロトタイプ宣言
//====================================
HRESULT InitStageSelect();
void    UnInitStageSelect();
void    DrawStageSelect();
void    UpdateStageSelect();
STAGE_SELECT* GetStageSelect(); //STAGE_SELECT構造体の先頭ポインタを取得

int GetStageNum();

void DrawStageCamUI();

int GetSelectStageSelect();



