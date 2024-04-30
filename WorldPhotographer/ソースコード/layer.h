//=============================================================================
//layer.h
// 作成者：舘崎　作成日：2022/10/22
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"

#include "mapchip.h"
//====================================
//マクロ定義
//====================================
#define LAYER_MAX (3)					//レイヤーの最大枚数

#define LAYER_SIZE_W (SCREEN_WIDTH)		//レイヤーの横幅
#define	LAYER_SIZE_H (SCREEN_HEIGHT)	//レイヤーの縦幅

#define	LAYER_CHIP_NUM_HEIGHT (SCREEN_HEIGHT / MAPCHIP_HEIGHT)	//レイヤーの縦のチップ数 18
#define	LAYER_CHIP_NUM_WIDTH (SCREEN_WIDTH / MAPCHIP_WIDTH)	//レイヤーの横のチップ数 32

//====================================
//マクロ定義(レイヤーの背景とマップチップの定義)
//====================================
#define LAYER_BG_01_00 ((char*)"data\\texture\\World1\\BG_Forest_Sky.png")	//背景データ(一番後ろの空)			
#define LAYER_BG_01_01 ((char*)"data\\texture\\World1\\BG_Forest_Forward.png")	//背景データ（レイヤー１）		
#define LAYER_BG_01_02 ((char*)"data\\texture\\World1\\BG_Forest_Middle.png")	//背景データ（レイヤー２）
#define LAYER_BG_01_03 ((char*)"data\\texture\\World1\\BG_Forest_Behind.png")	//背景データ（レイヤー３）

#define LAYER_BG_02_00 ((char*)"data\\texture\\World2\\BG_Desert_Sky.png")	//背景データ(一番後ろの空)				
#define LAYER_BG_02_01 ((char*)"data\\texture\\World2\\BG_Desert_Forward.png")	//背景データ（レイヤー１）			
#define LAYER_BG_02_02 ((char*)"data\\texture\\World2\\BG_Desert_Middle.png")	//背景データ（レイヤー２）
#define LAYER_BG_02_03 ((char*)"data\\texture\\World2\\BG_Desert_Behind.png")	//背景データ（レイヤー３）

#define LAYER_BG_03_00 ((char*)"data\\texture\\World3\\BG_Snow_Sky.png")	//背景データ(一番後ろの空)				
#define LAYER_BG_03_01 ((char*)"data\\texture\\World3\\BG_Snow_Forward.png")	//背景データ（レイヤー１）		
#define LAYER_BG_03_02 ((char*)"data\\texture\\World3\\BG_Snow_Middle.png")	//背景データ（レイヤー２）
#define LAYER_BG_03_03 ((char*)"data\\texture\\World3\\BG_Snow_Behind.png")	//背景データ（レイヤー３）



static	ID3D11ShaderResourceView* g_LayerTexture;//画像1枚で1つの変数が必要
static	char* g_LayerTextureName0 = LAYER_BG_01_00;//テクスチャファイルパス JPG BMP PNG
static	char* g_LayerTextureName1 = LAYER_BG_01_01;//テクスチャファイルパス JPG BMP PNG
static	char* g_LayerTextureName2 = LAYER_BG_01_02;//テクスチャファイルパス JPG BMP PNG
static	char* g_LayerTextureName3 = LAYER_BG_01_03;//テクスチャファイルパス JPG BMP PNG



//=============================================
//一般カメラのレイヤー
//=============================================
#define LAYER_MC_1_1_01 ((char*)"data\\stage\\ステージ1-1\\CMC1_1_1.txt")	//レイヤーデータ
#define LAYER_MC_1_1_02 ((char*)"data\\stage\\ステージ1-1\\CMC1_1_2.txt")	
#define LAYER_MC_1_1_03 ((char*)"data\\stage\\ステージ1-1\\CMC1_1_3.txt")	

#define LAYER_MC_1_2_01 ((char*)"data\\stage\\ステージ1-2\\CMC1_2_1.txt")	
#define LAYER_MC_1_2_02 ((char*)"data\\stage\\ステージ1-2\\CMC1_2_2.txt")	
#define LAYER_MC_1_2_03 ((char*)"data\\stage\\ステージ1-2\\CMC1_2_3.txt")	

