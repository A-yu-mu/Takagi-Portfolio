//=============================================================================
// stage_select.cpp
// �쐬�ҁF�ݒ��Ɓ@�쐬���F2022/06/27
//=============================================================================

#include "stage_select.h"
#include "sprite.h"
#include "texture.h"
#include "io_ex.h"
#include "fade.h"

#include "camera.h"

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================

static STAGE_SELECT g_stage_select[STAGE_MAX];

float pattern_num_stage_select = 0;
float yoko_num_stage_select = 1;
float tate_num_stage_select = 1;
int   pattern_size_stage_select = 1;
int   g_margin = 20;

//�J������UI�̃e�N�X�`���ԍ�
float stage_CamUItexno = 0;
int g_tempselect = 0;
bool DpadUpDown;
int stage_num;

//�e�X�e�[�W�̉摜
int stage1_1tex;
int stage1_2tex;
int stage1_3tex;
int stage2_1tex;
int stage2_2tex;
int stage2_3tex;
int stage3_1tex;
int stage3_2tex;
int stage3_3tex;

int stage_select_bg;

//===================================
//������
//===================================
HRESULT InitStageSelect()
{
	static	ID3D11ShaderResourceView* g_BGt;//�摜1����1�̕ϐ����K�v
	static	char* g_TextureNameBG = (char*)"data\\texture\\space.jpg";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

	for (int i = 0; i < STAGE_MAX; i++)
	{
		g_stage_select[i].select = 0;
		g_stage_select[i].h = SCREEN_HEIGHT/6;
		g_stage_select[i].w = SCREEN_WIDTH/4;
		g_stage_select[i].texno = LoadTexture(g_TextureNameBG);
		//g_stage_select[i].texStageList = LoadTexture(g_TextureNameStageList);
	}

	stage1_1tex = LoadTexture(g_TexturesStage1_1);
	stage1_2tex = LoadTexture(g_TexturesStage1_2);
	stage1_3tex = LoadTexture(g_TexturesStage1_3);
	stage2_1tex = LoadTexture(g_TexturesStage2_1);
	stage2_2tex = LoadTexture(g_TexturesStage2_2);
	stage2_3tex = LoadTexture(g_TexturesStage2_3);
	stage3_1tex = LoadTexture(g_TexturesStage3_1);
	stage3_2tex = LoadTexture(g_TexturesStage3_2);
	stage3_3tex = LoadTexture(g_TexturesStage3_3);

	stage_select_bg = LoadTexture(g_TextureStageSelectBG);

	stage_CamUItexno = LoadTexture(g_TextureNameCamera);

	DpadUpDown = false;

	PlayBGM(BGM_STAGESELECT);
	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitStageSelect()
{
	//UninitTexture();
	//���̑S��~
	StopSoundAll();
}


//===================================
//�`��
//===================================
void    DrawStageSelect()
{
	for (int i = 0; i < STAGE_MAX; i++)
	{
		// �^�C�g���摜
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_stage_select[i].texno));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, g_stage_select[i].Color, pattern_num_stage_select, tate_num_stage_select / pattern_size_stage_select, tate_num_stage_select, pattern_size_stage_select);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		if(g_stage_select[i].select == 9)
		{
			switch (g_tempselect)
			{
			case 0:
				// �e�N�X�`���̕\�� 1-1
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 1://�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
				// �e�N�X�`���̕\�� 1-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 2:
				// �e�N�X�`���̕\�� 1-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


				// �e�N�X�`���̕\�� 2-1
			case 3:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 4:
				// �e�N�X�`���̕\�� 2-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 5:
				// �e�N�X�`���̕\�� 2-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 6:
				// �e�N�X�`���̕\�� 3-1
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 7:
				// �e�N�X�`���̕\�� 3-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 8:
				// �e�N�X�`���̕\�� 3-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;
			}
		}
		
		// �X�e�[�W�I��
		{
			switch (g_stage_select[i].select)
			{
			case 0:
				// �e�N�X�`���̕\�� 1-1
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 1://�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
				// �e�N�X�`���̕\�� 1-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 2:
				// �e�N�X�`���̕\�� 1-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage1_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


				// �e�N�X�`���̕\�� 2-1
			case 3:
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 4:
				// �e�N�X�`���̕\�� 2-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 5:
				// �e�N�X�`���̕\�� 2-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage2_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 6:
				// �e�N�X�`���̕\�� 3-1
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_1tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 7:
				// �e�N�X�`���̕\�� 3-2
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_2tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;


			case 8:
				// �e�N�X�`���̕\�� 3-3
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage3_3tex));
				//�X�v���C�g�\��
				DrawSpriteColorRotation(SCREEN_WIDTH / 2,
					SCREEN_HEIGHT / 2,
					SCREEN_WIDTH / 1.5,
					SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].StageListColor, 1, 1, 1, 1);
				break;
			}
		}
		// ���b�N���w�i�摜
		{
			//�e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage_select_bg));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,SCREEN_WIDTH / 1.5,SCREEN_HEIGHT / 1.5, 0, g_stage_select[i].LockBGColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
	}

	DrawStageCamUI();
}


