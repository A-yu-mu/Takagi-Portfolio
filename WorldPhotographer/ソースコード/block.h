//=============================================================================
//block.h
// 作成者：岸直哉/小林良太　作成日：2022/10/21
//=============================================================================

#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include "renderer.h"
//====================================
//マクロ定義
//====================================
#define BLOCK_MAX 10
static	ID3D11ShaderResourceView* g_TextureBlock;//画像1枚で1つの変数が必要
static	char* g_TextureNameBlock = (char*)"data\\texture\\GrassBlock.jpg";//テクスチャファイルパス JPG BMP PNG
//====================================
//構造体
//====================================

struct BLOCK
{
	bool use;		//構造体利用中フラグ
	D3DXVECTOR2 size;     //boxサイズ
	D3DXVECTOR2 pos;//表示座標
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;

};



//====================================
//プロトタイプ宣言
//====================================
HRESULT   InitBlock();
void    UnInitBlock();
void    DrawBlock();
void    UpdateBlock();

void SetBlock(float x, float y, float px, float py);
BLOCK* GetBlock();



#endif // !BLOCK_H_