#define LAYER_MC_1_3_01 ((char*)"data\\stage\\ステージ1-3\\CMC1_3_1.txt")	
#define LAYER_MC_1_3_02 ((char*)"data\\stage\\ステージ1-3\\CMC1_3_2.txt")	
#define LAYER_MC_1_3_03 ((char*)"data\\stage\\ステージ1-3\\CMC1_3_3.txt")	

#define LAYER_MC_2_1_01 ((char*)"data\\stage\\ステージ2-1\\CMC2_1_1.txt")	
#define LAYER_MC_2_1_02 ((char*)"data\\stage\\ステージ2-1\\CMC2_1_2.txt")	
#define LAYER_MC_2_1_03 ((char*)"data\\stage\\ステージ2-1\\CMC2_1_3.txt")

#define LAYER_MC_2_2_01 ((char*)"data\\stage\\ステージ2-2\\CMC2_2_1.txt")	
#define LAYER_MC_2_2_02 ((char*)"data\\stage\\ステージ2-2\\CMC2_2_2.txt")	
#define LAYER_MC_2_2_03 ((char*)"data\\stage\\ステージ2-2\\CMC2_2_3.txt")	

#define LAYER_MC_2_3_01 ((char*)"data\\stage\\ステージ2-3\\CMC2_3_1.txt")	
#define LAYER_MC_2_3_02 ((char*)"data\\stage\\ステージ2-3\\CMC2_3_2.txt")	
#define LAYER_MC_2_3_03 ((char*)"data\\stage\\ステージ2-3\\CMC2_3_3.txt")	

#define LAYER_MC_3_1_01 ((char*)"data\\stage\\ステージ3-1\\CMC3_1_1.txt")	
#define LAYER_MC_3_1_02 ((char*)"data\\stage\\ステージ3-1\\CMC3_1_2.txt")	
#define LAYER_MC_3_1_03 ((char*)"data\\stage\\ステージ3-1\\CMC3_1_3.txt")	

#define LAYER_MC_3_2_01 ((char*)"data\\stage\\ステージ3-2\\CMC3_2_1.txt")	
#define LAYER_MC_3_2_02 ((char*)"data\\stage\\ステージ3-2\\CMC3_2_2.txt")	
#define LAYER_MC_3_2_03 ((char*)"data\\stage\\ステージ3-2\\CMC3_2_3.txt")	

#define LAYER_MC_3_3_01 ((char*)"data\\stage\\ステージ3-3\\CMC3_3_1.txt")	
#define LAYER_MC_3_3_02 ((char*)"data\\stage\\ステージ3-3\\CMC3_3_2.txt")	
#define LAYER_MC_3_3_03 ((char*)"data\\stage\\ステージ3-3\\CMC3_3_3.txt")	

//=============================================
//固定カメラのレイヤー
//=============================================

#define K_LAYER_MC_1_1_01 ((char*)"data\\stage\\ステージ1-1\\KMC1_1_1_1.txt")	//レイヤーデータ
#define K_LAYER_MC_1_1_02 ((char*)"data\\stage\\ステージ1-1\\KMC1_1_2_1.txt")	

#define K_LAYER_MC_1_2_01 ((char*)"data\\stage\\ステージ1-2\\KMC1_2_1_1.txt")	
#define K_LAYER_MC_1_2_02 ((char*)"data\\stage\\ステージ1-2\\KMC1_2_2_1.txt")	


#define K_LAYER_MC_1_3_01 ((char*)"data\\stage\\ステージ1-3\\KMC1_3_1_1.txt")	
#define K_LAYER_MC_1_3_02 ((char*)"data\\stage\\ステージ1-3\\KMC1_3_2_1.txt")	


#define K_LAYER_MC_2_1_01 ((char*)"data\\stage\\ステージ2-1\\KMC2_1_1_1.txt")	
#define K_LAYER_MC_2_1_02 ((char*)"data\\stage\\ステージ2-1\\KMC2_1_1_2.txt")	
#define K_LAYER_MC_2_1_03 ((char*)"data\\stage\\ステージ2-1\\KMC2_1_2_1.txt")	
#define K_LAYER_MC_2_1_04 ((char*)"data\\stage\\ステージ2-1\\KMC2_1_2_2.txt")	


