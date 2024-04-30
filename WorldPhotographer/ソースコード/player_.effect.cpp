//=============================================================================
//explosion.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/07/11
//=============================================================================

#include "player_effect.h"
#include "sprite.h"
#include "texture.h"

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================
// 
//===================================
//�O���[�o���ϐ�
//===================================


static PLAYER_EFFECT g_player_jump_effect;
static PLAYER_EFFECT g_player_landing_effect[EXPLOSION_MAX];

int   pattern_size_explosion = 8;


//===================================
//������
//===================================
HRESULT InitPlayerEffect()
{

	//�v���C���[�W�����v���̃G�t�F�N�g������
	g_player_jump_effect.pos.x = 0;
	g_player_jump_effect.pos.y = 0;

	g_player_jump_effect.w = EXPLOSION_SIZE_W;
	g_player_jump_effect.h = EXPLOSION_SIZE_H;

	g_player_jump_effect.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_player_jump_effect.rot = 0.0f;

	g_player_jump_effect.use = false;

	g_player_jump_effect.pattern_num_explosion = 0;

	g_player_jump_effect.texno = LoadTexture(g_TextureNamePlayerJumpEffect);

	//�v���C���[���n���̃G�t�F�N�g������
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_player_landing_effect[i].pos.x = 0;
		g_player_landing_effect[i].pos.y = 0;

		g_player_landing_effect[i].w = EXPLOSION_SIZE_W;
		g_player_landing_effect[i].h = EXPLOSION_SIZE_H;

		g_player_landing_effect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player_landing_effect[i].rot = 0.0f;

		g_player_landing_effect[i].use = false;

		g_player_landing_effect[i].pattern_num_explosion = 0;

		g_player_landing_effect[i].texno = LoadTexture(g_TextureNamePlayerLandingEffect);
	}

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitPlayerEffect()
{

}


//===================================
//�`��
//===================================
void    DrawPlayerEffect()
{
	//�v���C���[�\��
	if (g_player_jump_effect.use)
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_player_jump_effect.texno));

		//�X�v���C�g�\��

		DrawSpriteColorRotation(g_player_jump_effect.pos.x, g_player_jump_effect.pos.y, g_player_jump_effect.w, g_player_jump_effect.h, g_player_jump_effect.rot, g_player_jump_effect.Color,
			(int)g_player_jump_effect.pattern_num_explosion, 1.0 / pattern_size_explosion, 1.0 / 1.0, pattern_size_explosion);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_player_landing_effect[i].use)
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_player_landing_effect[i].texno));

			//�X�v���C�g�\��

			DrawSpriteColorRotation(g_player_landing_effect[i].pos.x, g_player_landing_effect[i].pos.y, g_player_landing_effect[i].w, g_player_landing_effect[i].h, g_player_landing_effect[i].rot, g_player_landing_effect[i].Color,
				(int)g_player_landing_effect[i].pattern_num_explosion, 1.0 / pattern_size_explosion, 1.0 / 1.0, pattern_size_explosion);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
	}
}


//===================================
//�X�V
//===================================
void    UpdatePlayerEffect()
{

	if (g_player_jump_effect.use)
	{
		g_player_jump_effect.pattern_num_explosion += g_player_jump_effect.m_animeSpeed;
		if ((int)g_player_jump_effect.pattern_num_explosion > EXPLOSION_ANIME_MAX)
		{
			g_player_jump_effect.use = false;
			g_player_jump_effect.pattern_num_explosion = 0.0f;
		}
	}
	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_player_landing_effect[i].use)
		{
			g_player_landing_effect[i].pattern_num_explosion += g_player_landing_effect[i].m_animeSpeed;
			if ((int)g_player_landing_effect[i].pattern_num_explosion > EXPLOSION_ANIME_MAX)
			{
				g_player_landing_effect[i].use = false;
				g_player_landing_effect[i].pattern_num_explosion = 0.0f;
			}
		}
	}
}

//===================================
//explosion�\���̂̐擪�|�C���^���擾
//===================================
PLAYER_EFFECT* GetPlayerEffect()
{
	return &g_player_jump_effect;
}

//==================================
//�Z�b�g�o���b�g
//==================================

void SetPlayerJumpEffect(float x,float y,float animeSpeed)
{

	if (!g_player_jump_effect.use)
	{
		//�o���b�g�̏�����
		g_player_jump_effect.pos.x = x;
		g_player_jump_effect.pos.y = (y + 20.0f);

		g_player_jump_effect.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_player_jump_effect.rot = 0.0f;

		g_player_jump_effect.m_animeSpeed = animeSpeed;
		g_player_jump_effect.use = true;
		return;

	}
}

void SetPlayerLandingEffect(float x, float y, float animeSpeed)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_player_landing_effect[i].use)
		{
			//�o���b�g�̏�����
			g_player_landing_effect[i].pos.x = x;
			g_player_landing_effect[i].pos.y = (y + 20.0f);

			g_player_landing_effect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_player_landing_effect[i].rot = 0.0f;

			g_player_landing_effect[i].m_animeSpeed = animeSpeed;
			g_player_landing_effect[i].use = true;
			return;

		}
	}
}