#include "playerCamera.h"
#include "player.h"
#include "mapchip.h"
#include "timelimit.h"

static PLAYERCAMERA g_playercamera;
D3DXVECTOR2 camerapos;
D3DXVECTOR2 screenpos;


HRESULT InitPlayerCamera()
{
	//g_playercamera.pos = D3DXVECTOR2(0, 0);
	//g_playercamera.oldpos = D3DXVECTOR2(0, 0);

	g_playercamera.range = D3DXVECTOR2(MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT);

	g_playercamera.pos.x = 0;
	g_playercamera.oldpos.x = 0;

	g_playercamera.ysp = 0;
	

	g_playercamera.scrollmoveRight = false;
	g_playercamera.scrollmoveLeft = false;
	g_playercamera.scrollLock = false;
	 return S_OK;
}
void UpdatePlayerCamera()
{

	//���W�m�F�p
	{
/*#ifdef _DEBUG
		printf("�v���C���[�J�������W�F�@%f %f \n", g_playercamera.pos.x, g_playercamera.pos.y);


#endif*/ // _DEBUG

	}
	g_playercamera.oldpos = g_playercamera.pos;

	PLAYER* player = GetPlayer();

	if (g_playercamera.pos.x - SCREEN_WIDTH /2 < 0)//�}�b�v�̍��[�ɍs���߂��Ȃ��悤�ɃJ�������Œ�
	{
		g_playercamera.pos.x = SCREEN_WIDTH/2;
	
	}

	if (g_playercamera.pos.x + SCREEN_WIDTH / 2 > g_playercamera.range.x)//�}�b�v�̈�ԉE�[�܂ōs���߂��Ȃ��悤�ɃJ�������Œ�
	{
		g_playercamera.pos.x = g_playercamera.range.x - SCREEN_WIDTH / 2;
	}
	
	//Y�̐ݒ�
	if (g_playercamera.pos.y - SCREEN_HEIGHT / 2 < 0)//�}�b�v�̏�ɍs���߂��Ȃ��悤�ɃJ�������Œ�
	{
		g_playercamera.pos.y = SCREEN_HEIGHT / 2;
	}

	if (g_playercamera.pos.y + SCREEN_HEIGHT / 2 > g_playercamera.range.y)//�}�b�v�̈�ԉ��܂ōs���߂��Ȃ��悤�ɃJ�������Œ�
	{
		g_playercamera.pos.y = g_playercamera.range.y - SCREEN_HEIGHT / 2;
	}

	if (g_playercamera.scrollmoveRight)
	{
		g_playercamera.pos.x += player->move;
	}
	if (g_playercamera.scrollmoveLeft)
	{
		g_playercamera.pos.x -= player->move;
	}

	if (player->pos.y >= SCREEN_HEIGHT * 2 / 3)
	{
		g_playercamera.pos.y += g_playercamera.ysp;
		player->pos.y = SCREEN_HEIGHT * 2 / 3;
		player->player_ysp = 0;
	}
	if (player->pos.y <= SCREEN_HEIGHT / 3)
	{
		
		/*player->pos.y = SCREEN_HEIGHT / 6;*/
		if (g_playercamera.ysp < 0)
		{
			g_playercamera.pos.y += g_playercamera.ysp;
			player->player_ysp = 0;
		}
	}
	
}



D3DXVECTOR2 ScreenPos(D3DXVECTOR2 pos)
{
	camerapos = D3DXVECTOR2(g_playercamera.pos.x - SCREEN_WIDTH / 2, g_playercamera.pos.y - SCREEN_HEIGHT / 2);//�����ŃJ�����̃|�W�V����������(���̏ꍇ�J�����̈ʒu��0�C0)

	screenpos = D3DXVECTOR2(pos.x - camerapos.x, pos.y - camerapos.y);//�J�����̈ʒu�ɍ��킹�ē����̂�scroll���Č�����

	return screenpos;
}

D3DXVECTOR2 OldScreenPos(D3DXVECTOR2 pos)
{
	camerapos = D3DXVECTOR2(g_playercamera.oldpos.x - SCREEN_WIDTH / 2, g_playercamera.oldpos.y - SCREEN_HEIGHT / 2);//�����ŃJ�����̃|�W�V����������(���̏ꍇ�J�����̈ʒu��0�C0)

	screenpos = D3DXVECTOR2(pos.x - camerapos.x, pos.y - camerapos.y);//�J�����̈ʒu�ɍ��킹�ē����̂�scroll���Č�����

	return screenpos;
}



PLAYERCAMERA* GetPlayerCamera()
{
	return &g_playercamera;
}


void ScrollStop(int i)
{
	CHIP* chip = GetChip();
	PLAYER* player = GetPlayer();

	D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);
	if (scrpos.x > SCREEN_WIDTH / 4) {
		g_playercamera.pos.x++; 
		player->pos.x--;
		player->controlrock = true;
		g_playercamera.scrollmoveRight = false;
		g_playercamera.scrollmoveLeft = false;
	}
	else {
		player->controlrock = false;
	}
	
	g_playercamera.scrollLock = true;

}

void ScrollStopLift(int i)
{
	CHIP* chip = GetChip();
	PLAYER* player = GetPlayer();

	D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);
	if (scrpos.x > SCREEN_WIDTH / 2) {
		g_playercamera.pos.x += 2;
		player->pos.x -= 2;
		player->controlrock = true;
		g_playercamera.scrollmoveRight = false;
		g_playercamera.scrollmoveLeft = false;
	}
	else {
		player->controlrock = false;
	}

	g_playercamera.scrollLock = false;
}

void ScrollStopGoal(int j)
{
	CHIP* chip = GetChip();
	PLAYER* player = GetPlayer();
	TimeLimit* timelimit = GetTimeLimit2();

	timelimit->PlayerGoal = true;

	D3DXVECTOR2 scrpos = ScreenPos(chip[j].pos);
	if (scrpos.x > SCREEN_WIDTH / 2) {
		g_playercamera.pos.x++;
		player->pos.x--;
		player->controlrock = true;
		g_playercamera.scrollmoveRight = false;
		g_playercamera.scrollmoveLeft = false;
	}
	else {
		player->PlayerGoal = true;
	}


	g_playercamera.scrollLock = true;

}