//=============================================================================
//enemy.h
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================



struct TITLE
{
	int select_title;

	float w, h;     //box�T�C�Y
	float texno;    //�e�N�X�`���C���f�b�N�X
	float texlogo;    //�e�N�X�`���C���f�b�N�X
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
};
//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitTitle();
void    UnInitTitle();
void    DrawTitle();
void    UpdateTitle();
TITLE* GetTitle(); //TITLE�\���̂̐擪�|�C���^���擾



