//=============================================================================
//photoreticle.cpp
// 作成者：舘崎　作成日：2022/10/22
//=============================================================================

#include "photoreticle.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "camera.h"
#include "layer.h"
#include "photo.h"
#include "playerCamera.h"

#include "fade.h"
#include "player.h"
#include "io_ex.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数                 
//===================================


static PHOTORETICLE g_photoreticle;
//===================================
//初期化
//===================================
HRESULT InitPhotoreticle()
{


	//カメラの標準の初期化
	g_photoreticle.pos.x = SCREEN_WIDTH / 2;
	g_photoreticle.pos.y = SCREEN_HEIGHT / 2;

	g_photoreticle.w = PHOTORETICLE_SIZE_W;
	g_photoreticle.h = PHOTORETICLE_SIZE_H;

	g_photoreticle.rot = 0.0f;
	g_photoreticle.use = true;
	g_photoreticle.texno = LoadTexture(g_PhotoreticleTextureName);


	return S_OK;
}


//===================================
//終了
//===================================
void    UnInitPhotoreticle()
{

}


//===================================
//描画
//===================================
void    DrawPhotoreticle()
{

	//カメラ表示
	if (g_photoreticle.use == true)
	{
		////レイヤーから現在のtexnoを取得
		//LAYER* p_layer = GetLayer();
		//
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_layer->texno));

		//DrawSpritePhoto(
		//	g_photoreticle.pos.x,
		//	g_photoreticle.pos.y,
		//	g_photoreticle.w,
		//	g_photoreticle.h,
		//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//	g_photoreticle.pos
		//);

		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photoreticle.texno));

		//スプライト表示
		DrawSpriteColorRotation(
			g_photoreticle.pos.x,
			g_photoreticle.pos.y,
			g_photoreticle.w,
			g_photoreticle.h,
			g_photoreticle.rot,
			g_photoreticle.Color,
			1,
			1,
			1,
			1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

	}


}


//===================================
//更新
//===================================
void    UpdatePhotoreticle()
{
	//キーボードの入力
	if (IsButton(L_UP, TRIGGER))
	{

		g_photoreticle.pos.y -= MAPCHIP_HEIGHT;
		if (g_photoreticle.pos.y - MAPCHIP_HEIGHT * 3 <= 0)
		{
			g_photoreticle.pos.y = MAPCHIP_HEIGHT * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	else if (IsButton(L_DOWN, TRIGGER))
	{

		g_photoreticle.pos.y += MAPCHIP_HEIGHT;
		if (g_photoreticle.pos.y + MAPCHIP_HEIGHT * 3 >= SCREEN_HEIGHT)
		{
			g_photoreticle.pos.y = SCREEN_HEIGHT - MAPCHIP_HEIGHT * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}

	if (IsButton(L_RIGHT, TRIGGER))
	{
		//押されている間の処理
		g_photoreticle.pos.x += MAPCHIP_WIDTH;
		if (g_photoreticle.pos.x + MAPCHIP_WIDTH * 3 >= SCREEN_WIDTH)
		{
			g_photoreticle.pos.x = SCREEN_WIDTH - MAPCHIP_WIDTH * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	else if (IsButton(L_LEFT, TRIGGER))
	{

		g_photoreticle.pos.x -= MAPCHIP_WIDTH;
		if (g_photoreticle.pos.x - MAPCHIP_WIDTH * 3 <= 0)
		{
			g_photoreticle.pos.x = MAPCHIP_WIDTH * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	//キーボードのtrigger入力
	if (IsButton(R1, TRIGGER) && GetFadeStatus() == FADE_NONE)//r1
	{
		
	////キーボードのtrigger入力
	//if ((GetKeyboardTrigger(DIK_V)|| IsMouseLeftTriggered())//Vキー もしくは 左クリック
	//	&& GetFadeStatus() == FADE_NONE)

		PlaySE(SE_SHUTTER);
		//レイヤーが撮れる状況なら撮る
		if (GetLayerCanGet() == true)
		{
			//レイヤーの情報を取得
			LAYER* p_layer = GetLayer();

			//計算してセットストックに渡すマップチップ情報を決める
			//標準の左上がどこのマップチップか計算する
			int chip_x = g_photoreticle.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
			int chip_y = g_photoreticle.pos.y / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
			//左上のチップから順に情報を格納していく
			CHIP chip_stock[PHOTO_MAPCHIP_NUM];
			int j = 0;
			for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
			{
				for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
				{
					chip_stock[j] = p_layer->chip[chip_x + x + ((LAYER_CHIP_NUM_WIDTH * (chip_y + y)))];
					j++;
				}
			}

			//現在のレイヤーtexnoとレティクルとマップチップをストックにセット
			SetPhotoStock(
				g_photoreticle.w,
				g_photoreticle.h,
				g_photoreticle.pos,
				D3DXCOLOR(p_layer->Color.r, p_layer->Color.g, p_layer->Color.b, 0.25f),
				p_layer->texno,
				chip_stock
			);
		}
		PLAYER* p_player = GetPlayer();
		//カメラパートの終了
		SetFade(FADE_OUT_NORMAL);
		SetaNum(0);
		p_player->PlayerCamera = false;
		

	}

}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
PHOTORETICLE* GetPhotoreticle()
{
	return &g_photoreticle;
}


