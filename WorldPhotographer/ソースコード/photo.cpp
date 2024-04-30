//=============================================================================
//photoreticle.cpp
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#include "photo.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "player.h"
#include "layer.h"

#include "mapchip.h"

#include "playerCamera.h"

#include "photoeffect.h"

#include "photoreticle.h"

#include "fade.h"
#include "camera.h"
#include "io_ex.h"
//===================================
//�}�N����`
//===================================
#define SET_POSITION (D3DXVECTOR2(150.0f, 0.0f))

#define UI_PHOTO_X (260)
#define UI_PHOTO_Y (480)
#define UI_PHOTO_SIZE (60)

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================

static PHOTO g_photo_stock;
static PHOTO g_photo_put;
int g_photo_reset[PHOTO_MAPCHIP_NUM];
bool g_photo_reset_flag;

int bg;//UI�p��

//===================================
//������
//===================================
HRESULT InitPhoto()
{
	//�X�g�b�N�t�H�g�̏�����
	g_photo_stock.old_pos.x = g_photo_stock.pos.x = SCREEN_WIDTH / 2;
	g_photo_stock.old_pos.y = g_photo_stock.pos.y = SCREEN_HEIGHT / 2;

	g_photo_stock.w = PHOTO_SIZE_W;
	g_photo_stock.h = PHOTO_SIZE_H;

	g_photo_stock.rot = 0.0f;
	g_photo_stock.use = false;
	g_photo_stock.texno = LoadTexture(g_PhotoTextureName);

	//�}�b�v�`�b�v�̏�����
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_stock.chip[i].pos.x = 0;
		g_photo_stock.chip[i].pos.y = 0;

		g_photo_stock.chip[i].size.x = MAPCHIP_WIDTH;
		g_photo_stock.chip[i].size.y = MAPCHIP_HEIGHT;

		g_photo_stock.chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_photo_stock.chip[i].type = CHIP_TYPE::TYPE_1;
		g_photo_stock.chip[i].texno = LoadTexture((char*)"data\\texture\\chip1.png");

		g_photo_stock.chip[i].use = true;
		g_photo_stock.chip[i].collision = false;
	}
	//�v�b�g�t�H�g�̏�����
	g_photo_put.pos.x = SCREEN_WIDTH / 2;
	g_photo_put.pos.y = SCREEN_HEIGHT / 2;
			
	g_photo_put.w = PHOTO_SIZE_W;
	g_photo_put.h = PHOTO_SIZE_H;
			
	g_photo_put.rot = 0.0f;
	g_photo_put.use = false;
	g_photo_put.texno = LoadTexture(g_PhotoTextureName);

	//�}�b�v�`�b�v�̏�����
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_put.chip[i].pos.x = 0;
		g_photo_put.chip[i].pos.y = 0;

		g_photo_put.chip[i].size.x = MAPCHIP_WIDTH;
		g_photo_put.chip[i].size.y = MAPCHIP_HEIGHT;

		g_photo_put.chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_photo_put.chip[i].type = CHIP_TYPE::TYPE_1;
		g_photo_put.chip[i].texno = LoadTexture((char*)"data\\texture\\chip1.png");

		g_photo_put.chip[i].use = true;
		g_photo_put.chip[i].collision = false;
	}

	
	//�}�b�v�`�b�v�̏�����
	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_reset[i] = 0;
	}
	g_photo_reset_flag = false;

	bg = LoadTexture((char*)"data\\texture\\fade_white.png");

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitPhoto()
{

}


