

#include "main.h"
#pragma once



struct PLAYERCAMERA
{
	D3DXVECTOR2 pos;//ï\é¶ç¿ïW
	D3DXVECTOR2 oldpos;
	D3DXVECTOR2 range;
	float ysp;

	bool scrollmoveRight;
	bool scrollmoveLeft;

	bool scrollLock;
};

HRESULT InitPlayerCamera();
void UpdatePlayerCamera();


D3DXVECTOR2 ScreenPos(D3DXVECTOR2 pos);
D3DXVECTOR2 OldScreenPos(D3DXVECTOR2 pos);
PLAYERCAMERA* GetPlayerCamera();

void ScrollStop(int i);
void ScrollStopLift(int i);

void ScrollStopGoal(int j);
