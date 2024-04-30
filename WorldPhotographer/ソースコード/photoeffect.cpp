//=============================================================================
//photoeffect.cpp
// �쐬�ҁF�L�� ��C�@�쐬���F2022/11/15
//=============================================================================

#include "photoeffect.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
#include "player.h"
#include "photo.h"

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================


static PHOTOEFFECT g_photoeffect[PHOTOEFFECT_MAX];

int   pattern_size_photoeffect = 8;

PLAYER* p_Player = GetPlayer();
PHOTO* p_Photo = GetPhotoPut();

//===================================
//������
//===================================
HRESULT InitPhotoEffect()
{

	for (int i = 0; i <PHOTOEFFECT_MAX; i++)
	{
		//�����̏�����
		g_photoeffect[i].pos.x = 0;
		g_photoeffect[i].pos.y = 0;
				
		g_photoeffect[i].w =PHOTOEFFECT_SIZE_W;
		g_photoeffect[i].h =PHOTOEFFECT_SIZE_H;
				
		g_photoeffect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_photoeffect[i].rot = 0.0f;
				
		g_photoeffect[i].use = false;

		g_photoeffect[i].pattern_num_explosion = 0;
				
		g_photoeffect[i].texno = LoadTexture(g_TextureNamePhotoEffect);
	}
	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitPhotoEffect()
{

}


//===================================
//�`��
//===================================
void    DrawPhotoEffect()
{
	//�v���C���[�\��
	{

		for (int i = 0; i < PHOTOEFFECT_MAX; i++)
		{
			if (g_photoeffect[i].use)
			{
				//�e�N�X�`���̕\��
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photoeffect[i].texno));

				//�X�v���C�g�\��
				//�v���C���[�̉E���Ɏʐ^��ݒu����ꍇ(�E����)
				if (p_Player->pos.x <= p_Photo->pos.x)
				{
					DrawSpriteColorRotation(g_photoeffect[i].pos.x, g_photoeffect[i].pos.y, g_photoeffect[i].w, g_photoeffect[i].h, g_photoeffect[i].rot, g_photoeffect[i].Color,
						(int)g_photoeffect[i].pattern_num_explosion, 1.0 / pattern_size_photoeffect, 1.0 / 2.0, pattern_size_photoeffect);
				}

				//�v���C���[�̍����Ɏʐ^��ݒu����ꍇ(������)
				if (p_Player->pos.x >= p_Photo->pos.x)
				{
					DrawSpriteColorRotation(g_photoeffect[i].pos.x, g_photoeffect[i].pos.y, g_photoeffect[i].w, g_photoeffect[i].h, g_photoeffect[i].rot, g_photoeffect[i].Color,
						(int)g_photoeffect[i].pattern_num_explosion + 8, 1.0 / pattern_size_photoeffect, 1.0 / 2.0, pattern_size_photoeffect);
				}
			}
		}
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
}


//===================================
//�X�V
//===================================
void    UpdatePhotoEffect()
{
	for (int i = 0; i < PHOTOEFFECT_MAX; i++)
	{
		if (g_photoeffect[i].use)
		{
			g_photoeffect[i].pattern_num_explosion += g_photoeffect[i].m_animeSpeed;
			if((int)g_photoeffect[i].pattern_num_explosion > PHOTOEFFECT_ANIME_MAX)
			{
				g_photoeffect[i].use = false;
				g_photoeffect[i].pattern_num_explosion = 0.0f;
			}
		}
	}

}

//===================================
//explosion�\���̂̐擪�|�C���^���擾
//===================================
PHOTOEFFECT* GetPhotoEffect()
{
	return g_photoeffect;
}

//==================================
//�Z�b�g�o���b�g
//==================================

void SetPhotoEffect(float x,float y,float animeSpeed)
{
	for (int i = 0; i <PHOTOEFFECT_MAX; i++)
	{
		if (!g_photoeffect[i].use)
		{
			//�o���b�g�̏�����
			g_photoeffect[i].pos.x = x;
			g_photoeffect[i].pos.y = y;

			g_photoeffect[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_photoeffect[i].rot = 0.0f;

			g_photoeffect[i].m_animeSpeed = animeSpeed;
			g_photoeffect[i].use = true;
			return;
		}
	}
}
