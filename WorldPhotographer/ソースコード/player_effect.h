//=============================================================================
//explosion.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/07/11
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define EXPLOSION_SIZE_W (80)
#define	EXPLOSION_SIZE_H (40)
#define EXPLOSION_MAX    (10)
#define EXPLOSION_SPEED  (10.0f)
#define EXPLOSION_ANIME_MAX (7)//�A�j���[�V�����ő吔

static	ID3D11ShaderResourceView* g_TexturePlayerJumpEffect;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNamePlayerJumpEffect = (char*)"data\\texture\\player_jump_effect.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_TexturePlayerLandingEffect;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNamePlayerLandingEffect = (char*)"data\\texture\\player_landing_effect.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct PLAYER_EFFECT
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X
	float m_animeSpeed;
	float pattern_num_explosion;

};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPlayerEffect();
void    UnInitPlayerEffect();
void    DrawPlayerEffect();
void    UpdatePlayerEffect();
PLAYER_EFFECT* GetPlayerEffect(); //BULLET�\���̂̐擪�|�C���^���擾
void SetPlayerJumpEffect(float x, float y, float animeSpeed);
void SetPlayerLandingEffect(float x, float y, float animeSpeed);


