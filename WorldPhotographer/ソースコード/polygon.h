/*==============================================================================

   ���_�Ǘ�[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BG_01 ((char*)"data\\texture\\World1\\BG_Forest_All.png")	//�w�i�f�[�^			
#define BG_02 ((char*)"data\\texture\\World2\\BG_Desert_All.png")				
#define BG_03 ((char*)"data\\texture\\World3\\BG_Snow_All.png")				


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

void SetBGTexture(char* name);
