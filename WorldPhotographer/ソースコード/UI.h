//=============================================================================
// UI.h
// 作成者：髙木歩夢　作成日：2022/11/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================

#define LIFE_POS_X (80)
#define	LIFE_POS_Y (480)

#define LIFE_SIZE_W (60)
#define	LIFE_SIZE_H (60)

#define TUTORIAL_POS_X (SCREEN_WIDTH * 5/ 6)
#define	TUTORIAL_POS_Y (SCREEN_HEIGHT * 2/7 )

#define TUTORIAL_SIZE_W (SCREEN_WIDTH / 4)
#define	TUTORIAL_SIZE_H (SCREEN_HEIGHT / 3)

#define STAGELOCK_SIZE_W (SCREEN_WIDTH /  5)
#define	STAGELOCK_SIZE_H (SCREEN_HEIGHT / 3)

static	ID3D11ShaderResourceView* g_Texture_Life;//画像1枚で1つの変数が必要
static	char* g_TextureLife = (char*)"data\\texture\\UI_Heart02_64_01-sheet.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_MoveToStageSelection;//画	変数が必要
static	char* g_TextureMoveToStageSelection = (char*)"data\\texture\\move_stage_selection.PNG";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Manual;//画像1枚で1つの変数が必要
static	char* g_TextureManual = (char*)"data\\texture\\manual.PNG";//テクスチャファイルパス JPG BMP PNG


static	ID3D11ShaderResourceView* g_Texture_BackTitel;//画像1枚で1つの変数が必要
static	char* g_TextureBackTitel = (char*)"data\\texture\\back_titel.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Retry;//画像1枚で1つの変数が必要
static	char* g_TextureRetry = (char*)"data\\texture\\retry.PNG";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Back;//画像1枚で1つの変数が必要
static	char* g_TextureBack = (char*)"data\\texture\\back.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_OperateManual;//画像1枚で1つの変数が必要
static	char* g_TextureOperateManual = (char*)"data\\texture\\game_sousa.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_CameraManual;//画像1枚で1つの変数が必要
static	char* g_TextureCameraManual = (char*)"data\\texture\\camera_sousa.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_PauseBottom;//画像1枚で1つの変数が必要
static	char* g_TextureArrowUI = (char*)"data\\texture\\select_arrow.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Arrow;//画像1枚で1つの変数が必要
static	char* g_TexturePauseGameButtom = (char*)"data\\texture\\game_pause.png";//テクスチャファイルパス JPG BMP PNG

// ステージセレクト画面
static	ID3D11ShaderResourceView* g_Texture_StageSelection;//画像1枚で1つの変数が必要
static	char* g_TextureStageSelection = (char*)"data\\texture\\stage_select.png";//テクスチャファイルパス JPG BMP PNG// ステージセレクト画面
// ステージロック
static	ID3D11ShaderResourceView* g_Texture_StageLock;//画像1枚で1つの変数が必要
static	char* g_TextureStageLock = (char*)"data\\texture\\stage_lock.png";//テクスチャファイルパス JPG BMP PNG

// チュートリアル表示
// 左右移動・ジャンプ
static	ID3D11ShaderResourceView* g_Texture_Tutorial1;
static	char* g_TextureTutorial1 = (char*)"data\\texture\\tutorial_player_operate.png";
// カメラピント調整・撮影位置調整・写真撮影
static	ID3D11ShaderResourceView* g_Texture_Tutorial2;
static	char* g_TextureTutorial2 = (char*)"data\\texture\\tutorial_camera.png";

// プレイヤー焼き付け
static	ID3D11ShaderResourceView* g_Texture_Tutorial3;
static	char* g_TextureTutorial3 = (char*)"data\\texture\\tutorial_3_player_burn.png";

// カメラ起動
static	ID3D11ShaderResourceView* g_Texture_Tutorial4;
static	char* g_TextureTutorial4 = (char*)"data\\texture\\tutorial_4_launch_camera.png";


struct UI
{
	bool use;		//構造体利用中フラグ
	bool pushpause;	// ポーズ画面にするやつ

	D3DXVECTOR2		Size;		//ポリゴンのサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	float texlife;    //テクスチャインデックス
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// タイトル・リザルト・ポーズ・ゲームオーバー 類
	D3DXCOLOR TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ManualColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texManual;
	float texMoveToStageSelection;
	float texBackTitel;
	float texRetry;
	float texBack;
	float texOperateManual;
	float texCameraManual;
	float texPauseButtom;
	float texArrow;
	float texStageSelection;
	float texStageLock;

	float texTutorial1;
	float texTutorial2;
	float texTutorial3;
	float texTutorial4;
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitUI();
void    UnInitUI();
void    DrawUI();
void    UpdateUI();



