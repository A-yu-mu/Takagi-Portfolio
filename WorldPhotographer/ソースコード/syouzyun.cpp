//=============================================================================
//cursor_A.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#include "syouzyun.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================


static CURSOR_A g_cursor_A;

float pattern_nums = 0;
float yoko_nums = 0;
float tate_nums = 1;
int   pattern_sizes = 1;
int tests;

//===================================
//������
//===================================
HRESULT InitCursor_A()
{
	//�v���C���[�̏�����
	g_cursor_A.pos.x = SCREEN_WIDTH / 2 + 40;
	g_cursor_A.pos.y = SCREEN_HEIGHT / 2 + 120;

	g_cursor_A.w = CURSOR_A_SIZE_W;
	g_cursor_A.h = CURSOR_A_SIZE_H;

	//g_cursor_A.Color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
	g_cursor_A.rot = 0.0f;
	g_cursor_A.use = true;
	g_cursor_A.texno = LoadTexture(g_TextureName_A);
	g_cursor_A.texno_B = LoadTexture(g_TextureName_B);
	g_cursor_A.texno_T1 = LoadTexture(g_TextureName_T1);
	g_cursor_A.texno_T2 = LoadTexture(g_TextureName_T2);
	g_cursor_A.texno_T3 = LoadTexture(g_TextureName_T3);
	g_cursor_A.texno_T4 = LoadTexture(g_TextureName_T4);
	g_cursor_A.texno_T5 = LoadTexture(g_TextureName_T5);

	g_cursor_A.camera_use = false;


	g_cursor_A.zoom = 1;
	//D3DXVECTOR2 pos_z;
	//float zw, zh;
	//int frame;

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitCursor_A()
{

}


//===================================
//�`��
//===================================
void    DrawCursor_A()
{
	if (g_cursor_A.camera_use == true)
	{
		

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_B));
		DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH+g_cursor_A.a*g_cursor_A.zoom-10, SCREEN_HEIGHT + g_cursor_A.a * g_cursor_A.zoom-10, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);

		if (g_cursor_A.zoom == 1)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T1));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		else if (g_cursor_A.zoom == 2)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T2));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else if (g_cursor_A.zoom == 3)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T3));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else if (g_cursor_A.zoom == 4)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T4));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
		else
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno_T5));
			DrawSpriteColorRotation(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1, 1, 2);
		}
	}


	//�v���C���[�\��
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cursor_A.texno));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(g_cursor_A.pos.x, g_cursor_A.pos.y, g_cursor_A.w, g_cursor_A.h, g_cursor_A.rot, g_cursor_A.Color, pattern_nums, tate_nums / pattern_sizes, tate_nums, pattern_sizes);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
	
}


//===================================
//�X�V
//===================================
void    UpdateCursor_A()
{
	if (GetKeyboardTrigger(DIK_R))//R�L�[
	{
		if (g_cursor_A.zoom >= 5)
		{

		}
		else
		{
			g_cursor_A.zoom += 1;
		}
		
	}
	else if (GetKeyboardTrigger(DIK_S))//S�L�[
	{
		if (g_cursor_A.zoom <= 1) 
		{
			
		}
		else
		{
			g_cursor_A.zoom -= 1;
		}
		
	}


	//�L�[�{�[�h�̓���
	if (GetKeyboardTrigger(DIK_Z))//Z�L�[
	{
		// �ォ��摜�킹��
		// �J�����N���t���O true
		g_cursor_A.camera_use = true;
	}
	else if (GetKeyboardTrigger(DIK_X))//X�L�[
	{
		g_cursor_A.camera_use = false;
	}


	//�L�[�{�[�h�̓���
	if (GetKeyboardPress(DIK_UP))//��L�[
	{
		//������Ă���Ԃ̏���
		g_cursor_A.pos.y -= 5.0f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_cursor_A.pos.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		//������Ă���Ԃ̏���
		g_cursor_A.pos.x += 5.0f;
		
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		g_cursor_A.pos.x -= 5.0f;
	}
	
}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
CURSOR_A* GetCursor_A()
{
	return &g_cursor_A;
}