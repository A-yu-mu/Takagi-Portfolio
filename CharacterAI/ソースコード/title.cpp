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

//----- マルチメディアライブラリファイル
#pragma comment(lib, "winmm.lib")


// ばね
#define BALL_RADIUS				10.0f	// ボールの半径
#define BALL_MASS				400.0f	// ボールの質量

#define SPRING_DEFAULT_LENGTH	150.0f	// ばねの自然長
#define SPRING_COEFFICIENT		3.0f	// ばね係数

#define NUM_BALL (15)
struct BALL
{
	float x, y;
	float vx, vy;
	float m;
	float r;
	float rotationAngle; // 回転角度
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

// ばねの変数
int		status;				// ステータス
float	position;			// 変位
float	velocity;			// 速度 (Velocity)
float	acceleration;		// 加速度 (Acceleration)
float	gravity;			// 重力 (Gravity)
float	tension;			// 弾性力 (Tension)

int g_Color = 255;
int g_ColorCount = 0;
bool g_multiplication = false;

HWND		g_hWndApp;				// ウィンドウハンドル
int			g_iClientWidth;			// クライアント領域サイズ
int			g_iClientHeight;		// クライアント領域サイズ
RECT		g_ClientRect;			// クライアント領域
HDC			g_hMemDC;				// 裏画面ＤＣ
HBITMAP		g_hBitmap;				// 裏画面ビットマップ
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
		// 裏画面を灰色でクリア
		RECT clientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		HBRUSH grayBrush = CreateSolidBrush(RGB(0, 0, 0));
		FillRect(g_hMemDC, &clientRect, grayBrush);
		DeleteObject(grayBrush);

		// ボールの位置を更新し、再描画


		switch (status) {
		case 0:		// 初期化
			position = SPRING_DEFAULT_LENGTH + 100.0f;		// 変位
			velocity = 0.0f;									// 速度
			acceleration = 0.0f;									// 加速度
			gravity = BALL_MASS * 0.98f;					// 重力
			tension = 0.0f;									// 弾性力
			status = 1;
			break;
		case 1:		// メイン処理
			// 弾性力を求める 現在の座標ー自然長＊ばね係数
			tension = -SPRING_COEFFICIENT * (position - SPRING_DEFAULT_LENGTH);

			// 合力と質量から加速度を求める　（重力＋弾性力）/質量
			acceleration = (gravity + tension) / BALL_MASS;

			// 速度に加速度を加える　現在速度＋加速度
			velocity += acceleration;

			// 速度から座標を移動
			position += velocity;

			break;
		}
		// "GR32" の描画
		D3DXVECTOR2 textPosition;
		textPosition.x = SCREEN_WIDTH * 2 / 7; // X座標
		textPosition.y = position; // Y座標

		// 虹色のパレットを準備
		COLORREF rainbowColors[] = {
			RGB(148, 0, 211),  // 紫
			RGB(75, 0, 130),   // 青紫
			RGB(0, 0, 255),    // 青
			RGB(0, 255, 0),    // 緑
			RGB(255, 255, 0),  // 黄
			RGB(255, 127, 0),  // オレンジ
			RGB(255, 0, 0)     // 赤
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

		// 文字列を文字ごとに虹色で描画
		for (int i = 0; i < 5; i++) {
			SetTextColor(g_hMemDC, RGB(g_Color, g_Color, g_Color));
			TextOut(g_hMemDC, textPosition.x + i * 100, textPosition.y / 2, _T("A   I") + i, 1);
		}



		SelectObject(g_hMemDC, oldFont);
		DeleteObject(font);

		// ウィンドウを再描画
		InvalidateRect(g_hWndApp, NULL, TRUE);


		// ボールの位置を更新し、再描画
		for (int i = 0; i < NUM_BALL; i++)
		{
			// ボールの速度を位置に加算して移動
			g_Ball[i].x += g_Ball[i].vx;
			g_Ball[i].y += g_Ball[i].vy;

			// ボールが画面外に出た場合、位置を修正
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

			// ボールの描画
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // 赤色のブラシを作成
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

		// ウィンドウを再描画
		InvalidateRect(g_hWndApp, NULL, TRUE);

		//ボールの描画
		for (int i = 0; i < NUM_BALL; i++)
		{
			// 虹色の描画色を計算
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

		// ★の描画
		for (int i = 0; i < NUM_BALL; i++)
		{
			// ★の描画色を計算
			int red = static_cast<int>(255 * (sin(g_Ball[i].x * 0.01) + 1) * 0.5);
			int green = static_cast<int>(255 * (sin(g_Ball[i].y * 0.01) + 1) * 0.5);
			int blue = static_cast<int>(255 * (cos((g_Ball[i].x + g_Ball[i].y) * 0.01) + 1) * 0.5);

			HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));
			HBRUSH oldBrush = (HBRUSH)SelectObject(g_hMemDC, brush);

			// ★の描画
			POINT starPoints[10];
			float angleIncrement = 2 * 3.14159f / 5; // 5つの角度を均等に分割
			for (int j = 0; j < 10; j++)
			{
				float angle = j * angleIncrement;
				float radius = j % 2 == 0 ? g_Ball[i].r : g_Ball[i].r * 0.5f; // 長い辺と短い辺を交互に
				starPoints[j].x = static_cast<int>(g_Ball[i].x + radius * cos(angle));
				starPoints[j].y = static_cast<int>(g_Ball[i].y - radius * sin(angle)); // y座標は上下反転
			}

			Polygon(g_hMemDC, starPoints, 10); // ★を描画

			SelectObject(g_hMemDC, oldBrush);
			DeleteObject(brush);
		}

		// ウィンドウを再描画
		InvalidateRect(g_hWndApp, NULL, TRUE);

		HFONT fontA = CreateFont(
			50, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, NULL
		);
		HFONT oldFontA = (HFONT)SelectObject(g_hMemDC, fontA);

		// 文字列を文字ごとに虹色で描画
		for (int i = 0; i < 12; i++) {
			SetTextColor(g_hMemDC, RGB(255, 255, 255));
			TextOut(g_hMemDC, SCREEN_WIDTH * 2 / 3 + i * 35, SCREEN_HEIGHT * 6 / 7, _T("TAKAGI.AYUMU") + i, 1);
		}

		SelectObject(g_hMemDC, oldFontA);
		DeleteObject(fontA);


		InvalidateRect(g_hWndApp, NULL, TRUE);		// 描画要求
	}
}
*/