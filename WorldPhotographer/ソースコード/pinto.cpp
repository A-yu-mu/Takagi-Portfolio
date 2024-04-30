//=============================================================================
//pinto.cpp
// �쐬�ҁF�ڍ�@�쐬���F2022/11/08
//=============================================================================

#include "pinto.h"

#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
//===================================
//�}�N����`
//===================================

#define PRESS_TIME_MAX	(1)	//�s���g���������ςɂ����Ƃ��ɉ��t���[����ɓ������p

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================
static PINTO g_pinto;

int			g_press;	//�{�^�����������ς��ǂ����̕ϐ�

int			g_limit;	//���C���[�̐����̕\����

//===================================
//������
//===================================
HRESULT InitPinto()
{
	g_pinto.use = true;

	g_pinto.maxpos = 600.0f;
	g_pinto.nowpos = 0.0f;

	g_pinto.change1pos = 200.0f;
	g_pinto.change2pos = 400.0f;

	g_pinto.texno1 = LoadTexture(g_PintoTextureName1);
	g_pinto.texno2 = LoadTexture(g_PintoTextureName2);

	g_press = 0;
	g_limit = 3;

	return S_OK;
}


//===================================
//�I��
//===================================
void    UnInitPinto()
{

}


//===================================
//�`��
//===================================
void    DrawPinto()
{
	//�f�o�b�O�悤�Ɋe�s���g�\���̗̂v�f����ʂɏo���Ă���
	//�s���g�\��
	if (g_pinto.use == true)
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_pinto.texno1));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			SCREEN_WIDTH / 2, SCREEN_HEIGHT - 26.0f,//xy
			960.0f / 2.0f, 57.0f / 2.0f,//wh
			0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),//rotcol
			1, 1, 1, 1);//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

		//���C���[�����ɂ���Čv�Z��ς���
		float max = 0.0f;
		switch (g_limit)
		{
		case 1: max = g_pinto.change1pos; break;
		case 2: max = g_pinto.change2pos; break;
		case 3: max = g_pinto.maxpos; break;

		}
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_pinto.texno2));

		
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			(g_pinto.nowpos / max * 900.0f / 2.0f) + SCREEN_WIDTH / 4.0f + 15.0f, 
			SCREEN_HEIGHT - 48.0f,//xy
			24.0f / 2.0f, 27.0f / 2.0f,//wh
			0.0f, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),//rotcol
			1, 1, 1, 1);//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�

		
		

	}


}


//===================================
//�X�V
//===================================
void    UpdatePinto()
{
	//�s���g�̓���������
	//�L�[�{�[�h�̓���
	/*if (IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		g_pinto.nowpos -= PINTO_MOVE_01;
	}
	else if (IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		g_pinto.nowpos += PINTO_MOVE_01;
	}*/

	//�{�^�������΂炭�������ςȂ炸���Ɠ�����
	if (IsButton(R_LEFT, PUSH))
	{
		g_press++;
		if (g_press >= PRESS_TIME_MAX)
		{
			g_pinto.nowpos -= PINTO_MOVE_02;
			if ((int)g_pinto.nowpos % 10)//��
			{
				PlaySE(SE_PINTO);
			}
		}
	}
	else if (IsButton(R_RIGHT, PUSH))
	{
		g_press++;
		if (g_press >= PRESS_TIME_MAX)
		{
			g_pinto.nowpos += PINTO_MOVE_02;
			if ((int)g_pinto.nowpos % 10)//��
			{
				PlaySE(SE_PINTO);
			}
		}
	}
	else
	{
		g_press = 0;
	}

	int max;
	switch (g_limit)
	{
	case 1: max = g_pinto.change1pos; break;
	case 2: max = g_pinto.change2pos; break;
	case 3: max = g_pinto.maxpos; break;
	
	}

	//�s���g�̈ʒu���ő�l�A�ŏ��l�𒴂�����߂�
	if (g_pinto.nowpos > max)
	{
		g_pinto.nowpos = max;
	}
	else if(g_pinto.nowpos < 0.0f)
	{
		g_pinto.nowpos = 0.0f;
	}





}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
PINTO* GetPinto()
{
	return &g_pinto;

}


void    SetLimit(int limit)
{
	g_limit = limit;

}
