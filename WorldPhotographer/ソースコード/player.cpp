//=============================================================================
//player.cpp
// 作成者：岸直哉　作成日：2022/06/27
//=============================================================================

#include "player.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "player_effect.h"
#include "playerCamera.h"
#include "collision.h"
#include "mapchip.h"
#include "fade.h"
#include "io_ex.h"
#include "timelimit.h"

//===================================
//マクロ定義
//===================================

#define COUNT	(1.5f * FRAME_RATE)	// 無敵時間 (無敵時間 × 秒間フレーム数);

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================


static PLAYER g_player;
static CHIP* g_chip;
static TimeLimit* g_timelimit_player = GetTimeLimit2();

//グローバル変数


float ysp = 0;
float y_num = 1;
int pattern_size[TEX_MAX];

float player_ysp = 0;


int	cnt_num = 0;
int camera_num = 0;
int goal_num = 0;
int num_a = 0;
int num_b = 0;

//===================================
//初期化
//===================================
HRESULT InitPlayer()
{

	//プレイヤーの初期化
	//開始位置の初期化
	CHIP* StartChip = GetChip();
	D3DXVECTOR2 startpos = D3DXVECTOR2(620.0f, 125.0f);//一応初期化
	for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		if (StartChip[i].type == CHIP_TYPE::TYPE_19)//初期位置が見つかったら初期化位置更新
		{
			startpos = StartChip[i].pos;

			break;
		}
	}
	PLAYERCAMERA* p_camera = GetPlayerCamera();
	p_camera->pos.y = p_camera->oldpos.y = startpos.y;

	g_player.pos = startpos;
	g_player.oldpos = startpos;
	g_player.size = D3DXVECTOR2(PLAYER_SIZE_W, PLAYER_SIZE_H);

	g_player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_player.rot = 0.0f;
	g_player.use = true;

	g_player.texSelect = 0;

	g_player.texno[0] = LoadTexture(g_TextureName);
	g_player.texno[1] = LoadTexture(g_TextureName2);
	g_player.texno[2] = LoadTexture(g_TextureName3);
	g_player.texno[3] = LoadTexture(g_TextureName4);
	pattern_size[0] = 3;
	pattern_size[1] = 5;
	pattern_size[2] = 3;
	pattern_size[3] = 4;

	g_player.move = 4.0f;
	g_player.texLorR = 1;

	g_player.PressRight = false;
	g_player.PressLeft = false;

	g_player.pattern_num = 0;
	g_player.life = 3;

	g_player.controlrock = false;
	g_player.isDamage = false;
	g_player.invincible = false;
	g_player.DeathFlag = false;

	g_player.count = 0;

	g_player.player_ysp = 0;

	g_player.PlayerWalk = false;
	g_player.PlayerCamera = false;
	g_player.PlayerGoal = false;

	g_player.PlayerJumpEffect = false;
	g_player.PlayerLandingEffect = false;

	cnt_num = 0;
	camera_num = 0;
	num_a = 0;
	num_b = 0;
	
	g_player.keyuse = false;
	g_player.keyuse_next = false;

	return S_OK;

}

//===================================
//終了
//===================================
void    UnInitPlayer()
{

}


