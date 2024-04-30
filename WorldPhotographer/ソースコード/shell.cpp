//=============================================================================
//shell.cpp		�C��
// �쐬�ҁF�����[�C�@�쐬���F2022/10/28
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
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================
#define CANNON_NUM (100)//�e�̏o���Ԋu�𐔂���ϐ��̍ő吔
#define CANNON_ATTACKCOUNT (240)
#define SHELL_SPD (3.0f)
#define SHELL_TIME (180.0f)
//===================================
//�O���[�o���ϐ�
//===================================


static SHELL g_shell[SHELL_MAX];

//float pattern_shell_num = 1;
//float x_num = 1;
//float shell_y_num = 1;
//int   pattern_shell_size = 1;
//float shell_ysp = 0;


//�e�̏o���Ԋu�𐔂���ϐ�
//chip��
int Count[CANNON_NUM];
int Cannon[CANNON_NUM];

//===================================
//������
//===================================
HRESULT InitShell()
{
	int texNo = LoadTexture(g_TextureShellName);

	//�J�m���̏�����
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

	//�J�m���p�̏�����
	for (int i = 0; i < CANNON_NUM; i++)
	{
		Count[i] = 170;
		Cannon[i] = 0;
	}

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitShell()
{

}


//===================================
//�`��
//===================================
void    DrawShell()
{
	
	//�J�m���\��
	for (int i = 0; i < SHELL_MAX; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(g_shell[i].pos);

		if (g_shell[i].use == true)
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_shell[i].texno));

		
			//�X�v���C�g�\��
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
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		
		}
	}

}

//===================================
//�X�V
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
//�J�m���\���̂̐擪�|�C���^���擾
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
		//�J�m���̔ԍ����o�^����Ă���J�E���g���グ��
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
		//�J�m���̔ԍ����o�^����Ė��������疢�g�p�̏��ɓo�^����
		if (Cannon[i] == 0)
		{
			Cannon[i] = chipnum;
			break;
		}
	}
	return false;
}