//===================================
//�`��
//===================================
void    DrawPhoto()
{

	//UI�p�̘g 
	//�e�N�X�`���̕\��
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
	//�X�v���C�g�\��
	DrawSpriteColorRotation(
		UI_PHOTO_X + UI_PHOTO_SIZE / 2, UI_PHOTO_Y,
		UI_PHOTO_SIZE * 2, UI_PHOTO_SIZE,
		g_photo_put.rot, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f),//�Z�s�A�����
		1, 1, 1, 1);

	//�X�g�b�N�t�H�g�\��
	if (g_photo_stock.use == true)
	{
		//�����Ă���UI�\��
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			UI_PHOTO_X, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_stock.rot, D3DXCOLOR(0.76f, 0.54f, 0.17f, 1.0f),//�Z�s�A�Â�
			1, 1, 1, 1);
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_stock.texno));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			UI_PHOTO_X, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, 1, 1);


		//�W���̃e�N�X�`�����g��
		PHOTORETICLE* p_reti = GetPhotoreticle();
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

		//�ݒu�\���ʒu�̃X�v���C�g�\��
		PLAYER* p_player = GetPlayer();
		D3DXVECTOR2 scrpos = p_player->pos;
		DrawSpriteColorRotation(
			scrpos.x + SET_POSITION.x * GerLR(),
			scrpos.y + SET_POSITION.y,
			g_photo_stock.w,
			g_photo_stock.h,
			g_photo_stock.rot,
			D3DXCOLOR(g_photo_stock.Color.r, g_photo_stock.Color.g, g_photo_stock.Color.b, 0.7f),
			1,
			1,
			1,
			1);
		{//�ݒu�\���ʒu�̃X�v���C�g�\��(�Ă��̂Q�J�N�J�N�o�[�W����)
			// PLAYERCAMERA* p_playercamera = GetPlayerCamera();
			////�؂�̂������ɐݒu����ׂɌv�Z����
			//scrpos = D3DXVECTOR2(((int)(scrpos.x / MAPCHIP_WIDTH)) * MAPCHIP_WIDTH,
			//	((int)(scrpos.y / MAPCHIP_HEIGHT)) * MAPCHIP_HEIGHT);
			////�X�N���[�����̍������v�Z���đ���������
			//D3DXVECTOR2 gap;
			//gap.x = ((int)(p_playercamera->pos.x)) % (int)MAPCHIP_WIDTH;
			//gap.y = ((int)(p_playercamera->pos.y)) % (int)MAPCHIP_HEIGHT;
			//if (gap.x >= MAPCHIP_WIDTH / 2)
			//{
			//	gap.x *= -1.0f;
			//}
			//if (gap.y >= MAPCHIP_HEIGHT / 2)
			//{
			//	gap.y *= -1.0f;
			//}
			//scrpos += gap;

			//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_stock.texno));

			//DrawSpritePhoto(
			//	g_photo_stock.old_pos.x,
			//	g_photo_stock.old_pos.y,
			//	g_photo_stock.w,
			//	g_photo_stock.h,
			//	D3DXCOLOR(g_photo_stock.Color.r, g_photo_stock.Color.g, g_photo_stock.Color.b, 0.1f),
			//	scrpos + SET_POSITION
			//);
		}
		
	}
	//�v�b�g�t�H�g�\��
	if (g_photo_put.use == true)
	{
		//�\���Ă���UI
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(bg));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_put.rot, D3DXCOLOR(0.96f, 0.73f, 0.50f, 1.0f),//�Z�s�A�����
			1, 1, 1, 1);
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_put.texno));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
			UI_PHOTO_SIZE, UI_PHOTO_SIZE,
			g_photo_put.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1, 1, 1, 1);

		//���ۂɂ����Ă���ʐ^
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_photo_put.texno));

		DrawSpritePhoto(
			g_photo_put.old_pos.x,
			g_photo_put.old_pos.y,
			g_photo_put.w,
			g_photo_put.h,
			g_photo_put.Color,
			ScreenPos(g_photo_put.pos)
		);

	}
	//UI�p�̘g 
	//�W���̃e�N�X�`�����g��
	PHOTORETICLE* p_reti = GetPhotoreticle();

	//�e�N�X�`���̕\��
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

	//�X�v���C�g�\��
	DrawSpriteColorRotation(
		UI_PHOTO_X, UI_PHOTO_Y,
		UI_PHOTO_SIZE, UI_PHOTO_SIZE,
		g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1, 1, 1, 1);

	//�e�N�X�`���̕\��
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(p_reti->texno));

	//�X�v���C�g�\��
	DrawSpriteColorRotation(
		UI_PHOTO_X + UI_PHOTO_SIZE, UI_PHOTO_Y,
		UI_PHOTO_SIZE, UI_PHOTO_SIZE,
		g_photo_stock.rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		1, 1, 1, 1);

}


