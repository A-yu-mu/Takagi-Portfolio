//=============================================================================
//cannon.h
// ì¬ÒFûü´[C@ì¬úF2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//}Nè`
//====================================
#define CANNON_SIZE_W (168)
#define	CANNON_SIZE_H (64)
#define CANNON_MAX (10)
static	ID3D11ShaderResourceView* g_TextureCannon;//æ1Å1ÂÌÏªKv
static	char* g_TextureCannonName = (char*)"data\\texture\\cannon.png";//eNX`t@CpX JPG BMP PNG
struct CANNON
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
};


//====================================
//vg^Cvé¾
//====================================
HRESULT InitCannon();
void    UnInitCannon();
void    DrawCannon();
void    UpdateCannon();
CANNON* GetCannon(); //CANNON\¢ÌÌæª|C^ðæ¾
void	SetCannon(D3DXVECTOR2 pos);