//=============================================================================
//game.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/09/05
//=============================================================================

#pragma once



#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================


struct GAME
{
	bool GameUpdateFlag = false;
	bool GameCameraFlag = false;
	int select_game = 0;

	D3DXCOLOR BackTitelColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RetryColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackColor_game = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texBackTitel_game;
	float texRetry_game;
	float texBack_game;
};

//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitGame();
void    UnInitGame();
void    DrawGame();
void    UpdateGame();

GAME* GetGame(); //GAME�\���̂̐擪�|�C���^���擾