//===================================
//�X�V
//===================================
void    UpdatePhoto()
{
	//�L�[�{�[�h��trigger����

	if (IsButton(R1, TRIGGER) && GetFadeStatus() == FADE_NONE
		&& NowCameraFlag() == false)//V�L�[�ƃt�F�[�h�������Ă��Ȃ���

	{
		//�X�g�b�N�����鎞�̏���
		if (g_photo_stock.use == true && g_photo_put.use == false)
		{
			PLAYER* p_player = GetPlayer();
			PLAYERCAMERA* p_playercamera = GetPlayerCamera();

			//�X�N���[���̈ړ������v�Z����
			D3DXVECTOR2 scrpos = p_player->pos;
			scrpos.x += (p_playercamera->pos.x - SCREEN_WIDTH / 2);
			scrpos.y += (p_playercamera->pos.y - SCREEN_HEIGHT / 2);
			//���݂̃X�g�b�N���v�b�g�ɃZ�b�g
			SetPhotoPut(
				g_photo_stock.w,
				g_photo_stock.h,
				g_photo_stock.old_pos,
				g_photo_stock.Color,
				g_photo_stock.texno,
				//�؂�̂������ɐݒu����ׂɌv�Z����
				D3DXVECTOR2(((int)(scrpos.x / MAPCHIP_WIDTH)) * MAPCHIP_WIDTH,
					((int)(scrpos.y / MAPCHIP_HEIGHT)) * MAPCHIP_HEIGHT)
				 + SET_POSITION * GerLR(),
				g_photo_stock.chip
			);
			

			//�ʐ^�ݒu�G�t�F�N�g
			SetPhotoEffect(p_player->pos.x + 80.0f * GerLR(), p_player->pos.y, 0.2f);
			

			PlaySE(SE_PHOTO_ON);
			

			//�X�g�b�N��false�ɂ���
			g_photo_stock.use = false;
		}
		//�v�b�g�����鎞�̏���
		else if (g_photo_put.use == true)
		{
			//�v�b�g��false�ɂ���
			g_photo_put.use = false;
			PlaySE(SE_PHOTO_OFF);

		}

	}

	//�v�b�g�t�H�g�̏������݂̃}�b�v�`�b�v�ɔ��f����
	//�}�b�v�`�b�v�̏����擾
	CHIP* p_chip = GetChip();
	int* p_mapChipList;
	//int p_reset_chip[PHOTO_MAPCHIP_NUM];


	//���C���[�̃}�b�v�`�b�v���v�b�g�t�H�g�ŏ㏑������
	if (g_photo_put.use == true)
	{
		int chip_x = g_photo_put.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
		int chip_y = g_photo_put.pos.y / MAPCHIP_HEIGHT - (PHOTO_MAPCHIP_HEIGHT_NUM / 2);

		int j = 0;
		PLAYER* p_player = GetPlayer();
		for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
		{
			for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
			{
				//�J�M�t���O���������玞�̓J�M���Z�b�g�t�H�g�������
				if (p_player->keyuse == true && (int)g_photo_put.chip[j].type == 13)
				{
					g_photo_put.chip[j].type = (CHIP_TYPE)0;
				}
				//����t����}�b�v�`�b�v��0�̎��͏��������Ȃ�
				if ((int)g_photo_put.chip[j].type != 0)
				{
					p_mapChipList = GetMapChipList(chip_y + y, chip_x + x);
					//���Z�b�g���܂��������
					if (g_photo_reset_flag == false)
					{
						g_photo_reset[j] = *p_mapChipList;
					}
					//����t����悪0�ȊO�̎������������Ȃ�
					if (*p_mapChipList == 0)
					{
						*p_mapChipList = (int)g_photo_put.chip[j].type;
					}

				}
				j++;
			}
		}
		//���Z�b�g��true�ɂ���
		g_photo_reset_flag = true;

	}

	//���C���[�̃}�b�v�`�b�v�����Z�b�g�t�H�g�ŏ㏑������
	if (g_photo_reset_flag == true && g_photo_put.use == false)
	{
		int chip_x = g_photo_put.pos.x / MAPCHIP_WIDTH - (PHOTO_MAPCHIP_WIDTH_NUM / 2);
		int chip_y = g_photo_put.pos.y / MAPCHIP_HEIGHT - (PHOTO_MAPCHIP_HEIGHT_NUM / 2);

		int j = 0;
		for (int y = 0; y < PHOTO_MAPCHIP_HEIGHT_NUM; y++)
		{
			for (int x = 0; x < PHOTO_MAPCHIP_WIDTH_NUM; x++)
			{
				//����t����}�b�v�`�b�v��0�̎��͏��������Ȃ�
				if ((int)g_photo_put.chip[j].type != 0)
				{
					p_mapChipList = GetMapChipList(chip_y + y, chip_x + x);
					
					*p_mapChipList = g_photo_reset[j];

				}
				j++;
			}
		}
		g_photo_reset_flag = false;
	}


	
}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
PHOTO* GetPhotoStock()
{
	return &g_photo_stock;
}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
PHOTO* GetPhotoPut()
{
	return &g_photo_put;
}

//===================================
//�X�g�b�N�̃Z�b�^�[
//===================================
void SetPhotoStock(float w, float h, D3DXVECTOR2 pos, D3DXCOLOR Color, float texno, CHIP* chip)
{
	g_photo_stock.old_pos.x = pos.x;
	g_photo_stock.old_pos.y = pos.y;

	g_photo_stock.w = w;
	g_photo_stock.h = h;

	g_photo_stock.Color = Color;

	g_photo_stock.use = true;
	g_photo_stock.texno = texno;

	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_stock.chip[i] = chip[i];
	}
}

//===================================
//�v�b�g�̃Z�b�^�[
//===================================
void SetPhotoPut(float w, float h, D3DXVECTOR2 old_pos, D3DXCOLOR Color, float texno, D3DXVECTOR2 pos, CHIP* chip)
{
	g_photo_put.old_pos.x = old_pos.x;
	g_photo_put.old_pos.y = old_pos.y;

	g_photo_put.w = w;
	g_photo_put.h = h;

	g_photo_put.Color = Color;

	g_photo_put.use = true;
	g_photo_put.texno = texno;

	g_photo_put.pos.x = pos.x;
	g_photo_put.pos.y = pos.y;

	for (int i = 0; i < PHOTO_MAPCHIP_NUM; i++)
	{
		g_photo_put.chip[i] = chip[i];
	}
}

