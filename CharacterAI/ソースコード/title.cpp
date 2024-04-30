#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "title.h"

#include "select.h"
// #include "polygon2D.h"
#include "titleLogo.h"
#include "fade.h"

/*
#include <windows.h>
#include <math.h>
#include <mmsystem.h>
#include <tchar.h>
#include <cmath>

//----- �}���`���f�B�A���C�u�����t�@�C��
#pragma comment(lib, "winmm.lib")


// �΂�
#define BALL_RADIUS				10.0f	// �{�[���̔��a
#define BALL_MASS				400.0f	// �{�[���̎���

#define SPRING_DEFAULT_LENGTH	150.0f	// �΂˂̎��R��
#define SPRING_COEFFICIENT		3.0f	// �΂ˌW��

#define NUM_BALL (15)
struct BALL
{
	float x, y;
	float vx, vy;
	float m;
	float r;
	float rotationAngle; // ��]�p�x
};

BALL g_Ball[NUM_BALL] =
{
	{100.0f,500.0f,18.0f,0.0f,200.0f,50.0f},
	{400.0f,100.0f,3.0f,-10.0f,200.0f,50.0f},
	{100.0f,200.0f,3.0f,-10.0f,200.0f,50.0f},
	{100.0f,600.0f,3.0f,-10.0f,200.0f,50.0f},
	{200.0f,500.0f,10.0f,-5.0f,200.0f,50.0f},
	{300.0f,200.0f,5.0f,-15.0f,200.0f,50.0f},
	{100.0f,100.0f,11.0f,-8.0f,200.0f,50.0f},
};

// �΂˂̕ϐ�
int		status;				// �X�e�[�^�X
float	position;			// �ψ�
float	velocity;			// ���x (Velocity)
float	acceleration;		// �����x (Acceleration)
float	gravity;			// �d�� (Gravity)
float	tension;			// �e���� (Tension)

int g_Color = 255;
int g_ColorCount = 0;
bool g_multiplication = false;

HWND		g_hWndApp;				// �E�B���h�E�n���h��
int			g_iClientWidth;			// �N���C�A���g�̈�T�C�Y
int			g_iClientHeight;		// �N���C�A���g�̈�T�C�Y
RECT		g_ClientRect;			// �N���C�A���g�̈�
HDC			g_hMemDC;				// ����ʂc�b
HBITMAP		g_hBitmap;				// ����ʃr�b�g�}�b�v
*/


