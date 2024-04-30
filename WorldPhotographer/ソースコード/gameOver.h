//=============================================================================
// gameOver.h
// ì¬ÒFûüØà²@ì¬úF2022/12/04
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//}Nè`
//====================================

static	ID3D11ShaderResourceView* g_Texture_GameOver;//æ1Å1ÂÌÏªKv
static	ID3D11ShaderResourceView* g_Texture_GameOverBG;//æ1Å1ÂÌÏªKv

static	char* g_TextureGameOver = (char*)"data\\texture\\game_over.png";//eNX`t@CpX JPG BMP PNG
static	char* g_TextureGameOverBG = (char*)"data\\texture\\fade_white.png";//eNX`t@CpX JPG BMP PNG

struct GameOver
{
	D3DXVECTOR2	Size;	//|SÌTCY
	D3DXVECTOR2 pos;	//\¦ÀW
	float rot;			//ñ]px
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.6f);
	
	float texGameOver;		//eNX`CfbNX
	float texGameOverBG;	//eNX`CfbNX

	int select_gameover = 0;
};


//====================================
//vg^Cvé¾
//====================================
HRESULT InitGameOver();
void    UnInitGameOver();
void    DrawGameOver();
void    UpdateGameOver();

GameOver* GetGameOver();	//GameOver\¢ÌÌæª|C^ðæ¾

