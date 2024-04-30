//=============================================================================
//shell.h
// ì¬ÒFûü´[C@ì¬úF2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//}Nè`
//====================================
#define SHELL_SIZE_W (25)
#define	SHELL_SIZE_H (25)
#define SHELL_MAX (100)
static	ID3D11ShaderResourceView* g_TextureShell;//æ1Å1ÂÌÏªKv
static	char* g_TextureShellName = (char*)"data\\texture\\shell.png";//eNX`t@CpX JPG BMP PNG
struct SHELL
{
	bool use;		//\¢ÌptO

	D3DXVECTOR2		size;		//|SÌTCY			
	//float w, h;     //boxTCY
	D3DXVECTOR2 pos;//\¦ÀW
	float rot;      //ñ]px
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //eNX`CfbNX
	//bool hitCollision;
	//bool upCollision;
	D3DXVECTOR2 spd;//Ú®¬x
	float time;		//­¶µÄ©çÌÔ
};


//====================================
//vg^Cvé¾
//====================================
HRESULT InitShell();
void    UnInitShell();
void    DrawShell();
void    UpdateShell();
SHELL* GetShell(); //SHELL\¢ÌÌæª|C^ðæ¾
void	SetShell(D3DXVECTOR2 pos, int puramai);

bool	CountShell(int chipnum);