//===================================
//描画
//===================================
void    DrawPlayer()
{
	//座標確認用
	{
//#ifdef _DEBUG
//	printf("プレイヤー座標：　%f %f \n", g_player.pos.x, g_player.pos.y);
//
//
//#endif // _DEBUG

	}




	//ジャンプ時の描画
		
	if (!g_player.PlayerWalk && !g_player.PlayerCamera && !g_player.PlayerGoal)
	{
		g_player.texSelect = 2;

		//スプライト表示
		if (g_player.player_ysp < 1)
		{
			g_player.pattern_num = 0;

			if (g_player.PlayerJumpEffect == true)
			{
				SetPlayerJumpEffect(g_player.pos.x, g_player.pos.y, 0.5f);
			}


			if (g_player.texLorR == -1)
			{
				g_player.pattern_num = -1;
			}
		}
		if (g_player.player_ysp > 1 && g_player.player_ysp < 15)
		{
			g_player.pattern_num = 1;
		}
		if (g_player.player_ysp > 15)
		{
			g_player.pattern_num = 2;
		}
	}

	//カメラモード移行時の表示

	if (g_player.PlayerCamera)
	{
		g_player.PlayerWalk = false;

		g_player.texSelect = 3;

		cnt_num++;

		if (g_player.texLorR == 1)
		{
			if (cnt_num % 15 == 0)
			{
				num_a += 1;
				cnt_num = 0;
			}

			switch (num_a)
			{
			case 0:
				camera_num = 0;
				break;
			case 1:
				camera_num = 1;
				break;
			case 2:
				camera_num = 2;
				break;
			case 3:
				camera_num = 3;
				break;
			case 4:
				SetFade(FADE_OUT_CAMERA);
				
				break;
			}
		}

		if (g_player.texLorR == -1)
		{
			if (cnt_num % 15 == 0)
			{
				num_b += 1;
				cnt_num = 0;
			}

			switch (num_b)
			{
			case 0:
				camera_num = 3;
				break;
			case 1:
				camera_num = 2;
				break;
			case 2:
				camera_num = 1;
				break;
			case 3:
				camera_num = 0;
				break;
			case 4:
				SetFade(FADE_OUT_CAMERA);
				
				break;
			}
		}
		g_player.pattern_num = camera_num;
	}

	//ゴール時のモーション
	if (g_player.PlayerGoal)
	{
		g_player.PlayerWalk = false;

		g_player.texSelect = 3;

		cnt_num++;

		if (g_player.texLorR == 1)
		{
			if (cnt_num % 15 == 0)
			{
				num_a += 1;
				cnt_num = 0;
			}

			switch (num_a)
			{
			case 0:
				goal_num = 0;
				break;
			case 1:
				goal_num = 1;
				break;
			case 2:
				goal_num = 2;
				break;
			case 3:
				goal_num = 3;
				break;
			case 4:
				SetFade(FADE_OUT_RESULT);
				break;
			}
		}
		if (g_player.texLorR == -1)
		{
			if (cnt_num % 15 == 0)
			{
				num_b += 1;
				cnt_num = 0;
			}

			switch (num_b)
			{
			case 0:
				goal_num = 3;
				break;
			case 1:
				goal_num = 2;
				break;
			case 2:
				goal_num = 1;
				break;
			case 3:
				goal_num = 0;
				break;
			case 4:
				SetFade(FADE_OUT_RESULT);
				break;
			}
		}
		g_player.pattern_num = goal_num;
	}

	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_player.texno[g_player.texSelect]));

	//スプライト表示

	DrawSpriteColorRotation(g_player.pos.x, g_player.pos.y, g_player.size.x, g_player.size.y, g_player.rot, g_player.Color,
		g_player.pattern_num, 1.0f / pattern_size[g_player.texSelect] * g_player.texLorR, 1.0f / y_num, pattern_size[g_player.texSelect]);
	//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

	


	//カギの表示
	if (g_player.keyuse == true)
	{
		CHIP* chip = GetChip();
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(chip[13].texno));

		//スプライト表示
		DrawSpriteColorRotation(g_player.pos.x, g_player.pos.y - 50, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),
			1, 1, 1, 1);
		//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数

	}
}


