//=============================================================================
// manual.h
// ì¬ÒFûüØà²@ì¬úF2023/01/25
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//}Nè`
//====================================

static	ID3D11ShaderResourceView* g_TextureManualBG;//æ1Å1ÂÌÏªKv
static	char* g_Texture_ManualBG = (char*)"data\\texture\\fade_white.png";//eNX`t@CpX JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualKeyboard;//æ1Å1ÂÌÏªKv
static	char* g_Texture_ManualKeyboard = (char*)"data\\texture\\keyboard_manual.png";//eNX`t@CpX JPG BMP PNG

static	ID3D11ShaderResourceView* g_TextureManualPad;//æ1Å1ÂÌÏªKv
static	char* g_Texture_ManualPad = (char*)"data\\texture\\Pad_manual.png";//eNX`t@CpX JPG BMP PNG


struct MANUAL
{
	int select_manual;
	int temp_select_manual;

	float w, h;     //boxTCY
	float texbg;    //eNX`CfbNX
	float texkeyboard;    //eNX`CfbNX
	float texpad;    //eNX`CfbNX
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ShadowColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);
};
//====================================
//vg^Cvé¾
//====================================
HRESULT InitManual();
void    UnInitManual();
void    DrawManual();
void    UpdateManual();
MANUAL* GetManual(); // MANUAL\¢ÌÌæª|C^ðæ¾



