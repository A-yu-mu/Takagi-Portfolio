#pragma once
/*
io_ex
2023/01/18~
舘崎礼音
操作&音声管理
*/

#include "main.h"

#include "inputx.h"		//XINPUT用
#include "keyboard.h"


#include "sound.h"


//ボタンの降下判定の種類
typedef enum 
{
	PUSH = 0,
	TRIGGER,
	RELEASE,

	ACT_MAX
}ACT;

//各ボタンの番号
typedef enum  
{
	L_UP = 0,
	L_DOWN,
	L_LEFT,
	L_RIGHT,
	R_UP,
	R_DOWN,
	R_LEFT,
	R_RIGHT,
	A,
	B,
	X,
	Y,
	L1,
	R1,
	START,

	BUTTON_MAX//ボタンの種類の最大数
}BUTTON_TYPE;


void InitIoEx();
void UpdateIoEx();

//指定したボタンと入力形式に応じてboolを返す
bool IsButton(BUTTON_TYPE type, ACT act);


//音関係
enum BGM_TYPE
{
	BGM_TITLE = 0,
	BGM_STAGESELECT,
	BGM_AREA01,
	BGM_AREA02,
	BGM_AREA03,
	
	BGM_MAX//BGMの最大数
};
enum SE_TYPE
{
	SE_OK = 0,
	SE_MOVECURSOR,
	SE_JUMP,
	SE_JUMPUP,
	SE_DAMAGE,
	SE_GET_KEY,
	SE_USE_KYE,
	SE_SWITCH_ON,
	SE_SWITCH_OFF,
	SE_SHUTTER,
	SE_FANFARE,
	SE_BOOING,
	SE_SHELL,
	SE_AFTERIMAGE_ON,
	SE_AFTERIMAGE_OFF,
	SE_PHOTO_ON,
	SE_PHOTO_OFF,
	SE_LANDING,
	SE_PAUSE_ON,
	SE_PAUSE_OFF,
	SE_SKELETON_DELETE,
	SE_SKELETON_REBORN,
	SE_PINTO,
	SE_TURN,
	SE_PHOTORETI_MOVE,


	SE_MAX//SEの最大数
};


//サウンドの再生
void PlayBGM(BGM_TYPE index);

void PlaySE(SE_TYPE index);

