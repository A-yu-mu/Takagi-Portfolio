//=============================================================================
//cursor_A.cpp
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#include "syouzyun.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================


static CURSOR_A g_cursor_A;

float pattern_nums = 0;
float yoko_nums = 0;
float tate_nums = 1;
int   pattern_sizes = 1;
int tests;

//===================================
//初期化
//===================================
HRESULT InitCursor_A()
{
	//プレイヤーの初期化
	g_cursor_A.pos.x = SCREEN_WIDTH / 2 + 40;
	g_cursor_A.pos.y = SCREEN_HEIGHT / 2 + 120;

	g_cursor_A.w = CURSOR_A_SIZE_W;
	g_cursor_A.h = CURSOR_A_SIZE_H;

	//g_cursor_A.Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
	g_cursor_A.rot = 0.0f;
	g_cursor_A.use = true;
	g_cursor_A.texno = LoadTexture(g_TextureName_A);
	g_cursor_A.texno_B = LoadTexture(g_TextureName_B);
	g_cursor_A.texno_T1 = LoadTexture(g_TextureName_T1);
	g_cursor_A.texno_T2 = LoadTexture(g_TextureName_T2);
	g_cursor_A.texno_T3 = LoadTexture(g_TextureName_T3);
	g_cursor_A.texno_T4 = LoadTexture(g_TextureName_T4);
	g_cursor_A.texno_T5 = LoadTexture(g_TextureName_T5);

	g_cursor_A.camera_use = false;


	g_cursor_A.zoom = 1;
	//D3DXVECTOR2 pos_z;
	//float zw, zh;
	//int frame;

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitCursor_A()
{

}


//===================================
//描画
//===================================
void    DrawCursor_A()
{
	if (g_cursor_A.camera_use == true)
	{
		

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_B));
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH+g_cursor_A.a*g_cursor_A.zoom-10, SCREEN_HEIGHT + g_cursor_A.a * g_cursor_A.zoom-10, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);

		if (g_cursor_A.zoom == 1)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T1));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
		else if (g_cursor_A.zoom == 2)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T2));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else if (g_cursor_A.zoom == 3)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T3));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else if (g_cursor_A.zoom == 4)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T4));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T5));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
	}


	//プレイヤー表示
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno));

		//スプライト表示
		DrawSpriteColorRotation(g_cursor_A.pos.x, g_cursor_A.pos.y, g_cursor_A.w, g_cursor_A.h, g_cursor_A.rot, g_cursor_A.Color, pattern_nums, tate_nums / pattern_sizes, tate_nums, pattern_sizes);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
	
}


//===================================
//更新
//===================================
void    UpdateCursor_A()
{
	if (GetKeyboardTrigger(DIK_R))//Rキー
	{
		if (g_cursor_A.zoom >= 5)
		{

		}
		else
		{
			g_cursor_A.zoom += 1;
		}
		
	}
	else if (GetKeyboardTrigger(DIK_S))//Sキー
	{
		if (g_cursor_A.zoom <= 1) 
		{
			
		}
		else
		{
			g_cursor_A.zoom -= 1;
		}
		
	}


	//キーボードの入力
	if (GetKeyboardTrigger(DIK_Z))//Zキー
	{
		// 上から画像被せる
		// カメラ起動フラグ true
		g_cursor_A.camera_use = true;
	}
	else if (GetKeyboardTrigger(DIK_X))//Xキー
	{
		g_cursor_A.camera_use = false;
	}


	//キーボードの入力
	if (GetKeyboardPress(DIK_UP))//上キー
	{
		//押されている間の処理
		g_cursor_A.pos.y -= 5.0f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_cursor_A.pos.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		//押されている間の処理
		g_cursor_A.pos.x += 5.0f;
		
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		g_cursor_A.pos.x -= 5.0f;
	}
	
}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
CURSOR_A* GetCursor_A()
{
	return &g_cursor_A;
}