//===================================
//更新
//===================================
void    UpdatePlayer()
{
	PLAYERCAMERA* playercamera = GetPlayerCamera();

	g_player.oldpos = g_player.pos;

	g_player.texSelect = 0;
	g_player.pattern_num -= 0.1f;

	if (IsButton(L_RIGHT, PUSH))
	{

		//押されている間の処理

		if (!g_player.controlrock)
		{
			g_player.PressRight = true;
			//押されている間の処理
			g_player.texLorR = 1;
			g_player.move = 3.5f;

			if (playercamera->pos.x + SCREEN_WIDTH / 2 >= playercamera->range.x && g_player.pos.x >= SCREEN_WIDTH / 2 || playercamera->scrollLock) //カメラがマップの右端に来た時、画面3/4より右でも移動可
			{
				if (g_player.pos.x >= SCREEN_WIDTH - g_player.size.x / 2) {} //画面右端でプレイヤーを止める
				else {
					g_player.pos.x += g_player.move;
					g_player.texSelect = 0;
				}
			}
			else if (g_player.pos.x >= SCREEN_WIDTH / 2) //カメラがマップの右端に来た時以外、画面3/4から右にスクロール
			{
				playercamera->scrollmoveRight = true;
				g_player.texSelect = 1;
			}
			else if (g_player.pos.x < SCREEN_WIDTH / 2) //画面3/4より右へ移動不可
			{
				g_player.pos.x += g_player.move;
				playercamera->scrollmoveRight = false;
				g_player.texSelect = 1;

			}

			g_player.texSelect = 1;
		}
		else
		{
			playercamera->scrollmoveRight = false;
		}

	}
	else
	{
		g_player.PressRight = false;
		playercamera->scrollmoveRight = false;
	}
	//--------------------------
	//cnt_numキー：左移動
	//--------------------------
	if (IsButton(L_LEFT, PUSH))
	{
		if (!g_player.controlrock)
		{
			g_player.PressLeft = true;
			g_player.move = 3.5f;
			g_player.texLorR = -1;
			if (playercamera->pos.x - SCREEN_WIDTH / 2 <= 0 && g_player.pos.x <= SCREEN_WIDTH / 2 || playercamera->scrollLock) //カメラがマップの左端に来た時、画面1/4より左でも移動可
			{
				if (g_player.pos.x <= 0 + g_player.size.x / 2) {}//画面左端でプレイヤーを止める
				else
				{
					g_player.pos.x -= g_player.move;
					g_player.texSelect = 0;
				}
			}
			else if (g_player.pos.x <= SCREEN_WIDTH / 2)	//カメラがマップの左端に来た時以外、画面1/4から左にスクロール
			{
				playercamera->scrollmoveLeft = true;
				g_player.texSelect = 1;
			}
			else if (g_player.pos.x > SCREEN_WIDTH / 2) //画面1/4より左へ移動不可
			{
				g_player.pos.x -= g_player.move;
				playercamera->scrollmoveLeft = false;
				g_player.texSelect = 1;
			}
			g_player.texSelect = 1;

		}
		else
		{
			playercamera->scrollmoveLeft = false;
		}
		
	}
	else
	{
		g_player.PressLeft = false;
		playercamera->scrollmoveLeft = false;
	}
	//
	if (g_player.PlayerWalk)
	{
		if (IsButton(A, TRIGGER))
		{
			g_player.player_ysp = -15;
			playercamera->ysp = -15;
			
			PlaySE(SE_JUMP);
		}
	}

	{	//重力
		g_player.pos.y += g_player.player_ysp;
		g_player.player_ysp += 1.0f;

		playercamera->ysp += 1.0f;
	}

	if (g_player.pos.y >= SCREEN_HEIGHT + g_player.size.y)
	{
		g_player.life = 0;
		g_player.use = false;
		g_player.DeathFlag = true;
	}

	if (g_timelimit_player->use == true && g_timelimit_player->Limit <= 0)
	{
		g_player.life -= 3;

		g_timelimit_player->use = false;
	}

	// 死んだときの処理
	if (g_player.life <= 0)
	{
		g_player.use = false;
		g_player.DeathFlag = true;
		g_player.pos.x = 0 + 80;
		g_player.pos.y = 0 + 300;
		g_player.count = 0;
		g_player.invincible = true;
		playercamera->pos.x = SCREEN_WIDTH / 2;
		playercamera->pos.y = SCREEN_HEIGHT / 2;

		g_player.life = 2;
		playercamera->scrollLock = false;
		// がめおべら
		SetFade(FADE_OUT_GAMEOVER);
	
	}
	else
	{
		g_player.DeathFlag = false;
	}

	// ダメージ処理
	if (g_player.isDamage == true && g_player.invincible == false && g_player.count <= 0)
	{
		g_player.life -= 1;
		PlaySE(SE_DAMAGE);

		if (g_player.life >= 1)
		{
			g_player.count = COUNT;
			g_player.Color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			g_player.invincible = true;
			g_player.isDamage = false;
		}
	}
	else
	{
		g_player.isDamage = false;
	}

	// 無敵終了処理
	if (g_player.invincible == true && g_player.count <= 0)
	{
		g_player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player.invincible = false;
	}

	// 無敵中処理
	if (g_player.count >= 0)
	{
		g_player.count--;

		if (g_player.count % 2)
		{
			g_player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_player.Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.1f);
		}
	}

	//カギの処理(ドアが2マスあるのでマップチップ内でフラグを変えると1マス残るので変な書き方しています)
	if (g_player.keyuse_next == false)
	{
		g_player.keyuse = false;
	}

	if (g_player.oldpos.y < g_player.pos.y)
	{
		g_player.PlayerLandingEffect = false;
	}
}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
PLAYER* GetPlayer()
{
	return &g_player;
}


void SetaNum(int num)
{
	num_a = num;
	num_b = num;
}
//プレイヤーの向いてる方向を返す
int	GerLR()
{
	return g_player.texLorR;

}