void Title::Init()
{
	AddGameObject<TitleLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
	//polygon2D->Title();
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Select>();
	}


}
/*
void Title::Draw()
{

	{
		// ����ʂ��D�F�ŃN���A
		RECT clientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		HBRUSH grayBrush = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(g_hMemDC, &clientRect, grayBrush);
		DeleteObject(grayBrush);

		// �{�[���̈ʒu���X�V���A�ĕ`��


		switch (status) {
		case 0:		// ������
			position = SPRING_DEFAULT_LENGTH + 100.0f;		// �ψ�
			velocity = 0.0f;									// ���x
			acceleration = 0.0f;									// �����x
			gravity = BALL_MASS * 0.98f;					// �d��
			tension = 0.0f;									// �e����
			status = 1;
			break;
		case 1:		// ���C������
			// �e���͂����߂� ���݂̍��W�[���R�����΂ˌW��
			tension = -SPRING_COEFFICIENT * (position - SPRING_DEFAULT_LENGTH);

			// ���͂Ǝ��ʂ�������x�����߂�@�i�d�́{�e���́j/����
			acceleration = (gravity + tension) / BALL_MASS;

			// ���x�ɉ����x��������@���ݑ��x�{�����x
			velocity += acceleration;

			// ���x������W���ړ�
			position += velocity;

			break;
		}
		// "GR32" �̕`��
		D3DXVECTOR2 textPosition;
		textPosition.x = SCREEN_WIDTH * 2 / 7; // X���W
		textPosition.y = position; // Y���W

		// ���F�̃p���b�g������
		COLORREF rainbowColors[] = {
			RGB(148, 0, 211),  // ��
			RGB(75, 0, 130),   // ��
			RGB(0, 0, 255),    // ��
			RGB(0, 255, 0),    // ��
			RGB(255, 255, 0),  // ��
			RGB(255, 127, 0),  // �I�����W
			RGB(255, 0, 0)     // ��
		};


		HFONT font = CreateFont(
			500, 0, 0, 0, FW_HEAVY, TRUE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Arial"
		);
		HFONT oldFont = (HFONT)SelectObject(g_hMemDC, font);

		g_ColorCount += 1;
		if (g_Color >= 255)
		{
			g_multiplication = false;
			g_Color = 255;
		}
		else if (g_Color <= 0)
		{
			g_multiplication = true;
			g_Color = 0;
		}

		if (g_ColorCount % 2 == 0)
		{
			if (g_multiplication)
			{
				g_Color++;
			}
			else
			{
				g_Color--;
			}
		}

		// ������𕶎����Ƃɓ��F�ŕ`��
		for (int i = 0; i < 5; i++) {
			SetTextColor(g_hMemDC, RGB(g_Color, g_Color, g_Color));
			TextOut(g_hMemDC, textPosition.x + i * 100, textPosition.y / 2, _T("A   I") + i, 1);
		}



		SelectObject(g_hMemDC, oldFont);
		DeleteObject(font);

		// �E�B���h�E���ĕ`��
		InvalidateRect(g_hWndApp, NULL, TRUE);


		// �{�[���̈ʒu���X�V���A�ĕ`��
		for (int i = 0; i < NUM_BALL; i++)
		{
			// �{�[���̑��x���ʒu�ɉ��Z���Ĉړ�
			g_Ball[i].x += g_Ball[i].vx;
			g_Ball[i].y += g_Ball[i].vy;

			// �{�[������ʊO�ɏo���ꍇ�A�ʒu���C��
			if (g_Ball[i].x - g_Ball[i].r < 0)
			{
				g_Ball[i].x = g_Ball[i].r;
				g_Ball[i].vx = -g_Ball[i].vx;
			}
			if (g_Ball[i].x + g_Ball[i].r > SCREEN_WIDTH)
			{
				g_Ball[i].x = SCREEN_WIDTH - g_Ball[i].r;
				g_Ball[i].vx = -g_Ball[i].vx;
			}
			if (g_Ball[i].y - g_Ball[i].r < 0)
			{
				g_Ball[i].y = g_Ball[i].r;
				g_Ball[i].vy = -g_Ball[i].vy;
			}
			if (g_Ball[i].y + g_Ball[i].r > SCREEN_HEIGHT)
			{
				g_Ball[i].y = SCREEN_HEIGHT - g_Ball[i].r;
				g_Ball[i].vy = -g_Ball[i].vy;
			}

			// �{�[���̕`��
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // �ԐF�̃u���V���쐬
			HBRUSH oldBrush = (HBRUSH)SelectObject(g_hMemDC, brush);

			Ellipse(g_hMemDC,
				(int)(g_Ball[i].x - g_Ball[i].r),
				(int)(g_Ball[i].y - g_Ball[i].r),
				(int)(g_Ball[i].x + g_Ball[i].r),
				(int)(g_Ball[i].y + g_Ball[i].r)
			);

			SelectObject(g_hMemDC, oldBrush);
			DeleteObject(brush);
		}

		// �E�B���h�E���ĕ`��
		InvalidateRect(g_hWndApp, NULL, TRUE);

		//�{�[���̕`��
		for (int i = 0; i < NUM_BALL; i++)
		{
			// ���F�̕`��F���v�Z
			int red = static_cast<int>(255 * (sin(g_Ball[i].x * 0.01) + 1) * 0.5);
			int green = static_cast<int>(255 * (sin(g_Ball[i].y * 0.01) + 1) * 0.5);
			int blue = static_cast<int>(255 * (cos((g_Ball[i].x + g_Ball[i].y) * 0.01) + 1) * 0.5);

			HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));
			HBRUSH oldBrush = (HBRUSH)SelectObject(g_hMemDC, brush);

			Ellipse(g_hMemDC,
				(int)(g_Ball[i].x - g_Ball[i].r),
				(int)(g_Ball[i].y - g_Ball[i].r),
				(int)(g_Ball[i].x + g_Ball[i].r),
				(int)(g_Ball[i].y + g_Ball[i].r)
			);

			SelectObject(g_hMemDC, oldBrush);
			DeleteObject(brush);
		}

		// ���̕`��
		for (int i = 0; i < NUM_BALL; i++)
		{
			// ���̕`��F���v�Z
			int red = static_cast<int>(255 * (sin(g_Ball[i].x * 0.01) + 1) * 0.5);
			int green = static_cast<int>(255 * (sin(g_Ball[i].y * 0.01) + 1) * 0.5);
			int blue = static_cast<int>(255 * (cos((g_Ball[i].x + g_Ball[i].y) * 0.01) + 1) * 0.5);

			HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));
			HBRUSH oldBrush = (HBRUSH)SelectObject(g_hMemDC, brush);

			// ���̕`��
			POINT starPoints[10];
			float angleIncrement = 2 * 3.14159f / 5; // 5�̊p�x���ϓ��ɕ���
			for (int j = 0; j < 10; j++)
			{
				float angle = j * angleIncrement;
				float radius = j % 2 == 0 ? g_Ball[i].r : g_Ball[i].r * 0.5f; // �����ӂƒZ���ӂ����݂�
				starPoints[j].x = static_cast<int>(g_Ball[i].x + radius * cos(angle));
				starPoints[j].y = static_cast<int>(g_Ball[i].y - radius * sin(angle)); // y���W�͏㉺���]
			}

			Polygon(g_hMemDC, starPoints, 10); // ����`��

			SelectObject(g_hMemDC, oldBrush);
			DeleteObject(brush);
		}

		// �E�B���h�E���ĕ`��
		InvalidateRect(g_hWndApp, NULL, TRUE);

		HFONT fontA = CreateFont(
			50, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, NULL
		);
		HFONT oldFontA = (HFONT)SelectObject(g_hMemDC, fontA);

		// ������𕶎����Ƃɓ��F�ŕ`��
		for (int i = 0; i < 12; i++) {
			SetTextColor(g_hMemDC, RGB(255, 255, 255));
			TextOut(g_hMemDC, SCREEN_WIDTH * 2 / 3 + i * 35, SCREEN_HEIGHT * 6 / 7, _T("TAKAGI.AYUMU") + i, 1);
		}

		SelectObject(g_hMemDC, oldFontA);
		DeleteObject(fontA);


		InvalidateRect(g_hWndApp, NULL, TRUE);		// �`��v��
	}
}
*/