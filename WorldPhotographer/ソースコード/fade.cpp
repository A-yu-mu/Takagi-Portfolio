
#include "fade.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"

#include "camera.h"

#define FADE_SPEED	(0.06f)

float g_Alfha;
FADE_STATUS g_Fade;

static	ID3D11ShaderResourceView* g_FadeTexture;//画像1枚で1つの変数が必要
static	char* g_FadeTextureName = (char*)"data\\texture\\Shutter_A_1920_1080_30fps_v02.png";//テクスチャファイルパス JPG BMP PNG

static int g_FadeTextureNo = 0;

bool UseCamera;

FADE* Fade;//背景構造体のポインタ変数

HRESULT InitFade()
{
	g_Alfha = 0.0f;
	g_Fade = FADE_NONE;

	//背景の初期化
	Fade = new FADE;//背景のインスタンス作成
	Fade->Position.x = SCREEN_WIDTH / 2;
	Fade->Position.y = SCREEN_HEIGHT / 2;
	Fade->Position.z = 0;

	Fade->size.x = SCREEN_WIDTH;
	Fade->size.y = SCREEN_HEIGHT;

	Fade->Rotation = 0.0f;

	Fade->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//textureのロード
	g_FadeTextureNo = LoadTexture(g_FadeTextureName);
	if (g_FadeTextureNo == -1)
	{//ロードエラー
		exit(999);//強制終了
	}

	UseCamera = false;

	return S_OK;
}


void UninitFade()
{
	if (Fade)
	{
		delete Fade;
	}
}


void UpdateFade()
{
	if (g_Fade == FADE_OUT_NORMAL)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//カメラモードの終了
			EndCamera();

			//UseCamera = true;
		}
	}

	if (g_Fade == FADE_OUT_CAMERA)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//カメラモードの起動
			StartCamera();

			//UseCamera = false;
		}
	}

	if (g_Fade == FADE_OUT_TITLE)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//リザルト画面移行
			SetScene(SCENE_TITLE);
		}
	}

	if (g_Fade == FADE_OUT_STAGESELECT)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//リザルト画面移行
			SetScene(SCENE_STAGESELECT);
		}
	}

	if (g_Fade == FADE_OUT_GAME)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//リザルト画面移行
			SetScene(SCENE_GAME);
		}
	}

	if (g_Fade == FADE_OUT_GAMEOVER)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//リザルト画面移行
			SetScene(SCENE_GAMEOVER);
		}
	}

	if (g_Fade == FADE_OUT_RESULT)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//リザルト画面移行
			SetScene(SCENE_RESULT);
		}
	}

	if (g_Fade == FADE_IN)
	{
		g_Alfha -= FADE_SPEED;

		if (g_Alfha <= 0.0f)
		{
			g_Alfha = 0.0f;
			g_Fade = FADE_NONE;
		}
	}
}

void DrawFade()
{
	//if (UseCamera == true)
	//{
	//	//テクスチャの表示
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeTextureNo));
	//	D3DXCOLOR col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	//	//スプライト表示
	//	DrawSpriteColorRotation(Fade->Position.x, Fade->Position.y, Fade->size.x, Fade->size.y, Fade->Rotation, Fade->Color, 0, 1, 1, 2);
	//	//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	//}

	if (g_Fade != FADE_NONE)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeTextureNo));

		//スプライト表示
		DrawSpriteColorRotation(Fade->Position.x, Fade->Position.y, Fade->size.x, Fade->size.y, Fade->Rotation, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			g_Alfha * 4 + 1, 0.2f, 1, 5);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
	}
}

void SetFade(FADE_STATUS status)
{
	g_Fade = status;

	if (status == FADE_IN)
	{
		g_Alfha = 1.0f;
	}

	if (status == FADE_OUT_NORMAL)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_TITLE)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_STAGESELECT)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_GAME)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_GAMEOVER)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_RESULT)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_CAMERA)
	{
		g_Alfha = 0.0f;
	}
}

//現在のフェードの状態を返す
FADE_STATUS GetFadeStatus()
{
	return g_Fade;
}
