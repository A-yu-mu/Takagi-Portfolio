//=============================================================================
// gameOver.cpp
// �쐬�ҁF���ؕ����@�쐬���F2022/12/04
//=============================================================================

#include "gameOver.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "io_ex.h"
#include "fade.h"
//===================================
//�}�N����`
//===================================


//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================

static GameOver g_gameover;

//===================================
//������
//===================================
HRESULT InitGameOver()
{
	g_gameover.select_gameover = 0;
	g_gameover.pos.x = 0;
	g_gameover.pos.y = 0;
	g_gameover.Size.x = SCREEN_WIDTH;
	g_gameover.Size.y = SCREEN_HEIGHT;

	g_gameover.texGameOver = LoadTexture(g_TextureGameOver);
	g_gameover.texGameOverBG = LoadTexture(g_TextureGameOverBG);
	PlaySE(SE_BOOING);

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitGameOver()
{
	//�S�T�E���h�̒�~
	StopSoundAll();	
}


//===================================
//�`��
//===================================
void    DrawGameOver()
{
	// GameOver�w�i
	{
		// �e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gameover.texGameOverBG));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_gameover.Size.x, g_gameover.Size.y, 0, g_gameover.BGColor, 0, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}

	// GameOver
	{
		// �e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gameover.texGameOver));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT *2/ 5, g_gameover.Size.x*6/7, g_gameover.Size.y/3, 0, g_gameover.Color, 0, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
}


//===================================
//�X�V
//===================================
void    UpdateGameOver()
{
	if (IsButton(L_RIGHT, TRIGGER))
	{
		if (g_gameover.select_gameover <= 1)
		{
			g_gameover.select_gameover += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_LEFT, TRIGGER))
	{
		if (g_gameover.select_gameover >= 1)
		{
			g_gameover.select_gameover -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		switch (g_gameover.select_gameover)
		{
		case 0:
			SetFade(FADE_OUT_TITLE);
			break;

		case 1:
			SetFade(FADE_OUT_GAME);
			break;

		case 2:
			// �X�e�[�W�Z���N�g
			SetFade(FADE_OUT_STAGESELECT);
			break;
		}
		PlaySE(SE_OK);
	}
}

GameOver* GetGameOver()
{
	return &g_gameover;
}
