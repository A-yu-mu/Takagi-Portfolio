#pragma once
/*
io_ex
2023/01/18~
�ڍ�特
����&�����Ǘ�
*/

#include "main.h"

#include "inputx.h"		//XINPUT�p
#include "keyboard.h"


#include "sound.h"


//�{�^���̍~������̎��
typedef enum 
{
	PUSH = 0,
	TRIGGER,
	RELEASE,

	ACT_MAX
}ACT;

//�e�{�^���̔ԍ�
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

	BUTTON_MAX//�{�^���̎�ނ̍ő吔
}BUTTON_TYPE;


void InitIoEx();
void UpdateIoEx();

//�w�肵���{�^���Ɠ��͌`���ɉ�����bool��Ԃ�
bool IsButton(BUTTON_TYPE type, ACT act);


//���֌W
enum BGM_TYPE
{
	BGM_TITLE = 0,
	BGM_STAGESELECT,
	BGM_AREA01,
	BGM_AREA02,
	BGM_AREA03,
	
	BGM_MAX//BGM�̍ő吔
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


	SE_MAX//SE�̍ő吔
};


//�T�E���h�̍Đ�
void PlayBGM(BGM_TYPE index);

void PlaySE(SE_TYPE index);

