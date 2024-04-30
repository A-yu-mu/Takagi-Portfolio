#pragma once

#include "main.h"
#include "renderer.h"

//====================================
//�}�N����`
//====================================

#define PINTO_MOVE_01	(1.0f)		//�s���g�̈�x�ɓ�������
#define PINTO_MOVE_02	(1.0f)		//�s���g�̈�x�ɓ�������
#define PINTO_OKLINE	(10.0f)		//�s���g�������Ă��锻��ɂ��鋖�e�͈�


static	ID3D11ShaderResourceView* g_PintoTexture;//�摜1����1�̕ϐ����K�v
static	char* g_PintoTextureName1 = (char*)"data\\texture\\UI_Focus01.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_PintoTextureName2 = (char*)"data\\texture\\UI_Focus02.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct PINTO
{
	bool use;			//�\���̗��p���t���O
	float maxpos;		//�s���g�̍ő�l
	float nowpos;		//�s���g�̌��݈ʒu
	float change1pos;	//���C���[�P�ƃ��C���[�Q�̐؂�ւ��̃s���g�̈ʒu
	float change2pos;	//���C���[�Q�ƃ��C���[�R�̐؂�ւ��̃s���g�̌��݈ʒu
	float texno1;		//�e�N�X�`���C���f�b�N�X
	float texno2;		//�e�N�X�`���C���f�b�N�X


};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPinto();
void    UnInitPinto();
void    DrawPinto();
void    UpdatePinto();
PINTO*	GetPinto(); //PINTO�\���̂̐擪�|�C���^���擾

void    SetLimit(int limit);
