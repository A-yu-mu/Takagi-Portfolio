//=============================================================================
//game.cpp
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================
#include <iostream>

#include "game.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "player.h"
#include "player_effect.h"
#include "block.h"
#include "camera.h"
#include "mapchip.h"
#include "mapscroll.h"
#include "playerCamera.h"
#include "Mapcollision.h"
#include "mapchip.h"
#include "mcgimmick.h"

#include "cannon.h"
#include "shell.h"
#include "UI.h"
#include "photoeffect.h"
#include "timelimit.h"
#include "player_afterimage.h"

#include "io_ex.h"
#include "fade.h"

#include "stage_select.h"
#include "layer.h"
#include "polygon.h"


static	ID3D11ShaderResourceView* g_PauseBGTexture;//画像1枚で1つの変数が必要
static	char* g_PauseBGTextureName = (char*)"data\\texture\\fade_white.png";//テクスチャファイルパス JPG BMP PNG

static int g_PauseBGTextureNo = 0;


static	ID3D11ShaderResourceView* g_PauseTexture;//画像1枚で1つの変数が必要
static	char* g_PauseTextureName = (char*)"data\\texture\\pause.png";//テクスチャファイルパス JPG BMP PNG

static int g_PauseTextureNo = 0;



//===================================
//マクロ定義
//===================================


//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================

static GAME g_game;




//===================================
//初期化
//===================================
HRESULT InitGame()
{
	InitCamera();
	g_game.GameUpdateFlag = true;
	g_game.GameCameraFlag = true;
	int st_num = GetStageNum();

	switch (st_num)
	{

	case 0://ステージ1‐1
		InitMapchip("data\\stage\\ステージ1-1\\SMC1_1.txt");
		SetLayerMC_01(LAYER_MC_1_1_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 1://ステージ1‐2
		InitMapchip("data\\stage\\ステージ1-2\\SMC1_2.txt");
		SetLayerMC_01(LAYER_MC_1_2_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 2://ステージ1‐3
		InitMapchip("data\\stage\\ステージ1-3\\SMC1_3.txt");
		SetLayerMC_01(LAYER_MC_1_3_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 3://ステージ2‐1
		InitMapchip("data\\stage\\ステージ2-1\\SMC2_1.txt");
		SetLayerMC_01(LAYER_MC_2_1_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 4://ステージ2‐2
		InitMapchip("data\\stage\\ステージ2-2\\SMC2_2.txt");
		SetLayerMC_01(LAYER_MC_2_2_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 5://ステージ2‐3
		InitMapchip("data\\stage\\ステージ2-3\\SMC2_3.txt");
		SetLayerMC_01(LAYER_MC_2_3_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 6://ステージ3‐1
		InitMapchip("data\\stage\\ステージ3-1\\SMC3_1.txt");
		SetLayerMC_01(LAYER_MC_3_1_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);
		PlayBGM(BGM_AREA03);
		break;
	case 7://ステージ3‐2
		InitMapchip("data\\stage\\ステージ3-2\\SMC3_2.txt");
		SetLayerMC_01(LAYER_MC_3_2_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);

		PlayBGM(BGM_AREA03);
		break;
	case 8://ステージ3‐3
		InitMapchip("data\\stage\\ステージ3-3\\SMC3_3.txt");
		SetLayerMC_01(LAYER_MC_3_3_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);
		PlayBGM(BGM_AREA03);
		break;
	case 9:
		SetScene(SCENE_TITLE);
		break;
	}

	InitPlayer();

	InitPlayerCamera();

	/*InitBlock();*/

	InitPlayerEffect();
	InitCannon();
	InitShell();

	InitTimeLimit();
	InitUI();

	InitPhotoEffect();
	InitAfterImage();

	InitMcGimmick();

	SetCannon(D3DXVECTOR2(700.0f, 388.0f));
	//SetShell(D3DXVECTOR2(300.0f, 300.0f));

	//textureのロード
	g_PauseBGTextureNo = LoadTexture(g_PauseBGTextureName);
	if (g_PauseBGTextureNo == -1)
	{//ロードエラー
		exit(999);//強制終了
	}


	//textureのロード
	g_PauseTextureNo = LoadTexture(g_PauseTextureName);
	if (g_PauseTextureNo == -1)
	{//ロードエラー
		exit(999);//強制終了
	}
	return S_OK;


}

//===================================
//終了
//===================================
void    UnInitGame()
{
	StopSoundAll();

	UninitMapchip();
	//UnInitBlock();

	UnInitPlayer();

	UnInitCamera();
	UnInitTimeLimit();

	UnInitAfterImage();
	UnInitPhotoEffect();
	UnInitPlayerEffect();
}


//===================================
//描画
//===================================
void  DrawGame()
{
	DrawMapchip();

	//カメラパート中はアクションパートの更新、描画処理を行わない
	if (NowCameraFlag() == false)
	{
		g_game.GameCameraFlag = false;
		DrawPhotoEffect();
		DrawPlayer();
		DrawCannon();
		DrawShell();
		/*DrawBlock();*/

		DrawAfterImage();
		DrawPlayerEffect();
	}
	else
	{
		g_game.GameCameraFlag = true;
	}
	DrawCamera();
	DrawTimeLimit();
	DrawUI();

	// ポーズ画面表示
	if (g_game.GameUpdateFlag == false)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PauseBGTextureNo));
		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, D3DXCOLOR(0.0, 0.0, 0.0, 0.3), 0, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PauseTextureNo));
		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, 0, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), 0, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}


}


//===================================
//更新
//===================================
void    UpdateGame()
{
	// ポーズ画面への移行
	if (IsButton(START, TRIGGER))
	{
		if (g_game.GameUpdateFlag == true)
		{
			g_game.select_game = 2;
			g_game.GameUpdateFlag = false;
			PlaySE(SE_PAUSE_ON);
		}
		else if (g_game.GameUpdateFlag == false)
		{
			g_game.GameUpdateFlag = true;
			PlaySE(SE_PAUSE_OFF);
		}
	}

	if (g_game.GameUpdateFlag == true)
	{
		UpdateMapchip();

		UpdatePlayerCamera();

		UpdateCamera();
		//カメラパート中はアクションパートの更新、描画処理を行わない
		if (NowCameraFlag() == false)
		{

			UpdatePlayer();
			UpdateShell();
			UpdateCannon();
			/*UpdateBlock();*/


			UpdateAfterImage();
			UpdatePlayerEffect();
			UpdatePhotoEffect();
		}
		UpdateTimeLimit();
	}
	else if (g_game.GameUpdateFlag == false)
	{
		if (IsButton(L_RIGHT, TRIGGER))
		{
			if (g_game.select_game <= 1)
			{
				g_game.select_game += 1;
			}
			PlaySE(SE_MOVECURSOR);
		}

		if (IsButton(L_LEFT, TRIGGER))
		{
			if (g_game.select_game >= 1)
			{
				g_game.select_game -= 1;
			}
			PlaySE(SE_MOVECURSOR);
		}


		if (IsButton(A, TRIGGER))
		{
			switch (g_game.select_game)
			{
			case 0:
				SetFade(FADE_OUT_TITLE);
				break;

			case 1:
				SetFade(FADE_OUT_GAME);
				break;

			case 2:
				// 戻る
				g_game.GameUpdateFlag = true;
				break;
			}
			PlaySE(SE_OK);
		}
	}

}

GAME* GetGame()
{
	return &g_game;
}