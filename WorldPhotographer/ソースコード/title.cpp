//=============================================================================
//title.cpp
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#include "title.h"
#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
#include "UI.h"
#include "fade.h"

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================

static TITLE g_title;

float pattern_num_title = 0;
float yoko_num_title = 10;
float tate_num_title = 6;
int   pattern_size_title = 60;


//===================================
//初期化
//===================================
HRESULT InitTitle()
{

	g_title.select_title = 0;

	static	ID3D11ShaderResourceView* g_TextureTitle;//画像1枚で1つの変数が必要
	static	char* g_TextureNameTitle = (char*)"data\\texture\\TitleBGSprite.png";//テクスチャファイルパス JPG BMP PNG
	
	static	ID3D11ShaderResourceView* g_TextureTitleLogo;//画像1枚で1つの変数が必要
	static	char* g_TextureNameTitleLogo = (char*)"data\\texture\\world_photographer.png";//テクスチャファイルパス JPG BMP PNG

	g_title.h = SCREEN_HEIGHT;
	g_title.w = SCREEN_WIDTH;
	g_title.texno = LoadTexture(g_TextureNameTitle);
	g_title.texlogo = LoadTexture(g_TextureNameTitleLogo);

	PlayBGM(BGM_TITLE);
	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitTitle()
{
	StopSoundAll();
	//UninitSound();
	//UninitTexture();
}


//===================================
//描画
//===================================
void    DrawTitle()
{
	// タイトル画像
	{
		{
			pattern_num_title+=0.4;
		}
		if (pattern_num_title >= 30)
		{
			pattern_num_title = 0;
		}
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_title.texno));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_title.w, g_title.h, 0, g_title.Color, pattern_num_title, /*tate_num_title / pattern_size_title*/1.0f/7, /*tate_num_title*/1.0f/9, /*pattern_size_title*/7);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
	// タイトルロゴ
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_title.texlogo));

		//スプライト表示
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-50.0f, g_title.w* 7/9, g_title.h*2/9, 0, g_title.Color, 1, 1.0f,1.0f,1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
	
}


//===================================
//更新
//===================================
void    UpdateTitle()
{
	if (IsButton(L_DOWN, TRIGGER))
	{
		if (g_title.select_title == 0)
		{
			g_title.select_title += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_UP, TRIGGER))
	{
		if (g_title.select_title == 1)
		{
			g_title.select_title -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		switch (g_title.select_title)
		{
		case 0:
			// ステージセレクト
			SetFade(FADE_OUT_STAGESELECT);
			break;

		case 1:
			// 操作説明
			SetScene(SCENE_MANUAL);
			break;
		}
		PlaySE(SE_OK);
	}

	// モード切り替え
	{
		if (IsButton(L1, PUSH) && IsButton(R1, TRIGGER))
		{
			if (GetStageLockMode() == true)
			{
				SetStageLockMode(false);
				SetStageOpen(8);
			}
			else if (GetStageLockMode() == false)
			{
				SetStageLockMode(true);
				SetStageOpen(0);
			}
		}
	}
}

TITLE* GetTitle()
{
	return &g_title;
}

