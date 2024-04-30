//=============================================================================
//photo.h
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//�T�C�Y���}�b�v�`�b�v�̃T�C�Y�ɘA��������
#include "mapchip.h"
//====================================
//�}�N����`
//====================================
#define PHOTO_MAPCHIP_WIDTH_NUM (6)		//�ʐ^�̉��̃}�b�v�`�b�v�̌�
#define PHOTO_MAPCHIP_HEIGHT_NUM (6)		//�ʐ^�̉��̃}�b�v�`�b�v�̌�
#define PHOTO_MAPCHIP_NUM (PHOTO_MAPCHIP_WIDTH_NUM * PHOTO_MAPCHIP_HEIGHT_NUM)			//�ʐ^�̏c���̃}�b�v�`�b�v�̍��v��

#define PHOTO_SIZE_W (MAPCHIP_WIDTH * PHOTO_MAPCHIP_WIDTH_NUM)
#define	PHOTO_SIZE_H (MAPCHIP_HEIGHT * PHOTO_MAPCHIP_WIDTH_NUM)

static	ID3D11ShaderResourceView* g_PhotoTexture;//�摜1����1�̕ϐ����K�v
static	char* g_PhotoTextureName = (char*)"data\\texture\\TSM.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct PHOTO
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 old_pos;//���̃��C���[�̕\�����W
	D3DXVECTOR2 pos;//���݂̕\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(0.97f, 0.5f, 0.44f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X

		//�}�b�v�`�b�v��������
	CHIP chip[PHOTO_MAPCHIP_NUM];		//�c���̍��v�����̃`�b�v��������

};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPhoto();
void    UnInitPhoto();
void    DrawPhoto();
void    UpdatePhoto();

//�t�H�g�ɂ̓X�g�b�N�ƃv�b�g�̓��ނ�����̂�
//�Q�b�^�[�𕪂���
PHOTO*	GetPhotoStock(); //PHOTO�\���̂̐擪�|�C���^���擾
PHOTO*	GetPhotoPut(); //PHOTO�\���̂̐擪�|�C���^���擾

//�Z�b�^�[
void	SetPhotoStock(float w, float h, D3DXVECTOR2 pos, D3DXCOLOR Color, float texno, CHIP* chip);
void	SetPhotoPut(float w, float h, D3DXVECTOR2 old_pos, D3DXCOLOR Color, float texno, D3DXVECTOR2 pos, CHIP* chip);
