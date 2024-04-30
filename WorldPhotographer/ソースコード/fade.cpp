
#include "fade.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"

#include "camera.h"

#define FADE_SPEED	(0.06f)

float g_Alfha;
FADE_STATUS g_Fade;

static	ID3D11ShaderResourceView* g_FadeTexture;//�摜1����1�̕ϐ����K�v
static	char* g_FadeTextureName = (char*)"data\\texture\\Shutter_A_1920_1080_30fps_v02.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static int g_FadeTextureNo = 0;

bool UseCamera;

FADE* Fade;//�w�i�\���̂̃|�C���^�ϐ�

HRESULT InitFade()
{
	g_Alfha = 0.0f;
	g_Fade = FADE_NONE;

	//�w�i�̏�����
	Fade = new FADE;//�w�i�̃C���X�^���X�쐬
	Fade->Position.x = SCREEN_WIDTH / 2;
	Fade->Position.y = SCREEN_HEIGHT / 2;
	Fade->Position.z = 0;

	Fade->size.x = SCREEN_WIDTH;
	Fade->size.y = SCREEN_HEIGHT;

	Fade->Rotation = 0.0f;

	Fade->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//texture�̃��[�h
	g_FadeTextureNo = LoadTexture(g_FadeTextureName);
	if (g_FadeTextureNo == -1)
	{//���[�h�G���[
		exit(999);//�����I��
	}

	UseCamera = false;

	return S_OK;
}


void UninitFade()
{
	if (Fade)
	{
		delete Fade;
	}
}


void UpdateFade()
{
	if (g_Fade == FADE_OUT_NORMAL)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//�J�������[�h�̏I��
			EndCamera();

			//UseCamera = true;
		}
	}

	if (g_Fade == FADE_OUT_CAMERA)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//�J�������[�h�̋N��
			StartCamera();

			//UseCamera = false;
		}
	}

	if (g_Fade == FADE_OUT_TITLE)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//���U���g��ʈڍs
			SetScene(SCENE_TITLE);
		}
	}

	if (g_Fade == FADE_OUT_STAGESELECT)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//���U���g��ʈڍs
			SetScene(SCENE_STAGESELECT);
		}
	}

	if (g_Fade == FADE_OUT_GAME)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//���U���g��ʈڍs
			SetScene(SCENE_GAME);
		}
	}

	if (g_Fade == FADE_OUT_GAMEOVER)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//���U���g��ʈڍs
			SetScene(SCENE_GAMEOVER);
		}
	}

	if (g_Fade == FADE_OUT_RESULT)
	{
		g_Alfha += FADE_SPEED;

		if (g_Alfha >= 1.0f)
		{
			g_Alfha = 1.0f;
			g_Fade = FADE_IN;

			//���U���g��ʈڍs
			SetScene(SCENE_RESULT);
		}
	}

	if (g_Fade == FADE_IN)
	{
		g_Alfha -= FADE_SPEED;

		if (g_Alfha <= 0.0f)
		{
			g_Alfha = 0.0f;
			g_Fade = FADE_NONE;
		}
	}
}

void DrawFade()
{
	//if (UseCamera == true)
	//{
	//	//�e�N�X�`���̕\��
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeTextureNo));
	//	D3DXCOLOR col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	//	//�X�v���C�g�\��
	//	DrawSpriteColorRotation(Fade->Position.x, Fade->Position.y, Fade->size.x, Fade->size.y, Fade->Rotation, Fade->Color, 0, 1, 1, 2);
	//	//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	//}

	if (g_Fade != FADE_NONE)
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FadeTextureNo));

		//�X�v���C�g�\��
		DrawSpriteColorRotation(Fade->Position.x, Fade->Position.y, Fade->size.x, Fade->size.y, Fade->Rotation, 
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			g_Alfha * 4 + 1, 0.2f, 1, 5);
		//�A�j���[�V�����p�^�[���ԍ��A�p�^�[���̉��T�C�Y�A�c�T�C�Y�A�������ԃp�^�[���̐�
	}
}

void SetFade(FADE_STATUS status)
{
	g_Fade = status;

	if (status == FADE_IN)
	{
		g_Alfha = 1.0f;
	}

	if (status == FADE_OUT_NORMAL)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_TITLE)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_STAGESELECT)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_GAME)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_GAMEOVER)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_RESULT)
	{
		g_Alfha = 0.0f;
	}

	if (status == FADE_OUT_CAMERA)
	{
		g_Alfha = 0.0f;
	}
}

//���݂̃t�F�[�h�̏�Ԃ�Ԃ�
FADE_STATUS GetFadeStatus()
{
	return g_Fade;
}
