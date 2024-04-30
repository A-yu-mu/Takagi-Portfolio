//=============================================================================
//player.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
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
//�}�N����`
//===================================

#define COUNT	(1.5f * FRAME_RATE)	// ���G���� (���G���� �~ �b�ԃt���[����);

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================


static PLAYER g_player;
static CHIP* g_chip;
static TimeLimit* g_timelimit_player = GetTimeLimit2();

//�O���[�o���ϐ�


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
//������
//===================================
HRESULT InitPlayer()
{

	//�v���C���[�̏�����
	//�J�n�ʒu�̏�����
	CHIP* StartChip = GetChip();
	D3DXVECTOR2 startpos = D3DXVECTOR2(620.0f, 125.0f);//�ꉞ������
	for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		if (StartChip[i].type == CHIP_TYPE::TYPE_19)//�����ʒu�����������珉�����ʒu�X�V
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
//�I��
//===================================
void    UnInitPlayer()
{

}


//===================================
//�`��
//===================================
void    DrawPlayer()
{
	//���W�m�F�p
	{
//#ifdef _DEBUG
//	printf("�v���C���[���W�F�@%f %f \n", g_player.pos.x, g_player.pos.y);
//
//
//#endif // _DEBUG

	}




	//�W�����v���̕`��
		
	if (!g_player.PlayerWalk && !g_player.PlayerCamera && !g_player.PlayerGoal)
	{
		g_player.texSelect = 2;

		//�X�v���C�g�\��
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

	//�J�������[�h�ڍs���̕\��

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

	//�S�[�����̃��[�V����
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

	//�X�v���C�g�\��

	DrawSpriteColorRotation(g_player.pos.x, g_player.pos.y, g_player.size.x, g_player.size.y, g_player.rot, g_player.Color,
		g_player.pattern_num, 1.0f / pattern_size[g_player.texSelect] * g_player.texLorR, 1.0f / y_num, pattern_size[g_player.texSelect]);
	//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

	


	//�J�M�̕\��
	if (g_player.keyuse == true)
	{
		CHIP* chip = GetChip();
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(chip[13].texno));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(g_player.pos.x, g_player.pos.y - 50, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f),
			1, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

	}
}


//===================================
//�X�V
//===================================
void    UpdatePlayer()
{
	PLAYERCAMERA* playercamera = GetPlayerCamera();

	g_player.oldpos = g_player.pos;

	g_player.texSelect = 0;
	g_player.pattern_num -= 0.1f;

	if (IsButton(L_RIGHT, PUSH))
	{

		//������Ă���Ԃ̏���

		if (!g_player.controlrock)
		{
			g_player.PressRight = true;
			//������Ă���Ԃ̏���
			g_player.texLorR = 1;
			g_player.move = 3.5f;

			if (playercamera->pos.x + SCREEN_WIDTH / 2 >= playercamera->range.x && g_player.pos.x >= SCREEN_WIDTH / 2 || playercamera->scrollLock) //�J�������}�b�v�̉E�[�ɗ������A���3/4���E�ł��ړ���
			{
				if (g_player.pos.x >= SCREEN_WIDTH - g_player.size.x / 2) {} //��ʉE�[�Ńv���C���[���~�߂�
				else {
					g_player.pos.x += g_player.move;
					g_player.texSelect = 0;
				}
			}
			else if (g_player.pos.x >= SCREEN_WIDTH / 2) //�J�������}�b�v�̉E�[�ɗ������ȊO�A���3/4����E�ɃX�N���[��
			{
				playercamera->scrollmoveRight = true;
				g_player.texSelect = 1;
			}
			else if (g_player.pos.x < SCREEN_WIDTH / 2) //���3/4���E�ֈړ��s��
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
	//cnt_num�L�[�F���ړ�
	//--------------------------
	if (IsButton(L_LEFT, PUSH))
	{
		if (!g_player.controlrock)
		{
			g_player.PressLeft = true;
			g_player.move = 3.5f;
			g_player.texLorR = -1;
			if (playercamera->pos.x - SCREEN_WIDTH / 2 <= 0 && g_player.pos.x <= SCREEN_WIDTH / 2 || playercamera->scrollLock) //�J�������}�b�v�̍��[�ɗ������A���1/4��荶�ł��ړ���
			{
				if (g_player.pos.x <= 0 + g_player.size.x / 2) {}//��ʍ��[�Ńv���C���[���~�߂�
				else
				{
					g_player.pos.x -= g_player.move;
					g_player.texSelect = 0;
				}
			}
			else if (g_player.pos.x <= SCREEN_WIDTH / 2)	//�J�������}�b�v�̍��[�ɗ������ȊO�A���1/4���獶�ɃX�N���[��
			{
				playercamera->scrollmoveLeft = true;
				g_player.texSelect = 1;
			}
			else if (g_player.pos.x > SCREEN_WIDTH / 2) //���1/4��荶�ֈړ��s��
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

	{	//�d��
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

	// ���񂾂Ƃ��̏���
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
		// ���߂��ׂ�
		SetFade(FADE_OUT_GAMEOVER);
	
	}
	else
	{
		g_player.DeathFlag = false;
	}

	// �_���[�W����
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

	// ���G�I������
	if (g_player.invincible == true && g_player.count <= 0)
	{
		g_player.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player.invincible = false;
	}

	// ���G������
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

	//�J�M�̏���(�h�A��2�}�X����̂Ń}�b�v�`�b�v���Ńt���O��ς����1�}�X�c��̂ŕςȏ��������Ă��܂�)
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
//�v���C���[�\���̂̐擪�|�C���^���擾
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
//�v���C���[�̌����Ă������Ԃ�
int	GerLR()
{
	return g_player.texLorR;

}
