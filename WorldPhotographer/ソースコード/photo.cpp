//=============================================================================
//photoreticle.cpp
// 作成者：舘崎　作成日：2022/10/22
//=============================================================================

#include "photo.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "player.h"
#include "layer.h"

#include "mapchip.h"

#include "playerCamera.h"

#include "photoeffect.h"

#include "photoreticle.h"

#include "fade.h"
#include "camera.h"
#include "io_ex.h"
//===================================
//マクロ定義
//===================================
#define SET_POSITION (D3DXVECTOR2(150.0f, 0.0f))

#define UI_PHOTO_X (260)
#define UI_PHOTO_Y (480)
#define UI_PHOTO_SIZE (60)

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================

static PHOTO g_photo_stock;
static PHOTO g_photo_put;
int g_photo_reset[PHOTO_MAPCHIP_NUM];
bool g_photo_reset_flag;

int bg;//UI用の

//===================================
//初期化
//===================================
HRESULT InitPhoto()
{
	//ストックフォトの初期化
	g_photo_stock.old_pos.x = g_photo_stock.pos.x = SCREEN_WIDTH / 2;
	g_photo_stock.old_pos.y = g_photo_stock.pos.y = SCREEN_HEIGHT / 2;

	g_photo_stock.w = PHOTO_SIZE_W;
	g_photo_stock.h = PHOTO_SIZE_H;

	g_photo_stock.rot = 0.0f;
	g_photo_stock.use = false;
	g_photo_stock.texno = LoadTexture(g_PhotoTextureName);

	//マップチップの初期化
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_stock.chip[i].pos.x = 0;
		g_photo_stock.chip[i].pos.y = 0;

		g_photo_stock.chip[i].size.x = MAPCHIP_WIDTH;
		g_photo_stock.chip[i].size.y = MAPCHIP_HEIGHT;

		g_photo_stock.chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_photo_stock.chip[i].type = CHIP_TYPE::TYPE_1;
		g_photo_stock.chip[i].texno = LoadTexture((char*)"data\\texture\\chip1.png");

		g_photo_stock.chip[i].use = true;
		g_photo_stock.chip[i].collision = false;
	}
	//プットフォトの初期化
	g_photo_put.pos.x = SCREEN_WIDTH / 2;
	g_photo_put.pos.y = SCREEN_HEIGHT / 2;
			
	g_photo_put.w = PHOTO_SIZE_W;
	g_photo_put.h = PHOTO_SIZE_H;
			
	g_photo_put.rot = 0.0f;
	g_photo_put.use = false;
	g_photo_put.texno = LoadTexture(g_PhotoTextureName);

	//マップチップの初期化
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_put.chip[i].pos.x = 0;
		g_photo_put.chip[i].pos.y = 0;

		g_photo_put.chip[i].size.x = MAPCHIP_WIDTH;
		g_photo_put.chip[i].size.y = MAPCHIP_HEIGHT;

		g_photo_put.chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_photo_put.chip[i].type = CHIP_TYPE::TYPE_1;
		g_photo_put.chip[i].texno = LoadTexture((char*)"data\\texture\\chip1.png");

		g_photo_put.chip[i].use = true;
		g_photo_put.chip[i].collision = false;
	}

	
	//マップチップの初期化
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_reset[i] = 0;
	}
	g_photo_reset_flag = false;

	bg = LoadTexture((char*)"data\\texture\\fade_white.png");

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitPhoto()
{

}


