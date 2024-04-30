//=============================================================================
// manual.cpp
// �쐬�ҁF���ؕ����@�쐬���F2023/01/25
//=============================================================================

#include "manual.h"
#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
#include "UI.h"
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

static MANUAL g_manual;

float pattern_num_manual = 0;
float yoko_num_manual = 10;
float tate_num_manual = 6;
int   pattern_size_manual = 60;


//===================================
//������
//===================================
HRESULT InitManual()
{
	g_manual.select_manual = 0;
	g_manual.temp_select_manual = 0;

	g_manual.h = SCREEN_HEIGHT;
	g_manual.w = SCREEN_WIDTH;
	g_manual.texbg = LoadTexture(g_Texture_ManualBG);
	g_manual.texkeyboard = LoadTexture(g_Texture_ManualKeyboard);
	g_manual.texpad = LoadTexture(g_Texture_ManualPad);

	// PlayBGM(BGM_01);
	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitManual()
{
	StopSoundAll();
}


//===================================
//�`��
//===================================
void    DrawManual()
{
	// �w�i�摜
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texbg));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_manual.w, g_manual.h, 0, g_manual.BGColor, 0, 1.0f, 1.0f, 1.0f);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}

	switch (g_manual.select_manual)
	{
	case 0:
	// �p�b�h����摜
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texpad));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH /2, SCREEN_HEIGHT *3/ 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
	break;

	case 1:
	// �L�[�{�[�h����摜
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texkeyboard));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
	break;

	case 2:
		switch (g_manual.temp_select_manual)
		{
		case 0:
			// �p�b�h����摜
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texpad));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;

		case 1:
			// �L�[�{�[�h����摜
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texkeyboard));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 3 / 7, g_manual.w * 9 / 10, g_manual.h * 9 / 10, 0, g_manual.Color, 0, 1.0f, 1.0f, 1.0f);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;
		}
		// ���I���� �e
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_manual.texbg));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_manual.w, g_manual.h, 0, g_manual.ShadowColor, 0, 1.0f, 1.0f, 1.0f);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;
	}
}


//===================================
//�X�V
//===================================
void    UpdateManual()
{
	if (IsButton(L_RIGHT, TRIGGER))
	{
		if (g_manual.select_manual == 0)
		{
			g_manual.select_manual += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_LEFT, TRIGGER))
	{
		if (g_manual.select_manual == 1)
		{
			g_manual.select_manual -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_DOWN, TRIGGER))
	{
		if (g_manual.select_manual <= 1)
		{
			g_manual.temp_select_manual = g_manual.select_manual;
			g_manual.select_manual = 2;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_UP, TRIGGER))
	{
		if (g_manual.select_manual == 2)
		{
			g_manual.select_manual = g_manual.temp_select_manual;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		if (g_manual.select_manual == 2)
		{
			// �X�e�[�W�Z���N�g
			SetFade(FADE_OUT_TITLE);
		}
		PlaySE(SE_OK);
	}
}

MANUAL* GetManual()
{
	return &g_manual;
}

