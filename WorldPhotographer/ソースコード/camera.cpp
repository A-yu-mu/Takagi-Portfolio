//=============================================================================
//camera.cpp
// �쐬�ҁF�ݒ���/���їǑ��@�쐬���F2022/10/21
//=============================================================================
#include "camera.h"
#include "sprite.h"
#include "texture.h"
#include "windows.h"
#include "main.h"

#include "fade.h"
#include "player.h"

//�J�����̎q��
#include "layer.h"
#include "photo.h"
#include "photoreticle.h"
#include "pinto.h"
#include "io_ex.h"

//�����J�����p�[�g���ǂ������f����t���O
bool camera_scene_flag;


static PLAYER* g_player = GetPlayer();

//�J������UI�̃e�N�X�`���ԍ�
float cameraUItexno = 0;


HRESULT InitCamera()
{
	//�t���O�̏�����
	camera_scene_flag = false;

	//�J�����̎q���̏�����
	InitLayer();
	InitPhoto();
	InitPhotoreticle();
	InitPinto();

	cameraUItexno = LoadTexture(g_TextureNameCamera);

	return S_OK;
}

void UnInitCamera()
{
	//�J�����̎q���̏I������
	UnInitLayer();
	UnInitPhoto();
	UnInitPhotoreticle();
	UnInitPinto();

}

void DrawCamera()
{
	DrawPhoto();

	//camera_scene_flag��true�ɂȂ��Ă��鎞�̂ݍX�V�A�`�揈�����s��
	if (camera_scene_flag == true)
	{
		
		
		//�J�����̎q���̕`�揈��
		DrawLayer();
		DrawPhotoreticle();
		DrawPinto();

		//UI�̕\��
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(cameraUItexno));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			SCREEN_WIDTH / 2, 
			SCREEN_HEIGHT / 2,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, 1, 1);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�


	}

}

void UpdateCamera()
{
	{//�J�����p�[�g�̐؂�ւ����L�[�{�[�h�ŊǗ�����
		//�L�[�{�[�h��trigger����

		if (IsButton(X, TRIGGER) || IsButton(Y, TRIGGER))//XY�L�[

		{
			g_player->PlayerCamera = true;
			//�������u�Ԃ̏���
			PlaySE(SE_TURN);
		}

	}

	UpdatePhoto();

	//camera_scene_flag��true�ɂȂ��Ă��鎞�̂ݍX�V�A�`�揈�����s��
	if (camera_scene_flag == true)
	{
		//�J�����̎q���̍X�V����
		UpdateLayer();
		UpdatePhotoreticle();
		UpdatePinto();

	}
	
}

//===================================
//�J�����p�[�g�̊J�n�֐�
//===================================
void    StartCamera()
{
	camera_scene_flag = true;
}

//===================================
//�J�����p�[�g�̏I���֐�
//===================================
void    EndCamera()
{
	camera_scene_flag = false;
}

//===================================
//���݂̃J�����p�[�g�̃t���O��Ԃ��֐�
//===================================
bool NowCameraFlag()
{
	return camera_scene_flag;
}

