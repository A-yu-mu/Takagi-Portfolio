//=============================================================================
// mcgimmick.cpp
// 作成者：髙木歩夢　作成日：2022/10/28 
//=============================================================================
#include "mcgimmick.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "player_effect.h"

#include "inputx.h"

#include "playerCamera.h"
#include "player_afterimage.h"
#include "playerCamera.h"

#include "mapchip.h"

#include "io_ex.h"
#include <iostream>

//===================================
// グローバル変数
//===================================


PLAYERCAMERA* playercamera = GetPlayerCamera();
PLAYER* pPlayer = GetPlayer();
CHIP* chip = GetChip();
PLAYERCAMERA* pPlayercamera = GetPlayerCamera();
AfterImage* afterimage = GetAfterImage();



#define DAMAGE1 (1)


#define SKELETON_NUM (200)//消える床の最大数
#define SKELETON_REBORNCOUNT (180)

static PLAYER *p_player;

int SkelCount[SKELETON_NUM];
int SkelNum[SKELETON_NUM];

int SkelNumStart[SKELETON_NUM];

void InitMcGimmick()
{
	for (int i = 0; i < SKELETON_NUM; i++)
	{
		SkelCount[i] = 0;
		SkelNum[i] = 0;
		SkelNumStart[i] = 0;
	}
	
}
//==================================
// ライフダメージ
//==================================
void LifeDamage(void)
{
	pPlayer->isDamage = true;	// ダメージ
}

//==================================
// ジャンプ力アップ
//==================================
void JunpPowerUp(void)
{
	pPlayer->player_ysp = -20; //ジャンプ力


	
	PlaySE(SE_JUMPUP);



	pPlayercamera->ysp = -20;

}

//==================================
// 通常時のジャンプ力
//==================================
void noGravity(void)
{
	pPlayer->player_ysp = 0;
	pPlayer->PlayerWalk = true;
	pPlayercamera->ysp = 0;

	

}

void afterimageGravity()
{
	afterimage->ysp = 0;
}

void ColMoveChipX(int chipno)
{
	pPlayer->pos.x += chip[chipno].move;
}

void AIColMoveChipX(int chipno)
{
	afterimage->pos.x += chip[chipno].move;
}

void ColMoveChipY(int chipno)
{
	pPlayer->pos.y += chip[chipno].move;
}

void AIColMoveChipY(int chipno)
{
	afterimage->pos.y += chip[chipno].move;
}

void MoveChipX(int chipno , float distance,int sp)//左がチップの配列番号、右がチップの動かしたい距離
{
	if (chip[chipno].movesp)
	{
		chip[chipno].move = sp;
		chip[chipno].movesp = false;
	}

	if (chip[chipno].originChipPos.x + (distance / 2) <= chip[chipno].pos.x || chip[chipno].originChipPos.x - (distance / 2) >= chip[chipno].pos.x)
	{
		chip[chipno].move *= -1;
		chip[chipno].pos.x += chip[chipno].move;
	}
	if (chip[chipno].originChipPos.x + (distance / 2) >= chip[chipno].pos.x && chip[chipno].originChipPos.x - (distance / 2) <= chip[chipno].pos.x)
	{
		chip[chipno].pos.x += chip[chipno].move ;
		
	}
}

void MoveChipY(int chipno, float distance, int sp)
{
	if (chip[chipno].movesp)
	{
		chip[chipno].move = sp;
		chip[chipno].movesp = false;
	}

	if (chip[chipno].originChipPos.y + (distance / 2) <= chip[chipno].pos.y || chip[chipno].originChipPos.y - (distance / 2) >= chip[chipno].pos.y)
	{
		chip[chipno].move *= -1;
		chip[chipno].pos.y += chip[chipno].move;
	}
	if (chip[chipno].originChipPos.y + (distance / 2) >= chip[chipno].pos.y && chip[chipno].originChipPos.y - (distance / 2) <= chip[chipno].pos.y)
	{
		chip[chipno].pos.y += chip[chipno].move;

	}
}

