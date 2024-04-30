#include "player_afterimage.h"
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "playerCamera.h"
#include "mapchip.h"
#include "io_ex.h"
#include "player_effect.h"

AfterImage after_image;
PLAYER* player;

int after_texLorR = 1;
int after_texSelect = 0;
float after_y_num = 1;
int after_pattern_size[TEX_MAX];

D3DXVECTOR2 scr;

//焼き付け用のエフェクト
float g_Effect;
static	int g_AFETexture;//画像1枚で1つの変数が必要
static	char* g_AFETextureName = (char*)"data\\texture\\afterimage.png";//テクスチャファイルパス JPG BMP PNG

HRESULT InitAfterImage()
{

	after_image.use = false;
	after_image.pos = D3DXVECTOR2(0.0f, 0.0f);
	after_image.oldpos = D3DXVECTOR2(0.0f, 0.0f);

	after_image.rot = 0.0f;

	after_image.scrpos = D3DXVECTOR2(0.0f, 0.0f);

	after_image.ysp = 0.0f;

	after_image.col = false;

	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float pattern_num;


	after_pattern_size[0] = 3;
	after_pattern_size[1] = 5;
	after_pattern_size[2] = 3;

	g_Effect = 0.0f;
	g_AFETexture = LoadTexture(g_AFETextureName);

	return S_OK;
}

void UnInitAfterImage()
{
}

void DrawAfterImage()
{
	if (after_image.use)
	{
		player = GetPlayer();
		
		//スプライト表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(player->texno[after_texSelect]));
		
		after_image.scrpos = ScreenPos(after_image.pos) - scr;
		
		//スプライト表示

		DrawSpriteColorRotation(after_image.scrpos.x, after_image.scrpos.y, after_image.size.x, after_image.size.y, player->rot, player->Color,
			after_image.pattern_num, 1.0f / after_pattern_size[after_texSelect] * after_texLorR, 1.0f / after_y_num, after_pattern_size[after_texSelect]);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

		//エフェクト表示
		if (g_Effect > 0.0f)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_AFETexture));

			//スプライト表示

			DrawSpriteColorRotation(after_image.scrpos.x, after_image.scrpos.y, 
				after_image.size.x * 1.7f, after_image.size.y * 1.7f,
				player->rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect),
				1,1,1,1);


		}
	}

}

void UpdateAfterImage()
{
	player = GetPlayer();
	D3DXVECTOR2 scrpos = ScreenPos(player->pos);

	after_image.oldpos = after_image.pos;

	if (!after_image.col)
	{
		after_image.pos.y += after_image.ysp;

		after_image.ysp += 1.0f;
	}

	if (!after_image.use && IsButton(L1, TRIGGER))
	{
		after_image.pos.x = player->pos.x;
		after_image.pos.y = player->pos.y -1;
		after_image.size = player->size;
		after_image.pattern_num = player->pattern_num;
		after_texSelect = player->texSelect;
		if (!player->PlayerWalk) { after_texSelect = 2; }

		scr = scrpos - player->pos;

		after_image.ysp = 0;
		after_image.use = true;

		//エフェクト
		g_Effect = 1.0f;
		SetPlayerJumpEffect(after_image.pos.x, after_image.pos.y - MAPCHIP_HEIGHT, 0.5f);
		PlaySE(SE_AFTERIMAGE_ON);
	}
	else if (after_image.use && IsButton(L1, TRIGGER))
	{
		after_image.col = false;
		after_image.use = false;
		SetAISwitch(false);

		//エフェクト
		g_Effect = 0.0f;

		PlaySE(SE_AFTERIMAGE_OFF);
	}

	//エフェクト更新
	if (g_Effect > 0.0f)
	{
		g_Effect -= 0.05f;
	}
	else if (g_Effect <= 0.0f)
	{
		g_Effect = 0.0f;
	}
	
}

AfterImage* GetAfterImage()
{
	return &after_image;
}

void AfterImageReset()
{
	if (after_image.use == true){
		PlaySE(SE_AFTERIMAGE_OFF);
	}
	after_image.col = false;
	after_image.use = false;
	SetAISwitch(false);

	//エフェクト
	g_Effect = 0.0f;

}
