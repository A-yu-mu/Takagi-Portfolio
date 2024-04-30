//=============================================================================
//shell.h
// 作成者：髙橋啓佑　作成日：2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define SHELL_SIZE_W (25)
#define	SHELL_SIZE_H (25)
#define SHELL_MAX (100)
static	ID3D11ShaderResourceView* g_TextureShell;//画像1枚で1つの変数が必要
static	char* g_TextureShellName = (char*)"data\\texture\\shell.png";//テクスチャファイルパス JPG BMP PNG
struct SHELL
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
	D3DXVECTOR2 spd;//移動速度
	float time;		//発生してからの時間
};


//====================================
//プロトタイプ宣言
//====================================
HRESULT InitShell();
void    UnInitShell();
void    DrawShell();
void    UpdateShell();
SHELL* GetShell(); //SHELL構造体の先頭ポインタを取得
void	SetShell(D3DXVECTOR2 pos, int puramai);

bool	CountShell(int chipnum);
