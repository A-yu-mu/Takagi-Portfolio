//=============================================================================
//cannon.cpp		大砲
// 作成者：髙橋啓佑　作成日：2022/10/28
//=============================================================================



//プレイヤーのライフが尽きて死亡フラグが立った時、大砲が画面右に動くようになっています。
//死亡したというのが見てわかるようにするためなのでのちに消す予定





#include "cannon.h"
#include "sprite.h"
#include "texture.h"
//#include "explosion.h"

#include "player.h"
#include "shell.h"
//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================


//===================================
//グローバル変数
//===================================
int yubiori;

static CANNON g_cannon[CANNON_MAX];

//===================================
//初期化
//===================================
HRESULT InitCannon()
{
	///*int texNo= LoadTexture(g_TextureCannonName);*/
	yubiori = 0;
	//カノンの初期化
	for (int i = 0; i < CANNON_MAX; i++)
	{
		g_cannon[i].pos.x = 0 + 42;
		g_cannon[i].pos.y = 0 + 16;

		/*g_cannon.w = CANNON_SIZE_W;
		g_cannon.h = CANNON_SIZE_H;*/
		g_cannon[i].size = D3DXVECTOR2(CANNON_SIZE_W, CANNON_SIZE_H);

		g_cannon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_cannon[i].rot = 0.0f;
		g_cannon[i].use = false;
		/*g_cannon[i].texno = texNo;*/
		//g_cannon[i].hitCollision = false;
		//g_cannon[i].upCollision = false;
		

	}
	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitCannon()
{

}


//===================================
//描画
//===================================
void    DrawCannon()
{
	//カノン表示
	//for (int  i = 0; i < CANNON_MAX; i++)
	//{
	//	if(g_cannon[i].use==true)
	//	{
	//	//テクスチャの表示
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cannon[i].texno));
	//	}
	//}
	
}

//===================================
//更新
//===================================
void    UpdateCannon()
{
	yubiori++;
	PLAYER* pPlayer = GetPlayer();
	SHELL* pShell = GetShell();
	/*for (int i = 0; i < CANNON_MAX; i++)
	{
		if (pPlayer->DeathFlag==true)
		{
			g_cannon[i].pos.x += 1.0f;
		}
		if (g_cannon[i].use == true)
		{
			if (yubiori % 60 == 0)
			{
				SetShell(g_cannon[i].pos - D3DXVECTOR2(96.0f,16.0f));
				
			}
		}
	}*/



}

//===================================
//カノン構造体の先頭ポインタを取得
//===================================
CANNON* GetCannon()
{
	return &g_cannon[0];
}

void SetCannon(D3DXVECTOR2 pos)
{
	for (int i = 0; i < CANNON_MAX; i++) {
		if (g_cannon[i].use == false)
		{
			g_cannon[i].pos = pos;
			g_cannon[i].use = true;
			return;
		}
	}
}