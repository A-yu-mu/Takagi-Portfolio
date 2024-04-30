//=============================================================================
//explosion.cpp
// 作成者：岸直哉　作成日：2022/07/11
//=============================================================================

#include "player_effect.h"
#include "sprite.h"
#include "texture.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================
// 
//===================================
//グローバル変数
//===================================


static PLAYER_EFFECT g_player_jump_effect;
static PLAYER_EFFECT g_player_landing_effect[EXPLOSION_MAX];

int   pattern_size_explosion = 8;


//===================================
//初期化
//===================================
HRESULT InitPlayerEffect()
{

	//プレイヤージャンプ時のエフェクト初期化
	g_player_jump_effect.pos.x = 0;
	g_player_jump_effect.pos.y = 0;

	g_player_jump_effect.w = EXPLOSION_SIZE_W;
	g_player_jump_effect.h = EXPLOSION_SIZE_H;

	g_player_jump_effect.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_player_jump_effect.rot = 0.0f;

	g_player_jump_effect.use = false;

	g_player_jump_effect.pattern_num_explosion = 0;

	g_player_jump_effect.texno = LoadTexture(g_TextureNamePlayerJumpEffect);

	//プレイヤー着地時のエフェクト初期化
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_player_landing_effect[i].pos.x = 0;
		g_player_landing_effect[i].pos.y = 0;

		g_player_landing_effect[i].w = EXPLOSION_SIZE_W;
		g_player_landing_effect[i].h = EXPLOSION_SIZE_H;

		g_player_landing_effect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player_landing_effect[i].rot = 0.0f;

		g_player_landing_effect[i].use = false;

		g_player_landing_effect[i].pattern_num_explosion = 0;

		g_player_landing_effect[i].texno = LoadTexture(g_TextureNamePlayerLandingEffect);
	}

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitPlayerEffect()
{

}


//===================================
//描画
//===================================
void    DrawPlayerEffect()
{
	//プレイヤー表示
	if (g_player_jump_effect.use)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_player_jump_effect.texno));

		//スプライト表示

		DrawSpriteColorRotation(g_player_jump_effect.pos.x, g_player_jump_effect.pos.y, g_player_jump_effect.w, g_player_jump_effect.h, g_player_jump_effect.rot, g_player_jump_effect.Color,
			(int)g_player_jump_effect.pattern_num_explosion, 1.0 / pattern_size_explosion, 1.0 / 1.0, pattern_size_explosion);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_player_landing_effect[i].use)
		{
			//テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_player_landing_effect[i].texno));

			//スプライト表示

			DrawSpriteColorRotation(g_player_landing_effect[i].pos.x, g_player_landing_effect[i].pos.y, g_player_landing_effect[i].w, g_player_landing_effect[i].h, g_player_landing_effect[i].rot, g_player_landing_effect[i].Color,
				(int)g_player_landing_effect[i].pattern_num_explosion, 1.0 / pattern_size_explosion, 1.0 / 1.0, pattern_size_explosion);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		}
	}
}


//===================================
//更新
//===================================
void    UpdatePlayerEffect()
{

	if (g_player_jump_effect.use)
	{
		g_player_jump_effect.pattern_num_explosion += g_player_jump_effect.m_animeSpeed;
		if ((int)g_player_jump_effect.pattern_num_explosion > EXPLOSION_ANIME_MAX)
		{
			g_player_jump_effect.use = false;
			g_player_jump_effect.pattern_num_explosion = 0.0f;
		}
	}
	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_player_landing_effect[i].use)
		{
			g_player_landing_effect[i].pattern_num_explosion += g_player_landing_effect[i].m_animeSpeed;
			if ((int)g_player_landing_effect[i].pattern_num_explosion > EXPLOSION_ANIME_MAX)
			{
				g_player_landing_effect[i].use = false;
				g_player_landing_effect[i].pattern_num_explosion = 0.0f;
			}
		}
	}
}

//===================================
//explosion構造体の先頭ポインタを取得
//===================================
PLAYER_EFFECT* GetPlayerEffect()
{
	return &g_player_jump_effect;
}

//==================================
//セットバレット
//==================================

void SetPlayerJumpEffect(float x,float y,float animeSpeed)
{

	if (!g_player_jump_effect.use)
	{
		//バレットの初期化
		g_player_jump_effect.pos.x = x;
		g_player_jump_effect.pos.y = (y + 20.0f);

		g_player_jump_effect.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player_jump_effect.rot = 0.0f;

		g_player_jump_effect.m_animeSpeed = animeSpeed;
		g_player_jump_effect.use = true;
		return;

	}
}

void SetPlayerLandingEffect(float x, float y, float animeSpeed)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_player_landing_effect[i].use)
		{
			//バレットの初期化
			g_player_landing_effect[i].pos.x = x;
			g_player_landing_effect[i].pos.y = (y + 20.0f);

			g_player_landing_effect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_player_landing_effect[i].rot = 0.0f;

			g_player_landing_effect[i].m_animeSpeed = animeSpeed;
			g_player_landing_effect[i].use = true;
			return;

		}
	}
}