#define K_LAYER_MC_2_2_01 ((char*)"data\\stage\\ステージ2-2\\KMC2_2_1_1.txt")	
#define K_LAYER_MC_2_2_02 ((char*)"data\\stage\\ステージ2-2\\KMC2_2_1_2.txt")	
#define K_LAYER_MC_2_2_03 ((char*)"data\\stage\\ステージ2-2\\KMC2_2_2_1.txt")	
#define K_LAYER_MC_2_2_04 ((char*)"data\\stage\\ステージ2-2\\KMC2_2_2_2.txt")	

#define K_LAYER_MC_2_3_01 ((char*)"data\\stage\\ステージ2-3\\KMC2_3_1_1.txt")	
#define K_LAYER_MC_2_3_02 ((char*)"data\\stage\\ステージ2-3\\KMC2_3_1_2.txt")	
#define K_LAYER_MC_2_3_03 ((char*)"data\\stage\\ステージ2-3\\KMC2_3_2_1.txt")
#define K_LAYER_MC_2_3_04 ((char*)"data\\stage\\ステージ2-3\\KMC2_3_2_2.txt")	

#define K_LAYER_MC_3_1_01 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_1_1.txt")	
#define K_LAYER_MC_3_1_02 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_1_2.txt")	
#define K_LAYER_MC_3_1_03 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_1_3.txt")
#define K_LAYER_MC_3_1_04 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_2_1.txt")	
#define K_LAYER_MC_3_1_05 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_2_2.txt")	
#define K_LAYER_MC_3_1_06 ((char*)"data\\stage\\ステージ3-1\\KMC3_1_2_3.txt")	

#define K_LAYER_MC_3_2_01 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_1_1.txt")	
#define K_LAYER_MC_3_2_02 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_1_2.txt")	
#define K_LAYER_MC_3_2_03 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_1_3.txt")
#define K_LAYER_MC_3_2_04 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_2_1.txt")	
#define K_LAYER_MC_3_2_05 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_2_2.txt")	
#define K_LAYER_MC_3_2_06 ((char*)"data\\stage\\ステージ3-2\\KMC3_2_2_3.txt")	

#define K_LAYER_MC_3_3_01 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_1_1.txt")	
#define K_LAYER_MC_3_3_02 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_1_2.txt")	
#define K_LAYER_MC_3_3_03 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_1_3.txt")
#define K_LAYER_MC_3_3_04 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_2_1.txt")	
#define K_LAYER_MC_3_3_05 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_2_2.txt")	
#define K_LAYER_MC_3_3_06 ((char*)"data\\stage\\ステージ3-3\\KMC3_3_2_3.txt")	




static	char* g_LayerMapchipName1 = LAYER_MC_1_1_01;//テクスチャファイルパス JPG BMP PNG
static	char* g_LayerMapchipName2 = LAYER_MC_1_1_01;//テクスチャファイルパス JPG BMP PNG
static	char* g_LayerMapchipName3 = LAYER_MC_1_1_01;//テクスチャファイルパス JPG BMP PNG

struct LAYER
{
	bool use;		//構造体利用中フラグ
	float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
	float texno;    //テクスチャインデックス

	//マップチップ情報も持つ
	CHIP chip[NUM_CHIP_ALL];
	int mapChipList[LAYER_CHIP_NUM_HEIGHT][LAYER_CHIP_NUM_WIDTH];
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitLayer();
void    UnInitLayer();
void    DrawLayer();
void    UpdateLayer();
LAYER* GetLayer(); //LAYER構造体の先頭ポインタを取得
bool	GetLayerCanGet();//現在が写真を撮れるかどうかを返す

void	SetLayerBGMC(char* name0, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6);
void	SetLayerBG(char* name0, char* name1, char* name2, char* name3);

void	SetLayerMC_01(char* name1);
void	SetLayerMC_02(char* name1, char* name2);
void	SetLayerMC_03(char* name1, char* name2, char* name3);

//マップチップ9番のスクロールストップのタイミングで
//レイヤーを切り替える関数
//一般レイヤー→固定レイヤー
void	SetLayerNextMC09();

//マップチップ10番のスクロールストップ解除のタイミングで
//レイヤーを切り替える関数
//固定レイヤー→一般レイヤー
void	SetLayerNextMC10();

