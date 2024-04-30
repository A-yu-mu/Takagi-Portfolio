//=============================================================================
// UI.cpp
// �쐬�ҁF���ؕ����@�쐬���F2022/11/02
//=============================================================================

#include "UI.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h""
#include "player.h"
#include "camera.h"
#include "title.h"
#include "gameOver.h"
#include "result.h"
#include "game.h"
#include "manual.h"
#include "stage_select.h"
#include "mapchip.h"

//===================================
//�}�N����`
//===================================


//===================================
//�v���g�^�C�v�錾
//===================================

SCENE g_scene_ui_draw;
SCENE g_scene_ui_update;

//===================================
//�O���[�o���ϐ�
//===================================


static UI g_ui;
static PLAYER* p_player;
static GAME* p_game;

static TITLE* p_title = GetTitle();
static GameOver* p_gameover = GetGameOver();
static RESULT* p_result= GetResult();
static MANUAL* p_manual = GetManual();

float pattern_num_tutorial_1 = 0;
float pattern_num_tutorial_2 = 0;
float pattern_num_tutorial_4 = 0;


//===================================
//������
//===================================
HRESULT InitUI()
{
	//UI�̏�����
	g_ui.pos.x = 0 + 80;
	g_ui.pos.y = 0 + 100;

	g_ui.Size = D3DXVECTOR2(LIFE_SIZE_W, LIFE_SIZE_H);

	g_ui.use = true;
	g_ui.pushpause = true;

	g_ui.texlife = LoadTexture(g_TextureLife);

	// �^�C�g���E���U���g�E�|�[�Y�E�Q�[���I�[�o�[ ��
	{
		g_ui.texManual = LoadTexture(g_TextureManual);
		g_ui.texMoveToStageSelection = LoadTexture(g_TextureMoveToStageSelection);
		g_ui.texBackTitel = LoadTexture(g_TextureBackTitel);
		g_ui.texRetry = LoadTexture(g_TextureRetry);
		g_ui.texBack = LoadTexture(g_TextureBack);
		g_ui.texOperateManual = LoadTexture(g_TextureOperateManual);
		g_ui.texCameraManual = LoadTexture(g_TextureCameraManual);
		g_ui.texPauseButtom = LoadTexture(g_TexturePauseGameButtom);
		g_ui.texArrow = LoadTexture(g_TextureArrowUI);
		g_ui.texStageSelection = LoadTexture(g_TextureStageSelection);
		g_ui.texStageLock = LoadTexture(g_TextureStageLock);
		g_ui.texTutorial1 = LoadTexture(g_TextureTutorial1);
		g_ui.texTutorial2 = LoadTexture(g_TextureTutorial2);
		g_ui.texTutorial3 = LoadTexture(g_TextureTutorial3);
		g_ui.texTutorial4 = LoadTexture(g_TextureTutorial4);
	}

	SetTutorial1(false);
	SetTutorial2(false);
	SetTutorial3(false);
	SetTutorial4(false);

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitUI()
{

}


//===================================
//�`��
//===================================
void    DrawUI()
{
	// �\��
	if (g_ui.use)
	{
		p_player = GetPlayer();
		p_game = GetGame();

		g_scene_ui_draw = GetScene();


		switch (g_scene_ui_draw)
		{
		case SCENE_TITLE:
			// �X�e�[�W�Z���N�g
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texMoveToStageSelection));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 5 / 7, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6.5, 0, g_ui.MoveToStageSelectionColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		// ��������I��
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texManual));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 7 / 8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.ManualColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;

		case SCENE_GAME:

			if (p_player->DeathFlag == false)
			{
				// ���C�t�\��
				{
					//�e�N�X�`���̕\��
					GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texlife));

					switch (p_player->life)
					{
					case 1:
						DrawSpriteColorRotation(LIFE_POS_X, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 1, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x * 2, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 1, 1.0f / 2, 1, 2);
						break;

					case 2:
						DrawSpriteColorRotation(LIFE_POS_X, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x * 2, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 1, 1.0f / 2, 1, 2);
						break;

					default:
						DrawSpriteColorRotation(LIFE_POS_X, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						DrawSpriteColorRotation(LIFE_POS_X + g_ui.Size.x * 2, LIFE_POS_Y, g_ui.Size.x, g_ui.Size.y, g_ui.rot, g_ui.Color, 0, 1.0f / 2, 1, 2);
						break;
					}
				}

				
				// �|�[�Y���\��
				if (p_game->GameUpdateFlag == false)
				{
					g_ui.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
					g_ui.TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

					// �^�C�g���֖߂�
					{
						// �e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBackTitel));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH / 6, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.BackTitelColor, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					// ���g���C
					{
						// �e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texRetry));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH * 4 / 7, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7, 0, g_ui.RetryColor, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					// �߂�
					{
						// �e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBack));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH * 7 / 8, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 6, SCREEN_HEIGHT / 7, 0, g_ui.BackColor, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					// ���쒆�}�j���A��
					{
						//�e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texOperateManual));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH * 7 / 8 - 40, SCREEN_HEIGHT * 1 / 8 + 120, SCREEN_WIDTH / 4 + 50, SCREEN_HEIGHT / 4 + 120, 0, g_ui.Color, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					// �J�������}�j���A���\��
					{
						//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texCameraManual));

						//DrawSpriteColorRotation(SCREEN_WIDTH * 7 / 8, SCREEN_HEIGHT * 1 / 8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, 0, g_ui.Color, 0, 1, 1, 1);
						//�e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texCameraManual));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH * 7 / 8 - 680, SCREEN_HEIGHT * 1 / 8 + 120, SCREEN_WIDTH / 4 + 50, SCREEN_HEIGHT / 4 + 80, 0, g_ui.Color, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}
				}
				else if(p_game->GameUpdateFlag == true)
				{
					g_ui.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

					// Puase�{�^��
					{
						// �e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texPauseButtom));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(SCREEN_WIDTH / 6 + 745 , SCREEN_HEIGHT * 6 / 7 - 425, SCREEN_WIDTH / 12, SCREEN_HEIGHT / 10, 0, g_ui.Color, 0, 1, 1, 1);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					g_ui.TutorialColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					if (GetTutorial1() == true)
					{
						//�e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texTutorial1));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(TUTORIAL_POS_X, TUTORIAL_POS_Y, TUTORIAL_SIZE_W, TUTORIAL_SIZE_H, 0, g_ui.TutorialColor, pattern_num_tutorial_1, 1.0f / 4, 1.0f, 4);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					if (GetTutorial2() == true)
					{
						if (p_game->GameCameraFlag == true)
						{
							//�e�N�X�`���̕\��
							GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texTutorial2));

							//�X�v���C�g�\��
							DrawSpriteColorRotation(TUTORIAL_POS_X, TUTORIAL_POS_Y, TUTORIAL_SIZE_W, TUTORIAL_SIZE_H * 3 / 2, 0, g_ui.TutorialColor, pattern_num_tutorial_2, 1.0f / 4, 1.0f, 4);
							//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
						}
						else
						{
							//�e�N�X�`���̕\��
							GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texTutorial4));

							//�X�v���C�g�\��
							DrawSpriteColorRotation(TUTORIAL_POS_X, TUTORIAL_POS_Y, TUTORIAL_SIZE_W, TUTORIAL_SIZE_H / 2, 0, g_ui.TutorialColor, pattern_num_tutorial_2, 1.0f / 2, 1.0f, 2);
							//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
						}
					}

					if (GetTutorial3() == true)
					{
						//�e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texTutorial3));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(TUTORIAL_POS_X, TUTORIAL_POS_Y, TUTORIAL_SIZE_W, TUTORIAL_SIZE_H, 0, g_ui.TutorialColor, pattern_num_tutorial_4, 1.0f / 2, 1, 2);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}

					if (GetTutorial4() == true)
					{
						//�e�N�X�`���̕\��
						GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texTutorial4));

						//�X�v���C�g�\��
						DrawSpriteColorRotation(TUTORIAL_POS_X, TUTORIAL_POS_Y, TUTORIAL_SIZE_W, TUTORIAL_SIZE_H, 0, g_ui.TutorialColor, pattern_num_tutorial_4, 1.0f / 2, 1, 2);
						//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
					}
				}
			}
			break;

		case SCENE_GAMEOVER:
			// �^�C�g���֖߂�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBackTitel));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 6, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.BackTitelColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// ���g���C
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texRetry));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 4 / 7, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7, 0, g_ui.RetryColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �X�e�[�W�Z���N�g��ʂ�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texMoveToStageSelection));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 5 / 6, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 7, 0, g_ui.MoveToStageSelectionColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;

		case SCENE_RESULT:
		// �^�C�g���֖߂�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBackTitel));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 6, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.BackTitelColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// ���g���C
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texRetry));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 4 / 7, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 7, 0, g_ui.RetryColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �X�e�[�W�Z���N�g��ʂ�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texMoveToStageSelection));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 5 / 6, SCREEN_HEIGHT * 6 / 7, SCREEN_WIDTH / 3.5, SCREEN_HEIGHT / 7, 0, g_ui.MoveToStageSelectionColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
		break;

		case SCENE_STAGESELECT:
		// �X�e�[�W���b�N
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texStageLock));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, STAGELOCK_SIZE_W, STAGELOCK_SIZE_H, 0, g_ui.StageLockColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �^�C�g���֖߂�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBackTitel));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 10 / 11, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.BackTitelColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �����
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texArrow));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 1 / 15, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4, 0, g_ui.LArrowColor, 0, 1.0f / 2, 1, 2);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �E���
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texArrow));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 14 / 15, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4, 0, g_ui.RArrowColor, 1, 1.0f / 2, 1, 2);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �X�e�[�W�Z���N�g
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texStageSelection));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10, SCREEN_WIDTH * 4 / 7, SCREEN_HEIGHT / 7, 0, g_ui.Color, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
			break;

		case SCENE_MANUAL:
		// �^�C�g���֖߂�
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texBackTitel));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 10 / 11, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 7, 0, g_ui.BackTitelColor, 0, 1, 1, 1);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �����
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texArrow));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 1 / 15, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4, 0, g_ui.LArrowColor, 0, 1.0f / 2, 1, 2);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}

		// �E���
		{
			// �e�N�X�`���̕\��
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ui.texArrow));

			//�X�v���C�g�\��
			DrawSpriteColorRotation(SCREEN_WIDTH * 14 / 15, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 4, 0, g_ui.RArrowColor, 1, 1.0f / 2, 1, 2);
			//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
		}
			break;
		}
	}
}


