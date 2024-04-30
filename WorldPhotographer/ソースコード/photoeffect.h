//=============================================================================
//photoeffect.h
// �쐬�ҁF�L�� ��C�@�쐬���F2022/11/15
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define PHOTOEFFECT_SIZE_W (280)
#define	PHOTOEFFECT_SIZE_H (280)
#define PHOTOEFFECT_MAX    (10)
#define PHOTOEFFECT_SPEED  (10.0f)
#define PHOTOEFFECT_ANIME_MAX (7)//�A�j���[�V�����ő吔

static	ID3D11ShaderResourceView* g_TexturePhotoEffect;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNamePhotoEffect = (char*)"data\\texture\\PhotoEffect.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct PHOTOEFFECT
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X
	float m_animeSpeed;
	float pattern_num_explosion;

};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitPhotoEffect();
void    UnInitPhotoEffect();
void    DrawPhotoEffect();
void    UpdatePhotoEffect();
PHOTOEFFECT* GetPhotoEffect(); //BULLET�\���̂̐擪�|�C���^���擾
void SetPhotoEffect(float x, float y,float animeSpeed);


