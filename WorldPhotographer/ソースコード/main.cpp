/*==============================================================================

   DirectXの初期化 [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include <iostream>
#include	"main.h"
#include	"renderer.h"
#include	"polygon.h"
#include    "sprite.h"
#include    "inputx.h"
#include	"keyboard.h"
#include    "collision.h"
#include	"io_ex.h"
#include	"player.h"

#include    "sound.h"
#include    "game.h"
#include    "title.h"
#include    "result.h"
#include    "block.h"
#include    "stage_select.h"
#include	"manual.h"

#include    "fade.h"
#include	"gameOver.h"
#include    "texture.h"
#include	"UI.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//#ifdef _DEBUG
//int		g_CountFPS;							// FPSカウンタ
//char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用
//
//FILE* out = 0;
//HANDLE Console;
//COORD CursorPos;
//#endif

SCENE g_scene;

static PLAYER* player;

int stage_open = 0;

bool stage_lock_mode = true;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);
	
	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG			msg;

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
//#ifdef _DEBUG
//				g_CountFPS = dwFrameCount;
//#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存
				
				
//#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
//				wsprintf(g_DebugStr, WINDOW_CAPTION);
//				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
//				SetWindowText(hWnd, g_DebugStr);
//#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算

			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "やめないでー", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
//#ifdef _DEBUG
//	AllocConsole();
//	(void)freopen_s(&out, "CON", "w", stdout);
//	Console = GetStdHandle(STD_OUTPUT_HANDLE);
//	CursorPos.X = 0;
//	CursorPos.Y = 0;
//#endif
	stage_open = 0;
	stage_lock_mode = true;

	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	InitPolygon();//ポリゴンの初期化

	//入力処理初期化
	InitInput(hInstance, hWnd);
	Keyboard_Initialize();
	
	//サウンドの初期化
	InitSound(hWnd);

	//コントローラーとキーボード入力をまとめて確認する為に必要
	InitIoEx();

	g_scene = SCENE_TITLE;

	InitFade();
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_GAMEOVER:
		InitGameOver();
		break;
	case SCENE_RESULT:
		InitResult();
	case SCENE_STAGESELECT:
		InitStageSelect();
	case SCENE_MANUAL:
		InitManual();
		break;
	}

	// UIの初期化
	InitUI();


//	SetScene(SCENE_TITLE);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
//#ifdef _DEBUG
//	//コンソール解放
//	fclose(out);
//	FreeConsole();
//#endif
	UninitFade();
	switch (g_scene)
	{
	case SCENE_TITLE:
		UnInitTitle();
		break;
	case SCENE_GAME:
		UnInitGame();
		break;
	case SCENE_GAMEOVER:
		UnInitGameOver();
		break;
	case SCENE_RESULT:
		UnInitResult();
		break;
	case SCENE_STAGESELECT:
		UnInitStageSelect();
		break;
	case SCENE_MANUAL:
		UnInitManual();
		break;
	}
	// UIの終了
	UnInitUI();

	UninitPolygon();	//ポリゴンの終了処理

	//入力処理の終了処理
	UninitInput();

	//サウンドの終了
	UninitSound();

	UninitTexture();

	// レンダリングの終了処理
	UninitRenderer();

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
//#ifdef _DEBUG
//	//カーソルを左上に移動
//	SetConsoleCursorPosition(Console, CursorPos);
//#endif
	//入力処理の更新処理 常に入力されたを見ているため
	UpdateInput();
	//
	Keyboard_GetState();
	//コントローラーとキーボード入力をまとめて確認する為に必要
	UpdateIoEx();

	UpdatePolygon();	//ポリゴンの更新


	switch (g_scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		UpdateCollision(); //当たり判定の更新
	
		break;
	case SCENE_GAMEOVER:
		UpdateGameOver();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;

	case SCENE_STAGESELECT:
		UpdateStageSelect();
		break;

	case SCENE_MANUAL:
		UpdateManual();
		break;
	}

	// UIの更新
	UpdateUI();

	UpdateFade();

	if (stage_lock_mode == false)
	{
		stage_open = 8;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{

	// バックバッファクリア
	Clear();

	// 2D描画なので深度無効
	SetDepthEnable(false);

	DrawPolygon();		//ポリゴンの描画


	switch (g_scene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_GAME:

		DrawGame();
		
		break;
	case SCENE_GAMEOVER:
		DrawGameOver();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;

	case SCENE_STAGESELECT:
		DrawStageSelect();
		break;

	case SCENE_MANUAL:
		DrawManual();
		break;
	}

	// UIの描画
	DrawUI();

	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}

void SetScene(SCENE scene)
{
	std::cout << "Init回数チェック" << std::endl;
	switch (g_scene)
	{
	case SCENE_TITLE:
		UnInitTitle();
		UnInitUI();
		break;

	case SCENE_GAME:
		UnInitGame();
		UnInitUI();
		break;

	case SCENE_GAMEOVER:
		UnInitGameOver();
		UnInitUI();
		break;

	case SCENE_RESULT:
		UnInitResult();
		UnInitUI();
		break;

	case SCENE_STAGESELECT:
		UnInitStageSelect();
		UnInitUI();
		break;

	case SCENE_MANUAL:
		UnInitManual();
		UnInitUI();
		break;

	default:
		break;
	}

	//シーンの切り替え

	g_scene = scene;

	//各初期化
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitle();
		InitUI();
		break;

	case SCENE_GAME:
		InitGame();
		InitUI();
		break;

	case SCENE_GAMEOVER:
		InitGameOver();
		InitUI();
		break;

	case SCENE_RESULT:
		InitResult();
		InitUI();
		break;

	case SCENE_STAGESELECT:
		InitStageSelect();
		break;

	case SCENE_MANUAL:
		InitManual();
		break;

	default:
		break;
	}

}

SCENE GetScene(void)
{
	return g_scene;
}

void SetStageOpen(int stageopen)
{
	stage_open = stageopen;
}

int GetStageOpen()
{
	return stage_open;
}

void SetStageLockMode(bool lockmode)
{
	stage_lock_mode = lockmode;
}

bool GetStageLockMode()
{
	return stage_lock_mode;
}
