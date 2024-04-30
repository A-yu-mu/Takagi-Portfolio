//=============================================================================
//photoreticle.cpp
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#include "photoreticle.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "camera.h"
#include "layer.h"
#include "photo.h"
#include "playerCamera.h"

#include "fade.h"
#include "player.h"
#include "io_ex.h"

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�                 
//===================================


static PHOTORETICLE g_photoreticle;
//===================================
//������
//===================================
HRESULT InitPhotoreticle()
{


	//�J�����̕W���̏�����
	g_photoreticle.pos.x = SCREEN_WIDTH / 2;
	g_photoreticle.pos.y = SCREEN_HEIGHT / 2;

	g_photoreticle.w = PHOTORETICLE_SIZE_W;
	g_photoreticle.h = PHOTORETICLE_SIZE_H;

	g_photoreticle.rot = 0.0f;
	g_photoreticle.use = true;
	g_photoreticle.texno = LoadTexture(g_PhotoreticleTextureName);


	return S_OK;
}


//===================================
//�I��
//===================================
void    UnInitPhotoreticle()
{

}


//===================================
//�`��
//===================================
void    DrawPhotoreticle()
{

	//�J�����\��
	if (g_photoreticle.use == true)
	{
		////���C���[���猻�݂�texno���擾
		//LAYER* p_layer = GetLayer();
		//
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_layer->texno));

		//DrawSpritePhoto(
		//	g_photoreticle.pos.x,
		//	g_photoreticle.pos.y,
		//	g_photoreticle.w,
		//	g_photoreticle.h,
		//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		//	g_photoreticle.pos
		//);

		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photoreticle.texno));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			g_photoreticle.pos.x,
			g_photoreticle.pos.y,
			g_photoreticle.w,
			g_photoreticle.h,
			g_photoreticle.rot,
			g_photoreticle.Color,
			1,
			1,
			1,
			1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

	}


}


//===================================
//�X�V
//===================================
void    UpdatePhotoreticle()
{
	//�L�[�{�[�h�̓���
	if (IsButton(L_UP, TRIGGER))
	{

		g_photoreticle.pos.y -= MAPCHIP_HEIGHT;
		if (g_photoreticle.pos.y - MAPCHIP_HEIGHT * 3 <= 0)
		{
			g_photoreticle.pos.y = MAPCHIP_HEIGHT * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	else if (IsButton(L_DOWN, TRIGGER))
	{

		g_photoreticle.pos.y += MAPCHIP_HEIGHT;
		if (g_photoreticle.pos.y + MAPCHIP_HEIGHT * 3 >= SCREEN_HEIGHT)
		{
			g_photoreticle.pos.y = SCREEN_HEIGHT - MAPCHIP_HEIGHT * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}

	if (IsButton(L_RIGHT, TRIGGER))
	{
		//������Ă���Ԃ̏���
		g_photoreticle.pos.x += MAPCHIP_WIDTH;
		if (g_photoreticle.pos.x + MAPCHIP_WIDTH * 3 >= SCREEN_WIDTH)
		{
			g_photoreticle.pos.x = SCREEN_WIDTH - MAPCHIP_WIDTH * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	else if (IsButton(L_LEFT, TRIGGER))
	{

		g_photoreticle.pos.x -= MAPCHIP_WIDTH;
		if (g_photoreticle.pos.x - MAPCHIP_WIDTH * 3 <= 0)
		{
			g_photoreticle.pos.x = MAPCHIP_WIDTH * 3;
		}
		PlaySE(SE_PHOTORETI_MOVE);
	}
	//�L�[�{�[�h��trigger����
	if (IsButton(R1, TRIGGER) && GetFadeStatus() == FADE_NONE)//r1
	{
		
	////�L�[�{�[�h��trigger����
	//if ((GetKeyboardTrigger(DIK_V)|| IsMouseLeftTriggered())//V�L�[ �������� ���N���b�N
	//	&& GetFadeStatus() == FADE_NONE)

		PlaySE(SE_SHUTTER);
		//���C���[���B���󋵂Ȃ�B��
		if (GetLayerCanGet() == true)
		{
			//���C���[�̏����擾
			LAYER* p_layer = GetLayer();

			//�v�Z���ăZ�b�g�X�g�b�N�ɓn���}�b�v�`�b�v�������߂�
			//�W���̍��オ�ǂ��̃}�b�v�`�b�v���v�Z����
			int chip_x = g_photoreticle.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
			int chip_y = g_photoreticle.pos.y / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
			//����̃`�b�v���珇�ɏ����i�[���Ă���
			CHIP chip_stock[PHOTO_MAPCHIP_NUM];
			int j = 0;
			for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
			{
				for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
				{
					chip_stock[j] = p_layer->chip[chip_x + x + ((LAYER_CHIP_NUM_WIDTH * (chip_y + y)))];
					j++;
				}
			}

			//���݂̃��C���[texno�ƃ��e�B�N���ƃ}�b�v�`�b�v���X�g�b�N�ɃZ�b�g
			SetPhotoStock(
				g_photoreticle.w,
				g_photoreticle.h,
				g_photoreticle.pos,
				D3DXCOLOR(p_layer->Color.r, p_layer->Color.g, p_layer->Color.b, 0.25f),
				p_layer->texno,
				chip_stock
			);
		}
		PLAYER* p_player = GetPlayer();
		//�J�����p�[�g�̏I��
		SetFade(FADE_OUT_NORMAL);
		SetaNum(0);
		p_player->PlayerCamera = false;
		

	}

}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
PHOTORETICLE* GetPhotoreticle()
{
	return &g_photoreticle;
}


