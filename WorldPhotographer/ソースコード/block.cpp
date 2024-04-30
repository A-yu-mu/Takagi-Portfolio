//=============================================================================
//block.cpp
// çÏê¨é“ÅFä›íºç∆/è¨ó—ó«ëæÅ@çÏê¨ì˙ÅF2022/10/21
//=============================================================================
#include "block.h"
#include "sprite.h"
#include "texture.h"

BLOCK g_block[BLOCK_MAX];

HRESULT InitBlock()
{
	for (int i = 0; i <BLOCK_MAX; i++)
	{
		//îöî≠ÇÃèâä˙âª
		g_block[i].pos.x = 0;
		g_block[i].pos.y = 0;

		g_block[i].size.x = 0;
		g_block[i].size.y = 0;
		g_block[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_block[i].use = false;

		g_block[i].texno = LoadTexture(g_TextureNameBlock);
	}
	return S_OK;

}

void UnInitBlock()
{


}

void DrawBlock()
{
	for(int i = 0;i < BLOCK_MAX;i++)
	{
		if (g_block[i].use)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_block[i].texno));
			DrawSpriteColorRotation(g_block[i].pos.x, g_block[i].pos.y, g_block[i].size.x, g_block[i].size.y, 0, g_block[i].Color, 0, 1, 1, 2);
		}
	}

}

void UpdateBlock()
{

}

void SetBlock(float x, float y, float px, float py)
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (!g_block[i].use)
		{
			g_block[i].size.x = x;
			g_block[i].size.y = y;


			g_block[i].pos.x = px;
			g_block[i].pos.y = py;

			g_block[i].use = true;

			return;
		}
	}

}

BLOCK* GetBlock()
{
	return g_block;
}