//===================================
//�X�V
//===================================
void    UpdateUI()
{
	// �`���[�g���A�� (���E�ړ��E�W�����v)
	if (GetTutorial1() == true)
	{
		pattern_num_tutorial_1 += 0.05;

		if (pattern_num_tutorial_1 >= 4)
		{
			pattern_num_tutorial_1 >= 0;
		}
	}

	// �`���[�g���A�� (�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e)
	if (GetTutorial2() == true)
	{
		pattern_num_tutorial_2 += 0.05;

		if (pattern_num_tutorial_2 >= 2)
		{
			pattern_num_tutorial_2 >= 0;
		}
	}

	// �`���[�g���A�� (�v���C���[�Ă��t��)
	if (GetTutorial3() == true)
	{
		pattern_num_tutorial_4 += 0.05;

		if (pattern_num_tutorial_4 >= 2)
		{
			pattern_num_tutorial_4 >= 0;
		}
	}

	g_scene_ui_update = GetScene();
	switch (g_scene_ui_update)
	{
	case SCENE_TITLE:
		// �^�C�g��
		switch (p_title->select_title)
		{
		case 0:
			g_ui.ManualColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case 1:
			// �X�e�[�W�Z���N�g
			g_ui.ManualColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			// �������
			break;
		}
		break;

	case SCENE_GAME:
		// �Q�[��
		switch (p_game->select_game)
		{
		case 0:
			// �^�C�g���֖߂�
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 1:
			// ���g���C
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 2:
			// �X�e�[�W�I��
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.BackColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
		break;

	case SCENE_GAMEOVER:
		// �Q�[���I�[�o�[
		switch (p_gameover->select_gameover)
		{
		case 0:
			// �^�C�g���֖߂�
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 1:
			// ���g���C
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 2:
			// �X�e�[�W�I��
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
		break;

	case SCENE_RESULT:
		// ���U���g
		switch (p_result->select_result)
		{
		case 0:
			// �^�C�g���֖߂�
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 1:
			// ���g���C
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 2:
			// �X�e�[�W�I��
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RetryColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.MoveToStageSelectionColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
		break;

	case SCENE_STAGESELECT:

		g_ui.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (GetSelectStageSelect())
		{
		case 0:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			break;

		case 1:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 1)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 2:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 2)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 3:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 3)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 4:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 4)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 5:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 5)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 6:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 6)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 7:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			if (GetStageOpen() >= 7)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 8:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			if (GetStageOpen() >= 8)
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			else
			{
				g_ui.StageLockColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
			}
			break;

		case 9:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;
		}
		break;

	case SCENE_MANUAL:
		switch (p_manual->select_manual)
		{
		case 0:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case 1:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;

		case 2:
			g_ui.BackTitelColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_ui.LArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			g_ui.RArrowColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;
		}
		break;
	}
}

