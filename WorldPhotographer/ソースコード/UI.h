//=============================================================================
// UI.h
// �쐬�ҁF���ؕ����@�쐬���F2022/11/02
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================

#define LIFE_POS_X (80)
#define	LIFE_POS_Y (480)

#define LIFE_SIZE_W (60)
#define	LIFE_SIZE_H (60)

#define TUTORIAL_POS_X (SCREEN_WIDTH * 5/ 6)
#define	TUTORIAL_POS_Y (SCREEN_HEIGHT * 2/7 )

#define TUTORIAL_SIZE_W (SCREEN_WIDTH / 4)
#define	TUTORIAL_SIZE_H (SCREEN_HEIGHT / 3)

#define STAGELOCK_SIZE_W (SCREEN_WIDTH /  5)
#define	STAGELOCK_SIZE_H (SCREEN_HEIGHT / 3)

static	ID3D11ShaderResourceView* g_Texture_Life;//�摜1����1�̕ϐ����K�v
static	char* g_TextureLife = (char*)"data\\texture\\UI_Heart02_64_01-sheet.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_MoveToStageSelection;//��	�ϐ����K�v
static	char* g_TextureMoveToStageSelection = (char*)"data\\texture\\move_stage_selection.PNG";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Manual;//�摜1����1�̕ϐ����K�v
static	char* g_TextureManual = (char*)"data\\texture\\manual.PNG";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


static	ID3D11ShaderResourceView* g_Texture_BackTitel;//�摜1����1�̕ϐ����K�v
static	char* g_TextureBackTitel = (char*)"data\\texture\\back_titel.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Retry;//�摜1����1�̕ϐ����K�v
static	char* g_TextureRetry = (char*)"data\\texture\\retry.PNG";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Back;//�摜1����1�̕ϐ����K�v
static	char* g_TextureBack = (char*)"data\\texture\\back.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_OperateManual;//�摜1����1�̕ϐ����K�v
static	char* g_TextureOperateManual = (char*)"data\\texture\\game_sousa.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_CameraManual;//�摜1����1�̕ϐ����K�v
static	char* g_TextureCameraManual = (char*)"data\\texture\\camera_sousa.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_PauseBottom;//�摜1����1�̕ϐ����K�v
static	char* g_TextureArrowUI = (char*)"data\\texture\\select_arrow.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture_Arrow;//�摜1����1�̕ϐ����K�v
static	char* g_TexturePauseGameButtom = (char*)"data\\texture\\game_pause.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

// �X�e�[�W�Z���N�g���
static	ID3D11ShaderResourceView* g_Texture_StageSelection;//�摜1����1�̕ϐ����K�v
static	char* g_TextureStageSelection = (char*)"data\\texture\\stage_select.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG// �X�e�[�W�Z���N�g���
// �X�e�[�W���b�N
static	ID3D11ShaderResourceView* g_Texture_StageLock;//�摜1����1�̕ϐ����K�v
static	char* g_TextureStageLock = (char*)"data\\texture\\stage_lock.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

// �`���[�g���A���\��
// ���E�ړ��E�W�����v
static	ID3D11ShaderResourceView* g_Texture_Tutorial1;
static	char* g_TextureTutorial1 = (char*)"data\\texture\\tutorial_player_operate.png";
// �J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e
static	ID3D11ShaderResourceView* g_Texture_Tutorial2;
static	char* g_TextureTutorial2 = (char*)"data\\texture\\tutorial_camera.png";

// �v���C���[�Ă��t��
static	ID3D11ShaderResourceView* g_Texture_Tutorial3;
static	char* g_TextureTutorial3 = (char*)"data\\texture\\tutorial_3_player_burn.png";

// �J�����N��
static	ID3D11ShaderResourceView* g_Texture_Tutorial4;
static	char* g_TextureTutorial4 = (char*)"data\\texture\\tutorial_4_launch_camera.png";


struct UI
{
	bool use;		//�\���̗��p���t���O
	bool pushpause;	// �|�[�Y��ʂɂ�����

	D3DXVECTOR2		Size;		//�|���S���̃T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	float texlife;    //�e�N�X�`���C���f�b�N�X
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �^�C�g���E���U���g�E�|�[�Y�E�Q�[���I�[�o�[ ��
	D3DXCOLOR TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ManualColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	float texManual;
	float texMoveToStageSelection;
	float texBackTitel;
	float texRetry;
	float texBack;
	float texOperateManual;
	float texCameraManual;
	float texPauseButtom;
	float texArrow;
	float texStageSelection;
	float texStageLock;

	float texTutorial1;
	float texTutorial2;
	float texTutorial3;
	float texTutorial4;
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitUI();
void    UnInitUI();
void    DrawUI();
void    UpdateUI();



