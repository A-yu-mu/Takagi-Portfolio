//=============================================================================
// mcgimmick.cpp
// ì¬ÒFûüØà²@ì¬úF2022/10/28 
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
// O[oÏ
//===================================


PLAYERCAMERA* playercamera = GetPlayerCamera();
PLAYER* pPlayer = GetPlayer();
CHIP* chip = GetChip();
PLAYERCAMERA* pPlayercamera = GetPlayerCamera();
AfterImage* afterimage = GetAfterImage();



#define DAMAGE1 (1)


#define SKELETON_NUM (200)//Á¦é°ÌÅå
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
// Ct_[W
//==================================
void LifeDamage(void)
{
	pPlayer->isDamage = true;	// _[W
}

//==================================
// WvÍAbv
//==================================
void JunpPowerUp(void)
{
	pPlayer->player_ysp = -20; //WvÍ


	
	PlaySE(SE_JUMPUP);



	pPlayercamera->ysp = -20;

}

//==================================
// ÊíÌWvÍ
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

void MoveChipX(int chipno , float distance,int sp)//¶ª`bvÌzñÔAEª`bvÌ®©µ½¢£
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
		if (playercamera->pos.x + SCREEN_WIDTH / 2 >= playercamera->range.x && pPlayer->pos.x >= SCREEN_WIDTH / 2 || playercamera->scrollLock) //Jª}bvÌE[É½AæÊ3/4æèEÅàÚ®Â
		{
			if (pPlayer->pos.x >= SCREEN_WIDTH - pPlayer->size.x / 2) {} //æÊE[ÅvC[ð~ßé
			else {
				pPlayer->pos.x += pPlayer->move;
			}
		}
		else if (pPlayer->pos.x >= SCREEN_WIDTH / 2) //Jª}bvÌE[É½ÈOAæÊ3/4©çEÉXN[
		{
			playercamera->pos.x += pPlayer->move;
		}
		else if (pPlayer->pos.x < SCREEN_WIDTH / 2) //æÊ3/4æèEÖÚ®sÂ
		{
			pPlayer->pos.x += pPlayer->move;
		}
	}

	if (pPlayer->texLorR == -1 && !pPlayer->PressLeft)
	{
		if (playercamera->pos.x - SCREEN_WIDTH / 2 <= 0 && pPlayer->pos.x <= SCREEN_WIDTH / 2 || playercamera->scrollLock) //Jª}bvÌE[É½AæÊ3/4æèEÅàÚ®Â
		{
			if (pPlayer->pos.x <= 0 + pPlayer->size.x / 2) {} //æÊE[ÅvC[ð~ßé
			else {
				pPlayer->pos.x -= pPlayer->move;
			}
		}
		else if (pPlayer->pos.x <= SCREEN_WIDTH / 2) //Jª}bvÌE[É½ÈOAæÊ3/4©çEÉXN[
		{
			playercamera->pos.x -= pPlayer->move;
		}
		else if (pPlayer->pos.x > SCREEN_WIDTH / 2) //æÊ3/4æèEÖÚ®sÂ
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
		//JmÌÔªo^³êÄ½çI¹·é
		if (chipnum == SkelNumStart[i])
		{
			end = false;
		}
	}
	for (int i = 0; i < SKELETON_NUM && end == true; i++)
	{
		//JmÌÔªo^³êÄ³©Á½ç¢gpÌÉo^·é
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
		//JmÌÔªo^³êÄ³©Á½ç¢gpÌÉo^·é
		if (SkelNumStart[i] == chipnum)
		{
			return true;
		}
	}
	//³¯êÎfalse
	return false;
}

bool SkeletonBlonkReborn(int chipnum)
{
	for (int i = 0; i < SKELETON_NUM; i++)
	{
		//JmÌÔªo^³êÄ½çJEgðã°é
		if (chipnum == SkelNum[i])
		{
			SkelCount[i] += 1;
			if (SkelCount[i] >= SKELETON_REBORNCOUNT)
			{
				SkelCount[i] = 0;
				for (int i = 0; i < SKELETON_NUM; i++)
				{
					//JmÌÔªo^³êÄ¢éðZbg·é
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
		//JmÌÔªo^³êÄ³©Á½ç¢gpÌÉo^·é
		if (SkelNum[i] == 0)
		{
			SkelNum[i] = chipnum;
			break;
		}
	}
	return false;
}

