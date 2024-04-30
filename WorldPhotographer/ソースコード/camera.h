#pragma once
//=============================================================================
//camera.h
// �쐬�ҁF�ݒ���/���їǑ��@�쐬���F2022/10/21
// �ύX�ҁF�ڍ�特�@�ύX���F2022/10/25
//=============================================================================

#ifndef  CAMERA_H_
#define  CAMERA_H_



#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define CAMERA_SIZE_W (150)
#define	CAMERA_SIZE_H (150)


static	ID3D11ShaderResourceView* g_TextureCamera;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNameCamera = (char*)"data\\texture\\UI_Cam01.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct CAMERA
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X

};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT    InitCamera();
void    UnInitCamera();
void    DrawCamera();
void    UpdateCamera();
CAMERA* GetCamera();

//�J�����p�[�g���J�n����֐��ƏI������֐�
void    StartCamera();
void    EndCamera();

//�����J�����p�[�g���ǂ�����Ԃ��֐�
bool	NowCameraFlag();

#endif // ! CAMERA_H_