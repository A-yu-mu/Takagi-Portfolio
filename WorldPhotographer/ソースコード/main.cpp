/*==============================================================================

   DirectX�̏����� [main.cpp]
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
// ���C�u�����̃����N
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//#ifdef _DEBUG
//int		g_CountFPS;							// FPS�J�E���^
//char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p
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
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
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
	
	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG			msg;

	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
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
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
//#ifdef _DEBUG
//				g_CountFPS = dwFrameCount;
//#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�
				
				
//#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
//				wsprintf(g_DebugStr, WINDOW_CAPTION);
//				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
//				SetWindowText(hWnd, g_DebugStr);
//#endif

				Update();			// �X�V����
				Draw();				// �`�揈��

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z

			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "��߂Ȃ��Ł[", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
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
// ����������
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

	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);

	InitPolygon();//�|���S���̏�����

	//���͏���������
	InitInput(hInstance, hWnd);
	Keyboard_Initialize();
	
	//�T�E���h�̏�����
	InitSound(hWnd);

	//�R���g���[���[�ƃL�[�{�[�h���͂��܂Ƃ߂Ċm�F����ׂɕK�v
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

	// UI�̏�����
	InitUI();


//	SetScene(SCENE_TITLE);

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
//#ifdef _DEBUG
//	//�R���\�[�����
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
	// UI�̏I��
	UnInitUI();

	UninitPolygon();	//�|���S���̏I������

	//���͏����̏I������
	UninitInput();

	//�T�E���h�̏I��
	UninitSound();

	UninitTexture();

	// �����_�����O�̏I������
	UninitRenderer();

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
//#ifdef _DEBUG
//	//�J�[�\��������Ɉړ�
//	SetConsoleCursorPosition(Console, CursorPos);
//#endif
	//���͏����̍X�V���� ��ɓ��͂��ꂽ�����Ă��邽��
	UpdateInput();
	//
	Keyboard_GetState();
	//�R���g���[���[�ƃL�[�{�[�h���͂��܂Ƃ߂Ċm�F����ׂɕK�v
	UpdateIoEx();

	UpdatePolygon();	//�|���S���̍X�V


	switch (g_scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		UpdateCollision(); //�����蔻��̍X�V
	
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

	// UI�̍X�V
	UpdateUI();

	UpdateFade();

	if (stage_lock_mode == false)
	{
		stage_open = 8;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{

	// �o�b�N�o�b�t�@�N���A
	Clear();

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	DrawPolygon();		//�|���S���̕`��


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

	// UI�̕`��
	DrawUI();

	DrawFade();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}

void SetScene(SCENE scene)
{
	std::cout << "Init�񐔃`�F�b�N" << std::endl;
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

	//�V�[���̐؂�ւ�

	g_scene = scene;

	//�e������
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
