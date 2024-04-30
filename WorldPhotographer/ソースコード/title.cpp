//=============================================================================
//title.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#include "title.h"
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

static TITLE g_title;

float pattern_num_title = 0;
float yoko_num_title = 10;
float tate_num_title = 6;
int   pattern_size_title = 60;


//===================================
//������
//===================================
HRESULT InitTitle()
{

	g_title.select_title = 0;

	static	ID3D11ShaderResourceView* g_TextureTitle;//�摜1����1�̕ϐ����K�v
	static	char* g_TextureNameTitle = (char*)"data\\texture\\TitleBGSprite.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
	
	static	ID3D11ShaderResourceView* g_TextureTitleLogo;//�摜1����1�̕ϐ����K�v
	static	char* g_TextureNameTitleLogo = (char*)"data\\texture\\world_photographer.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

	g_title.h = SCREEN_HEIGHT;
	g_title.w = SCREEN_WIDTH;
	g_title.texno = LoadTexture(g_TextureNameTitle);
	g_title.texlogo = LoadTexture(g_TextureNameTitleLogo);

	PlayBGM(BGM_TITLE);
	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitTitle()
{
	StopSoundAll();
	//UninitSound();
	//UninitTexture();
}


//===================================
//�`��
//===================================
void    DrawTitle()
{
	// �^�C�g���摜
	{
		{
			pattern_num_title+=0.4;
		}
		if (pattern_num_title >= 30)
		{
			pattern_num_title = 0;
		}
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_title.texno));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, g_title.w, g_title.h, 0, g_title.Color, pattern_num_title, /*tate_num_title / pattern_size_title*/1.0f/7, /*tate_num_title*/1.0f/9, /*pattern_size_title*/7);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
	// �^�C�g�����S
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_title.texlogo));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-50.0f, g_title.w* 7/9, g_title.h*2/9, 0, g_title.Color, 1, 1.0f,1.0f,1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
	
}


//===================================
//�X�V
//===================================
void    UpdateTitle()
{
	if (IsButton(L_DOWN, TRIGGER))
	{
		if (g_title.select_title == 0)
		{
			g_title.select_title += 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(L_UP, TRIGGER))
	{
		if (g_title.select_title == 1)
		{
			g_title.select_title -= 1;
		}
		PlaySE(SE_MOVECURSOR);
	}

	if (IsButton(A, TRIGGER))
	{
		switch (g_title.select_title)
		{
		case 0:
			// �X�e�[�W�Z���N�g
			SetFade(FADE_OUT_STAGESELECT);
			break;

		case 1:
			// �������
			SetScene(SCENE_MANUAL);
			break;
		}
		PlaySE(SE_OK);
	}

	// ���[�h�؂�ւ�
	{
		if (IsButton(L1, PUSH) && IsButton(R1, TRIGGER))
		{
			if (GetStageLockMode() == true)
			{
				SetStageLockMode(false);
				SetStageOpen(8);
			}
			else if (GetStageLockMode() == false)
			{
				SetStageLockMode(true);
				SetStageOpen(0);
			}
		}
	}
}

TITLE* GetTitle()
{
	return &g_title;
}

