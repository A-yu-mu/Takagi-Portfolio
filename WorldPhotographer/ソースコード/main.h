/*==============================================================================

   共通ヘッダー [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
//#include "inputx.h"
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"World Photographer"			// ウインドウのキャプション名



#define SCREEN_WIDTH	(960)				// ウインドウの幅
#define SCREEN_HEIGHT	(540)				// ウインドウの高さ
typedef enum
{
	SCENE_TITLE = 0,
	SCENE_GAME,
	SCENE_GAMEOVER,
	SCENE_RESULT,
	SCENE_STAGESELECT,
	SCENE_MANUAL,
	SCENE_MAX

}SCENE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void SetScene(SCENE scene);
SCENE GetScene(void);

void SetStageOpen(int stageopen);
int GetStageOpen();
void SetStageLockMode(bool lockmode);
bool GetStageLockMode();