void IceBlock()
{
	if (pPlayer->move > 0)
	{
		pPlayer->move -= 0.05f;
	}

	if (pPlayer->texLorR == 1 && !pPlayer->PressRight)
	{
		if (playercamera->pos.x + SCREEN_WIDTH / 2 >= playercamera->range.x && pPlayer->pos.x >= SCREEN_WIDTH / 2 || playercamera->scrollLock) //カメラがマップの右端に来た時、画面3/4より右でも移動可
		{
			if (pPlayer->pos.x >= SCREEN_WIDTH - pPlayer->size.x / 2) {} //画面右端でプレイヤーを止める
			else {
				pPlayer->pos.x += pPlayer->move;
			}
		}
		else if (pPlayer->pos.x >= SCREEN_WIDTH / 2) //カメラがマップの右端に来た時以外、画面3/4から右にスクロール
		{
			playercamera->pos.x += pPlayer->move;
		}
		else if (pPlayer->pos.x < SCREEN_WIDTH / 2) //画面3/4より右へ移動不可
		{
			pPlayer->pos.x += pPlayer->move;
		}
	}

	if (pPlayer->texLorR == -1 && !pPlayer->PressLeft)
	{
		if (playercamera->pos.x - SCREEN_WIDTH / 2 <= 0 && pPlayer->pos.x <= SCREEN_WIDTH / 2 || playercamera->scrollLock) //カメラがマップの右端に来た時、画面3/4より右でも移動可
		{
			if (pPlayer->pos.x <= 0 + pPlayer->size.x / 2) {} //画面右端でプレイヤーを止める
			else {
				pPlayer->pos.x -= pPlayer->move;
			}
		}
		else if (pPlayer->pos.x <= SCREEN_WIDTH / 2) //カメラがマップの右端に来た時以外、画面3/4から右にスクロール
		{
			playercamera->pos.x -= pPlayer->move;
		}
		else if (pPlayer->pos.x > SCREEN_WIDTH / 2) //画面3/4より右へ移動不可
		{
			pPlayer->pos.x -= pPlayer->move;
		}
	}
}

void SkeletonBlonkStart(int chipnum)
{
	bool end = true; 
	for (int i = 0; i < SKELETON_NUM && end == true; i++)
	{
		//カノンの番号が登録されてたら終了する
		if (chipnum == SkelNumStart[i])
		{
			end = false;
		}
	}
	for (int i = 0; i < SKELETON_NUM && end == true; i++)
	{
		//カノンの番号が登録されて無かったら未使用の所に登録する
		if (SkelNumStart[i] == 0)
		{
			SkelNumStart[i] = chipnum;
			break;
		}
	}


}


bool SkeletonBlonkDo(int chipnum)
{
	for (int i = 0; i < SKELETON_NUM; i++)
	{
		//カノンの番号が登録されて無かったら未使用の所に登録する
		if (SkelNumStart[i] == chipnum)
		{
			return true;
		}
	}
	//無ければfalse
	return false;
}

bool SkeletonBlonkReborn(int chipnum)
{
	for (int i = 0; i < SKELETON_NUM; i++)
	{
		//カノンの番号が登録されてたらカウントを上げる
		if (chipnum == SkelNum[i])
		{
			SkelCount[i] += 1;
			if (SkelCount[i] >= SKELETON_REBORNCOUNT)
			{
				SkelCount[i] = 0;
				for (int i = 0; i < SKELETON_NUM; i++)
				{
					//カノンの番号が登録されている所をリセットする
					if (chipnum == SkelNumStart[i])
					{
						SkelNumStart[i] = 0;
						return true;
					}
				}
			}
			else
			{
				return false;
			}

		}
	}

	for (int i = 0; i < SKELETON_NUM; i++)
	{
		//カノンの番号が登録されて無かったら未使用の所に登録する
		if (SkelNum[i] == 0)
		{
			SkelNum[i] = chipnum;
			break;
		}
	}
	return false;
}

