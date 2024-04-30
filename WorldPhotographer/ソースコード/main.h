/*==============================================================================

   ���ʃw�b�_�[ [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
//#include "inputx.h"
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"World Photographer"			// �E�C���h�E�̃L���v�V������



#define SCREEN_WIDTH	(960)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(540)				// �E�C���h�E�̍���
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
// �v���g�^�C�v�錾
//*****************************************************************************

void SetScene(SCENE scene);
SCENE GetScene(void);

void SetStageOpen(int stageopen);
int GetStageOpen();
void SetStageLockMode(bool lockmode);
bool GetStageLockMode();