//===================================
//�X�V
//===================================
void    UpdateStageSelect()
{

	for (int i = 0; i < STAGE_MAX; i++)
	{
		switch (g_stage_select[i].select)
		{
		case 0:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;
		case 1:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 0)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 2:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			if (GetStageOpen() <= 1)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 3:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 2)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 4:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 3)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 5:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 4)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 6:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 5)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 7:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 6)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 8:
			// �X�e�[�W�Z���N�g
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() <= 7)
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			}
			else
			{
				g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			break;
		case 9:
			// �^�C�g���ɖ߂�
			g_stage_select[i].StageListColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_stage_select[i].LockBGColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;
		}


		if (IsButton(L_RIGHT, TRIGGER))
		{
			if (g_stage_select[i].select < 8)
			{
				g_stage_select[i].select += 1;
			}
			PlaySE(SE_MOVECURSOR);
		}

		if (IsButton(L_LEFT, TRIGGER))
		{
			if (g_stage_select[i].select > 0 )
			{
				if (g_stage_select[i].select <= 8)
				{
					g_stage_select[i].select -= 1;
				}
			}
			PlaySE(SE_MOVECURSOR);
		}

		if (IsButton(L_DOWN, TRIGGER))
		{
			if (g_stage_select[i].select < 9)
			{
				g_tempselect = g_stage_select[i].select;
				g_stage_select[i].select = 9;
			}
			PlaySE(SE_MOVECURSOR);
		}

		if (IsButton(L_UP, TRIGGER))
		{
			if (g_stage_select[i].select == 9)
			{
				g_stage_select[i].select = g_tempselect;
			}
			PlaySE(SE_MOVECURSOR);
		}
		if (IsButton(A, TRIGGER))
		{
			PlaySE(SE_OK);
			stage_num = g_stage_select[i].select;
			if (g_stage_select[i].select == 9)
			{
				SetFade(FADE_OUT_TITLE);
			}
			if (g_stage_select[i].select <= GetStageOpen())
			{
				switch (g_stage_select[i].select)
				{
				case 0:
					// �X�e�[�W1-1
					SetFade(FADE_OUT_GAME);
					break;

				case 1:

					SetFade(FADE_OUT_GAME);

					break;

				case 2:
					SetFade(FADE_OUT_GAME);

					break;
				case 3:
					SetFade(FADE_OUT_GAME);

					break;
				case 4:
					SetFade(FADE_OUT_GAME);

					break;
				case 5:
					SetFade(FADE_OUT_GAME);

					break;
				case 6:
					SetFade(FADE_OUT_GAME);

					break;
				case 7:
					SetFade(FADE_OUT_GAME);

					break;
				case 8:
					SetFade(FADE_OUT_GAME);

					break;

				default:
					SetFade(FADE_OUT_TITLE);
					break;
				}
			}
			break;
		}
	}
}

void DrawStageCamUI()
{
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(stage_CamUItexno));

	//�X�v���C�g�\��
	DrawSpriteColorRotation(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		SCREEN_WIDTH/1.2,
		SCREEN_HEIGHT/1.2,
		0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, 1, 1);
}

int GetSelectStageSelect()
{
	for (int i = 0; i < STAGE_MAX; i++)
	{
		return g_stage_select[i].select;
	}
}

int GetStageNum()
{
	return stage_num;
}

