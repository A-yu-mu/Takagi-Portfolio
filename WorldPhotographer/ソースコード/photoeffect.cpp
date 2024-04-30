//=============================================================================
//photoeffect.cpp
// 作成者：有郷 拓海　作成日：2022/11/15
//=============================================================================

#include "photoeffect.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "player.h"
#include "photo.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================


static PHOTOEFFECT g_photoeffect[PHOTOEFFECT_MAX];

int   pattern_size_photoeffect = 8;

PLAYER* p_Player = GetPlayer();
PHOTO* p_Photo = GetPhotoPut();

//===================================
//初期化
//===================================
HRESULT InitPhotoEffect()
{

	for (int i = 0; i <PHOTOEFFECT_MAX; i++)
	{
		//爆発の初期化
		g_photoeffect[i].pos.x = 0;
		g_photoeffect[i].pos.y = 0;
				
		g_photoeffect[i].w =PHOTOEFFECT_SIZE_W;
		g_photoeffect[i].h =PHOTOEFFECT_SIZE_H;
				
		g_photoeffect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_photoeffect[i].rot = 0.0f;
				
		g_photoeffect[i].use = false;

		g_photoeffect[i].pattern_num_explosion = 0;
				
		g_photoeffect[i].texno = LoadTexture(g_TextureNamePhotoEffect);
	}
	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitPhotoEffect()
{

}


//===================================
//描画
//===================================
void    DrawPhotoEffect()
{
	//プレイヤー表示
	{

		for (int i = 0; i < PHOTOEFFECT_MAX; i++)
		{
			if (g_photoeffect[i].use)
			{
				//テクスチャの表示
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photoeffect[i].texno));

				//スプライト表示
				//プレイヤーの右側に写真を設置する場合(右向き)
				if (p_Player->pos.x <= p_Photo->pos.x)
				{
					DrawSpriteColorRotation(g_photoeffect[i].pos.x, g_photoeffect[i].pos.y, g_photoeffect[i].w, g_photoeffect[i].h, g_photoeffect[i].rot, g_photoeffect[i].Color,
						(int)g_photoeffect[i].pattern_num_explosion, 1.0 / pattern_size_photoeffect, 1.0 / 2.0, pattern_size_photoeffect);
				}

				//プレイヤーの左側に写真を設置する場合(左向き)
				if (p_Player->pos.x >= p_Photo->pos.x)
				{
					DrawSpriteColorRotation(g_photoeffect[i].pos.x, g_photoeffect[i].pos.y, g_photoeffect[i].w, g_photoeffect[i].h, g_photoeffect[i].rot, g_photoeffect[i].Color,
						(int)g_photoeffect[i].pattern_num_explosion + 8, 1.0 / pattern_size_photoeffect, 1.0 / 2.0, pattern_size_photoeffect);
				}
			}
		}
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
}


//===================================
//更新
//===================================
void    UpdatePhotoEffect()
{
	for (int i = 0; i < PHOTOEFFECT_MAX; i++)
	{
		if (g_photoeffect[i].use)
		{
			g_photoeffect[i].pattern_num_explosion += g_photoeffect[i].m_animeSpeed;
			if((int)g_photoeffect[i].pattern_num_explosion > PHOTOEFFECT_ANIME_MAX)
			{
				g_photoeffect[i].use = false;
				g_photoeffect[i].pattern_num_explosion = 0.0f;
			}
		}
	}

}

//===================================
//explosion構造体の先頭ポインタを取得
//===================================
PHOTOEFFECT* GetPhotoEffect()
{
	return g_photoeffect;
}

//==================================
//セットバレット
//==================================

void SetPhotoEffect(float x,float y,float animeSpeed)
{
	for (int i = 0; i <PHOTOEFFECT_MAX; i++)
	{
		if (!g_photoeffect[i].use)
		{
			//バレットの初期化
			g_photoeffect[i].pos.x = x;
			g_photoeffect[i].pos.y = y;

			g_photoeffect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_photoeffect[i].rot = 0.0f;

			g_photoeffect[i].m_animeSpeed = animeSpeed;
			g_photoeffect[i].use = true;
			return;
		}
	}
}
