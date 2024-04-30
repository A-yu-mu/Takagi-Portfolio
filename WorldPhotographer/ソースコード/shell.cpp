//=============================================================================
//shell.cpp		砲丸
// 作成者：髙橋啓佑　作成日：2022/10/28
//=============================================================================
#include "shell.h"
#include "sprite.h"
#include "texture.h"
//#include "explosion.h"
#include "playerCamera.h"

#include "player.h"
#include "io_ex.h"
#include "mapchip.h"
//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================
#define CANNON_NUM (100)//弾の出す間隔を数える変数の最大数
#define CANNON_ATTACKCOUNT (240)
#define SHELL_SPD (3.0f)
#define SHELL_TIME (180.0f)
//===================================
//グローバル変数
//===================================


static SHELL g_shell[SHELL_MAX];

//float pattern_shell_num = 1;
//float x_num = 1;
//float shell_y_num = 1;
//int   pattern_shell_size = 1;
//float shell_ysp = 0;


//弾の出す間隔を数える変数
//chipの
int Count[CANNON_NUM];
int Cannon[CANNON_NUM];

//===================================
//初期化
//===================================
HRESULT InitShell()
{
	int texNo = LoadTexture(g_TextureShellName);

	//カノンの初期化
	for (int i = 0; i < SHELL_MAX; i++)
	{
		g_shell[i].pos.x = 0;
		g_shell[i].pos.y = 0;

		/*g_shell.w = shell_SIZE_W;
		g_shell.h = shell_SIZE_H;*/
		g_shell[i].size = D3DXVECTOR2(SHELL_SIZE_W, SHELL_SIZE_H);

		g_shell[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_shell[i].rot = 0.0f;
		g_shell[i].use = false;
		g_shell[i].texno = texNo;
		g_shell[i].spd = D3DXVECTOR2(0.0f, 0.0f);
		g_shell[i].time = 0.0f;

	}

	//カノン用の初期化
	for (int i = 0; i < CANNON_NUM; i++)
	{
		Count[i] = 170;
		Cannon[i] = 0;
	}

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitShell()
{

}


//===================================
//描画
//===================================
void    DrawShell()
{
	
	//カノン表示
	for (int i = 0; i < SHELL_MAX; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(g_shell[i].pos);

		if (g_shell[i].use == true)
		{
			//テクスチャの表示
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_shell[i].texno));

		
			//スプライト表示
			DrawSpriteColorRotation
			(
				scrpos.x,
				scrpos.y,
				g_shell[i].size.x,
				g_shell[i].size.y,
				g_shell[i].rot,
				g_shell[i].Color,
				1,
				-1 * (g_shell[i].spd.x / SHELL_SPD),
				1.0f,
				1
			);
			//アニメーションパターン番号、パターンの横サイズ、縦サイズ、横居並ぶパターンの数
		
		}
	}

}

//===================================
//更新
//===================================
void    UpdateShell()
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (g_shell[i].use)
		{
			g_shell[i].pos += g_shell[i].spd;
			g_shell[i].time += 1.0f;
			if (g_shell[i].time >= SHELL_TIME)
			{
				g_shell[i].time = 0.0f;
				g_shell[i].use = false;
			}
	
		}

	}
	


}


//===================================
//カノン構造体の先頭ポインタを取得
//===================================
SHELL* GetShell()
{
	return &g_shell[0];
}

void SetShell(D3DXVECTOR2 pos, int puramai)
{
	for (int i = 0; i < SHELL_MAX; i++) {
		if (g_shell[i].use == false)
		{
			g_shell[i].pos = pos;
			g_shell[i].use = true;
			g_shell[i].spd = D3DXVECTOR2(SHELL_SPD * puramai, 0.0f);
			PlaySE(SE_SHELL);
			return;
		}
	}
}

bool	CountShell(int chipnum)
{
	for (int i = 0; i < CANNON_NUM; i++)
	{
		//カノンの番号が登録されてたらカウントを上げる
		if (chipnum == Cannon[i])
		{
			Count[i] += 1;
			if (Count[i] >= CANNON_ATTACKCOUNT)
			{
				Count[i] = 0;
				return true;
			}
			else
			{
				return false;
			}

		}
	}
		
	for (int i = 0; i < CANNON_NUM; i++)
	{		
		//カノンの番号が登録されて無かったら未使用の所に登録する
		if (Cannon[i] == 0)
		{
			Cannon[i] = chipnum;
			break;
		}
	}
	return false;
}