//===================================
//描画
//===================================
void    DrawPhoto()
{

	//UI用の枠 
	//テクスチャの表示
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
	//スプライト表示
	DrawSpriteColorRotation(
		UI_PHOTO_X + UI_PHOTO_SIZE / 2, UI_PHOTO_Y,
		UI_PHOTO_SIZE * 2, UI_PHOTO_SIZE,
		g_photo_put.rot, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f),//セピア明るめ
		1, 1, 1, 1);

	//ストックフォト表示
	if (g_photo_stock.use == true)
	{
		//持っているUI表示
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
		//スプライト表示
		DrawSpriteColorRotation(
			UI_PHOTO_X, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_stock.rot, D3DXCOLOR(0.76f, 0.54f, 0.17f, 1.0f),//セピア暗め
			1, 1, 1, 1);
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_stock.texno));
		//スプライト表示
		DrawSpriteColorRotation(
			UI_PHOTO_X, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, 1, 1);


		//標準のテクスチャを使う
		PHOTORETICLE* p_reti = GetPhotoreticle();
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

		//設置予測位置のスプライト表示
		PLAYER* p_player = GetPlayer();
		D3DXVECTOR2 scrpos = p_player->pos;
		DrawSpriteColorRotation(
			scrpos.x + SET_POSITION.x * GerLR(),
			scrpos.y + SET_POSITION.y,
			g_photo_stock.w,
			g_photo_stock.h,
			g_photo_stock.rot,
			D3DXCOLOR(g_photo_stock.Color.r, g_photo_stock.Color.g, g_photo_stock.Color.b, 0.7f),
			1,
			1,
			1,
			1);
		{//設置予測位置のスプライト表示(案その２カクカクバージョン)
			// PLAYERCAMERA* p_playercamera = GetPlayerCamera();
			////切りのいい所に設置する為に計算する
			//scrpos = D3DXVECTOR2(((int)(scrpos.x / MAPCHIP_WIDTH)) * MAPCHIP_WIDTH,
			//	((int)(scrpos.y / MAPCHIP_HEIGHT)) * MAPCHIP_HEIGHT);
			////スクロール分の差分を計算して増減させる
			//D3DXVECTOR2 gap;
			//gap.x = ((int)(p_playercamera->pos.x)) % (int)MAPCHIP_WIDTH;
			//gap.y = ((int)(p_playercamera->pos.y)) % (int)MAPCHIP_HEIGHT;
			//if (gap.x >= MAPCHIP_WIDTH / 2)
			//{
			//	gap.x *= -1.0f;
			//}
			//if (gap.y >= MAPCHIP_HEIGHT / 2)
			//{
			//	gap.y *= -1.0f;
			//}
			//scrpos += gap;

			//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_stock.texno));

			//DrawSpritePhoto(
			//	g_photo_stock.old_pos.x,
			//	g_photo_stock.old_pos.y,
			//	g_photo_stock.w,
			//	g_photo_stock.h,
			//	D3DXCOLOR(g_photo_stock.Color.r, g_photo_stock.Color.g, g_photo_stock.Color.b, 0.1f),
			//	scrpos + SET_POSITION
			//);
		}
		
	}
	//プットフォト表示
	if (g_photo_put.use == true)
	{
		//貼っているUI
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
		//スプライト表示
		DrawSpriteColorRotation(
			UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_put.rot, D3DXCOLOR(0.96f, 0.73f, 0.50f, 1.0f),//セピア明るめ
			1, 1, 1, 1);
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_put.texno));
		//スプライト表示
		DrawSpriteColorRotation(
			UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_put.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, 1, 1);

		//実際においている写真
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_put.texno));

		DrawSpritePhoto(
			g_photo_put.old_pos.x,
			g_photo_put.old_pos.y,
			g_photo_put.w,
			g_photo_put.h,
			g_photo_put.Color,
			ScreenPos(g_photo_put.pos)
		);

	}
	//UI用の枠 
	//標準のテクスチャを使う
	PHOTORETICLE* p_reti = GetPhotoreticle();

	//テクスチャの表示
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

	//スプライト表示
	DrawSpriteColorRotation(
		UI_PHOTO_X, UI_PHOTO_Y,
		UI_PHOTO_SIZE, UI_PHOTO_SIZE,
		g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1, 1, 1, 1);

	//テクスチャの表示
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

	//スプライト表示
	DrawSpriteColorRotation(
		UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
		UI_PHOTO_SIZE, UI_PHOTO_SIZE,
		g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1, 1, 1, 1);

}


