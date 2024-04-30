//=============================================================================
//game.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================
#include <iostream>

#include "game.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "player.h"
#include "player_effect.h"
#include "block.h"
#include "camera.h"
#include "mapchip.h"
#include "mapscroll.h"
#include "playerCamera.h"
#include "Mapcollision.h"
#include "mapchip.h"
#include "mcgimmick.h"

#include "cannon.h"
#include "shell.h"
#include "UI.h"
#include "photoeffect.h"
#include "timelimit.h"
#include "player_afterimage.h"

#include "io_ex.h"
#include "fade.h"

#include "stage_select.h"
#include "layer.h"
#include "polygon.h"


static	ID3D11ShaderResourceView* g_PauseBGTexture;//�摜1����1�̕ϐ����K�v
static	char* g_PauseBGTextureName = (char*)"data\\texture\\fade_white.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static int g_PauseBGTextureNo = 0;


static	ID3D11ShaderResourceView* g_PauseTexture;//�摜1����1�̕ϐ����K�v
static	char* g_PauseTextureName = (char*)"data\\texture\\pause.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static int g_PauseTextureNo = 0;



//===================================
//�}�N����`
//===================================


//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================

static GAME g_game;




//===================================
//������
//===================================
HRESULT InitGame()
{
	InitCamera();
	g_game.GameUpdateFlag = true;
	g_game.GameCameraFlag = true;
	int st_num = GetStageNum();

	switch (st_num)
	{

	case 0://�X�e�[�W1�]1
		InitMapchip("data\\stage\\�X�e�[�W1-1\\SMC1_1.txt");
		SetLayerMC_01(LAYER_MC_1_1_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 1://�X�e�[�W1�]2
		InitMapchip("data\\stage\\�X�e�[�W1-2\\SMC1_2.txt");
		SetLayerMC_01(LAYER_MC_1_2_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 2://�X�e�[�W1�]3
		InitMapchip("data\\stage\\�X�e�[�W1-3\\SMC1_3.txt");
		SetLayerMC_01(LAYER_MC_1_3_01);
		SetLayerBG(LAYER_BG_01_00, LAYER_BG_01_01, LAYER_BG_01_02, LAYER_BG_01_03);
		SetBGTexture(BG_01);
		PlayBGM(BGM_AREA01);
		break;
	case 3://�X�e�[�W2�]1
		InitMapchip("data\\stage\\�X�e�[�W2-1\\SMC2_1.txt");
		SetLayerMC_01(LAYER_MC_2_1_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 4://�X�e�[�W2�]2
		InitMapchip("data\\stage\\�X�e�[�W2-2\\SMC2_2.txt");
		SetLayerMC_01(LAYER_MC_2_2_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 5://�X�e�[�W2�]3
		InitMapchip("data\\stage\\�X�e�[�W2-3\\SMC2_3.txt");
		SetLayerMC_01(LAYER_MC_2_3_01);
		SetLayerBG(LAYER_BG_02_00, LAYER_BG_02_01, LAYER_BG_02_02, LAYER_BG_02_03);
		SetBGTexture(BG_02);
		PlayBGM(BGM_AREA02);
		break;
	case 6://�X�e�[�W3�]1
		InitMapchip("data\\stage\\�X�e�[�W3-1\\SMC3_1.txt");
		SetLayerMC_01(LAYER_MC_3_1_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);
		PlayBGM(BGM_AREA03);
		break;
	case 7://�X�e�[�W3�]2
		InitMapchip("data\\stage\\�X�e�[�W3-2\\SMC3_2.txt");
		SetLayerMC_01(LAYER_MC_3_2_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);

		PlayBGM(BGM_AREA03);
		break;
	case 8://�X�e�[�W3�]3
		InitMapchip("data\\stage\\�X�e�[�W3-3\\SMC3_3.txt");
		SetLayerMC_01(LAYER_MC_3_3_01);
		SetLayerBG(LAYER_BG_03_00, LAYER_BG_03_01, LAYER_BG_03_02, LAYER_BG_03_03);
		SetBGTexture(BG_03);
		PlayBGM(BGM_AREA03);
		break;
	case 9:
		SetScene(SCENE_TITLE);
		break;
	}

	InitPlayer();

	InitPlayerCamera();

	/*InitBlock();*/

	InitPlayerEffect();
	InitCannon();
	InitShell();

	InitTimeLimit();
	InitUI();

	InitPhotoEffect();
	InitAfterImage();

	InitMcGimmick();

	SetCannon(D3DXVECTOR2(700.0f, 388.0f));
	//SetShell(D3DXVECTOR2(300.0f, 300.0f));

	//texture�̃��[�h
	g_PauseBGTextureNo = LoadTexture(g_PauseBGTextureName);
	if (g_PauseBGTextureNo == -1)
	{//���[�h�G���[
		exit(999);//�����I��
	}


	//texture�̃��[�h
	g_PauseTextureNo = LoadTexture(g_PauseTextureName);
	if (g_PauseTextureNo == -1)
	{//���[�h�G���[
		exit(999);//�����I��
	}
	return S_OK;


}

//===================================
//�I��
//===================================
void    UnInitGame()
{
	StopSoundAll();

	UninitMapchip();
	//UnInitBlock();

	UnInitPlayer();

	UnInitCamera();
	UnInitTimeLimit();

	UnInitAfterImage();
	UnInitPhotoEffect();
	UnInitPlayerEffect();
}


//===================================
//�`��
//===================================
void  DrawGame()
{
	DrawMapchip();

	//�J�����p�[�g���̓A�N�V�����p�[�g�̍X�V�A�`�揈�����s��Ȃ�
	if (NowCameraFlag() == false)
	{
		g_game.GameCameraFlag = false;
		DrawPhotoEffect();
		DrawPlayer();
		DrawCannon();
		DrawShell();
		/*DrawBlock();*/

		DrawAfterImage();
		DrawPlayerEffect();
	}
	else
	{
		g_game.GameCameraFlag = true;
	}
	DrawCamera();
	DrawTimeLimit();
	DrawUI();

	// �|�[�Y��ʕ\��
	if (g_game.GameUpdateFlag == false)
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PauseBGTextureNo));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, D3DXCOLOR(0.0, 0.0, 0.0, 0.3), 0, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_PauseTextureNo));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5, 0, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), 0, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}


}


