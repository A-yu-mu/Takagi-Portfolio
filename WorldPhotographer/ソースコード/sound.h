
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd); //サウンドの初期化
void UninitSound(void);    //サウンドの終了

int LoadSound(char* pFilename);          //サウンドのロード
void PlaySound(int index, int loopCount);//サウンドの再生 loopcount 0 = 1回再生　loopcount < 0 ループ
void StopSound(int index);				 //サウンドの停止


void StopSoundAll(void);				 //全サウンドの停止
void SetVolume(int index, float vol);	 //音量設定