//===================================
//更新
//===================================
void    UpdatePhoto()
{
	//キーボードのtrigger入力

	if (IsButton(R1, TRIGGER) && GetFadeStatus() == FADE_NONE
		&& NowCameraFlag() == false)//Vキーとフェードが動いていない時

	{
		//ストックがある時の処理
		if (g_photo_stock.use == true && g_photo_put.use == false)
		{
			PLAYER* p_player = GetPlayer();
			PLAYERCAMERA* p_playercamera = GetPlayerCamera();

			//スクリーンの移動分を計算する
			D3DXVECTOR2 scrpos = p_player->pos;
			scrpos.x += (p_playercamera->pos.x - SCREEN_WIDTH / 2);
			scrpos.y += (p_playercamera->pos.y - SCREEN_HEIGHT / 2);
			//現在のストックをプットにセット
			SetPhotoPut(
				g_photo_stock.w,
				g_photo_stock.h,
				g_photo_stock.old_pos,
				g_photo_stock.Color,
				g_photo_stock.texno,
				//切りのいい所に設置する為に計算する
				D3DXVECTOR2(((int)(scrpos.x / MAPCHIP_WIDTH)) * MAPCHIP_WIDTH,
					((int)(scrpos.y / MAPCHIP_HEIGHT)) * MAPCHIP_HEIGHT)
				 + SET_POSITION * GerLR(),
				g_photo_stock.chip
			);
			

			//写真設置エフェクト
			SetPhotoEffect(p_player->pos.x + 80.0f * GerLR(), p_player->pos.y, 0.2f);
			

			PlaySE(SE_PHOTO_ON);
			

			//ストックをfalseにする
			g_photo_stock.use = false;
		}
		//プットがある時の処理
		else if (g_photo_put.use == true)
		{
			//プットをfalseにする
			g_photo_put.use = false;
			PlaySE(SE_PHOTO_OFF);

		}

	}

	//プットフォトの情報を現在のマップチップに反映する
	//マップチップの情報を取得
	CHIP* p_chip = GetChip();
	int* p_mapChipList;
	//int p_reset_chip[PHOTO_MAPCHIP_NUM];


	//レイヤーのマップチップをプットフォトで上書きする
	if (g_photo_put.use == true)
	{
		int chip_x = g_photo_put.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
		int chip_y = g_photo_put.pos.y / MAPCHIP_HEIGHT - (PHOTO_MAPCHIP_HEIGHT_NUM / 2);

		int j = 0;
		PLAYER* p_player = GetPlayer();
		for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
		{
			for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
			{
				//カギフラグが立ったら時はカギをセットフォトから消す
				if (p_player->keyuse == true && (int)g_photo_put.chip[j].type == 13)
				{
					g_photo_put.chip[j].type = (CHIP_TYPE)0;
				}
				//張り付けるマップチップが0の時は書き換えない
				if ((int)g_photo_put.chip[j].type != 0)
				{
					p_mapChipList = GetMapChipList(chip_y + y, chip_x + x);
					//リセットがまだ無ければ
					if (g_photo_reset_flag == false)
					{
						g_photo_reset[j] = *p_mapChipList;
					}
					//張り付ける先が0以外の時も書き換えない
					if (*p_mapChipList == 0)
					{
						*p_mapChipList = (int)g_photo_put.chip[j].type;
					}

				}
				j++;
			}
		}
		//リセットをtrueにする
		g_photo_reset_flag = true;

	}

	//レイヤーのマップチップをリセットフォトで上書きする
	if (g_photo_reset_flag == true && g_photo_put.use == false)
	{
		int chip_x = g_photo_put.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
		int chip_y = g_photo_put.pos.y / MAPCHIP_HEIGHT - (PHOTO_MAPCHIP_HEIGHT_NUM / 2);

		int j = 0;
		for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
		{
			for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
			{
				//張り付けるマップチップが0の時は書き換えない
				if ((int)g_photo_put.chip[j].type != 0)
				{
					p_mapChipList = GetMapChipList(chip_y + y, chip_x + x);
					
					*p_mapChipList = g_photo_reset[j];

				}
				j++;
			}
		}
		g_photo_reset_flag = false;
	}


	
}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
PHOTO* GetPhotoStock()
{
	return &g_photo_stock;
}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
PHOTO* GetPhotoPut()
{
	return &g_photo_put;
}

//===================================
//ストックのセッター
//===================================
void SetPhotoStock(float w, float h, D3DXVECTOR2 pos, D3DXCOLOR Color, float texno, CHIP* chip)
{
	g_photo_stock.old_pos.x = pos.x;
	g_photo_stock.old_pos.y = pos.y;

	g_photo_stock.w = w;
	g_photo_stock.h = h;

	g_photo_stock.Color = Color;

	g_photo_stock.use = true;
	g_photo_stock.texno = texno;

	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_stock.chip[i] = chip[i];
	}
}

//===================================
//プットのセッター
//===================================
void SetPhotoPut(float w, float h, D3DXVECTOR2 old_pos, D3DXCOLOR Color, float texno, D3DXVECTOR2 pos, CHIP* chip)
{
	g_photo_put.old_pos.x = old_pos.x;
	g_photo_put.old_pos.y = old_pos.y;

	g_photo_put.w = w;
	g_photo_put.h = h;

	g_photo_put.Color = Color;

	g_photo_put.use = true;
	g_photo_put.texno = texno;

	g_photo_put.pos.x = pos.x;
	g_photo_put.pos.y = pos.y;

	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_put.chip[i] = chip[i];
	}
}