//===================================
//�X�V
//===================================
void    UpdateGame()
{
	// �|�[�Y��ʂւ̈ڍs
	if (IsButton(START, TRIGGER))
	{
		if (g_game.GameUpdateFlag == true)
		{
			g_game.select_game = 2;
			g_game.GameUpdateFlag = false;
			PlaySE(SE_PAUSE_ON);
		}
		else if (g_game.GameUpdateFlag == false)
		{
			g_game.GameUpdateFlag = true;
			PlaySE(SE_PAUSE_OFF);
		}
	}

	if (g_game.GameUpdateFlag == true)
	{
		UpdateMapchip();

		UpdatePlayerCamera();

		UpdateCamera();
		//�J�����p�[�g���̓A�N�V�����p�[�g�̍X�V�A�`�揈�����s��Ȃ�
		if (NowCameraFlag() == false)
		{

			UpdatePlayer();
			UpdateShell();
			UpdateCannon();
			/*UpdateBlock();*/


			UpdateAfterImage();
			UpdatePlayerEffect();
			UpdatePhotoEffect();
		}
		UpdateTimeLimit();
	}
	else if (g_game.GameUpdateFlag == false)
	{
		if (IsButton(L_RIGHT, TRIGGER))
		{
			if (g_game.select_game <= 1)
			{
				g_game.select_game += 1;
			}
			PlaySE(SE_MOVECURSOR);
		}

		if (IsButton(L_LEFT, TRIGGER))
		{
			if (g_game.select_game >= 1)
			{
				g_game.select_game -= 1;
			}
			PlaySE(SE_MOVECURSOR);
		}


		if (IsButton(A, TRIGGER))
		{
			switch (g_game.select_game)
			{
			case 0:
				SetFade(FADE_OUT_TITLE);
				break;

			case 1:
				SetFade(FADE_OUT_GAME);
				break;

			case 2:
				// �߂�
				g_game.GameUpdateFlag = true;
				break;
			}
			PlaySE(SE_OK);
		}
	}

}

GAME* GetGame()
{
	return &g_game;
}