//*********************************************************
// sprite.h
// �쐬�ҁF�ݒ��Ɓ@�쐬��2022/06/13
//*********************************************************
#pragma once

#include "main.h"

//*********************************************************
//�}�N����`
//*********************************************************




//*********************************************************
//�v���g�^�C�v�錾
//*********************************************************

//static	float	PaternNo = 0;	//�p�^�[���ԍ�
//float	uv_w = 0.5f;			//���T�C�Y
//float	uv_h = 0.5f;			//�c�T�C�Y
//int		NumPatern = 2;			//������

void DrawSpriteColorRotation(float, float, int, int, float, D3DXCOLOR,float PaternNo,float uv_w,float uv_h,int NumPatern);	//�O�p�`�p���_�i�[����
void DrawSpritePhoto(float, float, int, int, D3DXCOLOR, D3DXVECTOR2);	//�t�H�g�̕`���p���� by�ڍ�
void InitSprite(); //�X�v���C�g������
void UninitSprite();//�X�v���C�g�I������








