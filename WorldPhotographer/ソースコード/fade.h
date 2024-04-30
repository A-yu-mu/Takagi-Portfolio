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
	D3DXVECTOR3 Position; //表示座標
	D3DXCOLOR   Color;    //表示色
	float       Rotation; //角度
	D3DXVECTOR2 size;	  //ポリゴンのサイズ
}FADE;

HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void SetFade(FADE_STATUS status);

//現在のフェードの状態を返す
FADE_STATUS GetFadeStatus();

#endif // !_FADE_H_
