//=============================================================================
//pinto.cpp
// 作成者：舘崎　作成日：2022/11/08
//=============================================================================

#include "pinto.h"

#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
//===================================
//マクロ定義
//===================================

#define PRESS_TIME_MAX	(1)	//ピントをおしっぱにしたときに何フレーム後に動くか用

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================
static PINTO g_pinto;

int			g_press;	//ボタンをおしっぱかどうかの変数

int			g_limit;	//レイヤーの制限の表示数

//===================================
//初期化
//===================================
HRESULT InitPinto()
{
	g_pinto.use = true;

	g_pinto.maxpos = 600.0f;
	g_pinto.nowpos = 0.0f;

	g_pinto.change1pos = 200.0f;
	g_pinto.change2pos = 400.0f;

	g_pinto.texno1 = LoadTexture(g_PintoTextureName1);
	g_pinto.texno2 = LoadTexture(g_PintoTextureName2);

	g_press = 0;
	g_limit = 3;

	return S_OK;
}


//===================================
//終了
//===================================
void    UnInitPinto()
{

}


//===================================
//描画
//===================================
void    DrawPinto()
{
	//デバッグように各ピント構造体の要素を画面に出しておく
	//ピント表示
	if (g_pinto.use == true)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_pinto.texno1));

		//スプライト表示
		DrawSpriteColorRotation(
			SCREEN_WIDTH / 2, SCREEN_HEIGHT - 26.0f,//xy
			960.0f / 2.0f, 57.0f / 2.0f,//wh
			0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//rotcol
			1, 1, 1, 1);//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

		//レイヤー枚数によって計算を変える
		float max = 0.0f;
		switch (g_limit)
		{
		case 1: max = g_pinto.change1pos; break;
		case 2: max = g_pinto.change2pos; break;
		case 3: max = g_pinto.maxpos; break;

		}
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_pinto.texno2));

		
		//スプライト表示
		DrawSpriteColorRotation(
			(g_pinto.nowpos / max * 900.0f / 2.0f) + SCREEN_WIDTH / 4.0f + 15.0f, 
			SCREEN_HEIGHT - 48.0f,//xy
			24.0f / 2.0f, 27.0f / 2.0f,//wh
			0.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),//rotcol
			1, 1, 1, 1);//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

		
		

	}


}


//===================================
//更新
//===================================
void    UpdatePinto()
{
	//ピントの動かす処理
	//キーボードの入力
	/*if (IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		g_pinto.nowpos -= PINTO_MOVE_01;
	}
	else if (IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		g_pinto.nowpos += PINTO_MOVE_01;
	}*/

	//ボタンをしばらくおしっぱならずっと動かす
	if (IsButton(R_LEFT, PUSH))
	{
		g_press++;
		if (g_press >= PRESS_TIME_MAX)
		{
			g_pinto.nowpos -= PINTO_MOVE_02;
			if ((int)g_pinto.nowpos % 10)//音
			{
				PlaySE(SE_PINTO);
			}
		}
	}
	else if (IsButton(R_RIGHT, PUSH))
	{
		g_press++;
		if (g_press >= PRESS_TIME_MAX)
		{
			g_pinto.nowpos += PINTO_MOVE_02;
			if ((int)g_pinto.nowpos % 10)//音
			{
				PlaySE(SE_PINTO);
			}
		}
	}
	else
	{
		g_press = 0;
	}

	int max;
	switch (g_limit)
	{
	case 1: max = g_pinto.change1pos; break;
	case 2: max = g_pinto.change2pos; break;
	case 3: max = g_pinto.maxpos; break;
	
	}

	//ピントの位置が最大値、最小値を超えたら戻す
	if (g_pinto.nowpos > max)
	{
		g_pinto.nowpos = max;
	}
	else if(g_pinto.nowpos < 0.0f)
	{
		g_pinto.nowpos = 0.0f;
	}





}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
PINTO* GetPinto()
{
	return &g_pinto;

}


void    SetLimit(int limit)
{
	g_limit = limit;

}
