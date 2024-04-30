
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd); //�T�E���h�̏�����
void UninitSound(void);    //�T�E���h�̏I��

int LoadSound(char* pFilename);          //�T�E���h�̃��[�h
void PlaySound(int index, int loopCount);//�T�E���h�̍Đ� loopcount 0 = 1��Đ��@loopcount < 0 ���[�v
void StopSound(int index);				 //�T�E���h�̒�~


void StopSoundAll(void);				 //�S�T�E���h�̒�~
void SetVolume(int index, float vol);	 //���ʐݒ�
