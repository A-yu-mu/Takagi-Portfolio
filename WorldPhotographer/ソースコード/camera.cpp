//=============================================================================
//camera.cpp
// 作成者：岸直哉/小林良太　作成日：2022/10/21
//=============================================================================
#include "camera.h"
#include "sprite.h"
#include "texture.h"
#include "windows.h"
#include "main.h"

#include "fade.h"
#include "player.h"

//カメラの子分
#include "layer.h"
#include "photo.h"
#include "photoreticle.h"
#include "pinto.h"
#include "io_ex.h"

//今がカメラパートがどうか判断するフラグ
bool camera_scene_flag;


static PLAYER* g_player = GetPlayer();

//カメラのUIのテクスチャ番号
float cameraUItexno = 0;


HRESULT InitCamera()
{
	//フラグの初期化
	camera_scene_flag = false;

	//カメラの子分の初期化
	InitLayer();
	InitPhoto();
	InitPhotoreticle();
	InitPinto();

	cameraUItexno = LoadTexture(g_TextureNameCamera);

	return S_OK;
}

void UnInitCamera()
{
	//カメラの子分の終了処理
	UnInitLayer();
	UnInitPhoto();
	UnInitPhotoreticle();
	UnInitPinto();

}

void DrawCamera()
{
	DrawPhoto();

	//camera_scene_flagがtrueになっている時のみ更新、描画処理を行う
	if (camera_scene_flag == true)
	{
		
		
		//カメラの子分の描画処理
		DrawLayer();
		DrawPhotoreticle();
		DrawPinto();

		//UIの表示
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(cameraUItexno));

		//スプライト表示
		DrawSpriteColorRotation(
			SCREEN_WIDTH / 2, 
			SCREEN_HEIGHT / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数


	}

}

void UpdateCamera()
{
	{//カメラパートの切り替えをキーボードで管理する
		//キーボードのtrigger入力

		if (IsButton(X, TRIGGER) || IsButton(Y, TRIGGER))//XYキー

		{
			g_player->PlayerCamera = true;
			//押した瞬間の処理
			PlaySE(SE_TURN);
		}

	}

	UpdatePhoto();

	//camera_scene_flagがtrueになっている時のみ更新、描画処理を行う
	if (camera_scene_flag == true)
	{
		//カメラの子分の更新処理
		UpdateLayer();
		UpdatePhotoreticle();
		UpdatePinto();

	}
	
}

//===================================
//カメラパートの開始関数
//===================================
void    StartCamera()
{
	camera_scene_flag = true;
}

//===================================
//カメラパートの終了関数
//===================================
void    EndCamera()
{
	camera_scene_flag = false;
}

//===================================
//現在のカメラパートのフラグを返す関数
//===================================
bool NowCameraFlag()
{
	return camera_scene_flag;
}

