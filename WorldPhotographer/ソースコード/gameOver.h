//=============================================================================
// gameOver.h
// �쐬�ҁF���ؕ����@�쐬���F2022/12/04
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================

static	ID3D11ShaderResourceView* g_Texture_GameOver;//�摜1����1�̕ϐ����K�v
static	ID3D11ShaderResourceView* g_Texture_GameOverBG;//�摜1����1�̕ϐ����K�v

static	char* g_TextureGameOver = (char*)"data\\texture\\game_over.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_TextureGameOverBG = (char*)"data\\texture\\fade_white.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct GameOver
{
	D3DXVECTOR2	Size;	//�|���S���̃T�C�Y
	D3DXVECTOR2 pos;	//�\�����W
	float rot;			//��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR BGColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.6f);
	
	float texGameOver;		//�e�N�X�`���C���f�b�N�X
	float texGameOverBG;	//�e�N�X�`���C���f�b�N�X

	int select_gameover = 0;
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitGameOver();
void    UnInitGameOver();
void    DrawGameOver();
void    UpdateGameOver();

GameOver* GetGameOver();	//GameOver�\���̂̐擪�|�C���^���擾

