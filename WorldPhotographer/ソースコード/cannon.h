//=============================================================================
//cannon.h
// 作成者：髙橋啓佑　作成日：2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define CANNON_SIZE_W (168)
#define	CANNON_SIZE_H (64)
#define CANNON_MAX (10)
static	ID3D11ShaderResourceView* g_TextureCannon;//画像1枚で1つの変数が必要
static	char* g_TextureCannonName = (char*)"data\\texture\\cannon.png";//テクスチャファイルパス JPG BMP PNG
struct CANNON
{
	bool use;		//構造体利用中フラグ

	D3DXVECTOR2		size;		//ポリゴンのサイズ			
	//float w, h;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	float rot;      //回転角度
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //テクスチャインデックス
	//bool hitCollision;
	//bool upCollision;
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitCannon();
void    UnInitCannon();
void    DrawCannon();
void    UpdateCannon();
CANNON* GetCannon(); //CANNON構造体の先頭ポインタを取得
void	SetCannon(D3DXVECTOR2 pos);