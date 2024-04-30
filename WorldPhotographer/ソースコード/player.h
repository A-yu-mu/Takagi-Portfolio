//=============================================================================
//player.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"


//====================================
//�}�N����`
//====================================
#define PLAYER_SIZE_W (60)
#define	PLAYER_SIZE_H (60)
#define FRAME_RATE (60)	// �t���[�����[�g
const int TEX_MAX = 4;

static	ID3D11ShaderResourceView* g_Texture;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName = (char*)"data\\texture\\player_Idling.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture2;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName2 = (char*)"data\\texture\\player_walk.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture3;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName3 = (char*)"data\\texture\\player_jump.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_Texture4;//�摜1����1�̕ϐ����K�v
static	char* g_TextureName4 = (char*)"data\\texture\\player_mode.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG


struct PLAYER
{
	D3DXVECTOR2		size;		//�|���S���̃T�C�Y			
	//float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	D3DXVECTOR2 oldpos;//�X�V�O���W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno[TEX_MAX];    //�e�N�X�`���C���f�b�N�X
	float pattern_num;

	int texSelect;

	float move;
	float player_ysp;
	int life = 0;			//�v���C���[�̃��C�t�|�C���g
	int count;

	bool use;		//�\���̗��p���t���O

	int texLorR;


	bool isDamage;
	bool invincible;
	bool DeathFlag;			//�v���C���[�����񂾂Ƃ���true�ɂ��鎀�S�t���O

	bool controlrock;
	bool PressRight;
	bool PressLeft;

	//�v���C���[�̏�Ԏg�p�t���O
	bool PlayerWalk;	//����
	bool PlayerCamera;	//�J�������[�h�ڍs��
	bool PlayerGoal;	//�S�[�����̃��[�V����

	bool PlayerJumpEffect;		//�W�����v�G�t�F�N�g�g�p�t���O
	bool PlayerLandingEffect;	//���n�G�t�F�N�g�g�p�t���O

	bool keyuse;
	bool keyuse_next;//�����\�肩�ǂ����̃t���O(�����������ăS�����I)
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPlayer();
void    UnInitPlayer();
void    DrawPlayer();
void    UpdatePlayer();
PLAYER* GetPlayer(); //PLAYER�\���̂̐擪�|�C���^���擾
void SetaNum(int num);

int		GerLR();		//�v���C���[�̌����Ă������Ԃ�

