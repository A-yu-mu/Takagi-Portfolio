#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "renderer.h"

typedef enum{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT_NORMAL,
	FADE_OUT_CAMERA,
	FADE_OUT_TITLE,
	FADE_OUT_STAGESELECT,
	FADE_OUT_GAME,
	FADE_OUT_GAMEOVER,
	FADE_OUT_RESULT,
	FADE_MAX
}FADE_STATUS;

typedef struct
{
	D3DXVECTOR3 Position; //�\�����W
	D3DXCOLOR   Color;    //�\���F
	float       Rotation; //�p�x
	D3DXVECTOR2 size;	  //�|���S���̃T�C�Y
}FADE;

HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void SetFade(FADE_STATUS status);

//���݂̃t�F�[�h�̏�Ԃ�Ԃ�
FADE_STATUS GetFadeStatus();

#endif // !_FADE_H_
