#include "io_ex.h"

#define STICK_DEADZONE (0.25f)//スティックの遊び（どこまでは入力を無視するか）

//現在と前回の判定
//[0]は現在の判定、[1]は古い判定
enum NOW_OLD
{
	NOW = 0,
	OLD,

	NOW_OLD_MAX//ボタンの判定の種類の最大数
};


//各判定のボタン判定
//ボタンの種類数(BUTTON_MAX)
//[0]は現在の判定、[1]は古い判定(NOW_OLD_MAX)
bool b[BUTTON_MAX][NOW_OLD_MAX];


//音の番号
int BGM[BGM_MAX];
int SE[SE_MAX];



void InitIoEx()
{
	//全ての判定の初期化
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		for (int j = 0; j < NOW_OLD_MAX; j++)
		{
			b[i][j] = false;
		}
	}

	//音の設定一覧
	BGM[BGM_TITLE] = LoadSound((char*)"data/BGM/タイトルBGMmusmus.wav");
	BGM[BGM_STAGESELECT] = LoadSound((char*)"data/BGM/ステージセレクトBGMmusmus.wav");
	BGM[BGM_AREA01] = LoadSound((char*)"data/BGM/stage1musmus.wav");
	BGM[BGM_AREA02] = LoadSound((char*)"data/BGM/stage2.魔王魂.wav");
	BGM[BGM_AREA03] = LoadSound((char*)"data/BGM/stage3.DOVA.wav");
	
	
	SE[SE_OK] = LoadSound((char*)"data/SE/決定ボタンを押す40.wav");
	SE[SE_MOVECURSOR] = LoadSound((char*)"data/SE/カーソル移動3.wav");
	SE[SE_JUMP] = LoadSound((char*)"data/SE/jump01.wav");
	SE[SE_JUMPUP] = LoadSound((char*)"data/SE/jump06.wav");
	SE[SE_DAMAGE] = LoadSound((char*)"data/SE/damage3.wav");
	SE[SE_GET_KEY] = LoadSound((char*)"data/SE/決定ボタンを押す20.wav");
	SE[SE_USE_KYE] = LoadSound((char*)"data/SE/決定ボタンを押す21.wav");
	SE[SE_SWITCH_ON] = LoadSound((char*)"data/SE/決定ボタンを押す31.wav");
	SE[SE_SWITCH_OFF] = LoadSound((char*)"data/SE/決定ボタンを押す32.wav");
	SE[SE_SHUTTER] = LoadSound((char*)"data/SE/Shutter.wav");
	SE[SE_FANFARE] = LoadSound((char*)"data/SE/リザルトジングル.wav");
	SE[SE_BOOING] = LoadSound((char*)"data/SE/defend001.wav");
	SE[SE_SHELL] = LoadSound((char*)"data/SE/shot001.wav");
	SE[SE_AFTERIMAGE_ON] = LoadSound((char*)"data/SE/可愛いジャンプ.wav");
	SE[SE_AFTERIMAGE_OFF] = LoadSound((char*)"data/SE/キャンセル5.wav");
	SE[SE_PHOTO_ON] = LoadSound((char*)"data/SE/laser000.wav");
	SE[SE_PHOTO_OFF] = LoadSound((char*)"data/SE/決定ボタンを押す33.wav");
	SE[SE_LANDING] = LoadSound((char*)"data/SE/ジャンプの着地.wav");
	SE[SE_PAUSE_ON] = LoadSound((char*)"data/SE/決定ボタンを押す44.wav");
	SE[SE_PAUSE_OFF] = LoadSound((char*)"data/SE/決定ボタンを押す44.wav");
	SE[SE_SKELETON_DELETE] = LoadSound((char*)"data/SE/決定(ピキィ).wav");
	SE[SE_SKELETON_REBORN] = LoadSound((char*)"data/SE/決定ボタンを押す12.wav");
	SE[SE_PINTO] = LoadSound((char*)"data/SE/決定ボタンを押す7.wav");
	SE[SE_TURN] = LoadSound((char*)"data/SE/ピント調整.wav");
	SE[SE_PHOTORETI_MOVE] = LoadSound((char*)"data/SE/カーソル移動8.wav");



	//SetVolume(BGM[BGM_01], 0.3f);
	//SetVolume(SE[SE_FIRE], 0.3f);
	//SetVolume(SE[SE_CRASH], 1.0f);
	//SetVolume(SE[SE_OP], 0.3f);
	//SetVolume(SE[SE_ED], 0.5f);

}

void UpdateIoEx()
{
	//前回の判定を記憶する
	//[0]は現在の判定、[1]は古い判定
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		
		b[i][OLD] = b[i][NOW];
		
	}

	//現在のボタンの情報を確認し、現在の判定を更新する
	b[L_UP][NOW] = (Keyboard_IsKeyDown(KK_W) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_UP) || GetThumbLeftY(0) > +STICK_DEADZONE);
	b[L_DOWN][NOW] = (Keyboard_IsKeyDown(KK_S) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_DOWN) || GetThumbLeftY(0) < -STICK_DEADZONE);
	b[L_LEFT][NOW] = (Keyboard_IsKeyDown(KK_A) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_LEFT) || GetThumbLeftX(0) < -STICK_DEADZONE);
	b[L_RIGHT][NOW] = (Keyboard_IsKeyDown(KK_D) || IsButtonPressed(0, XINPUT_GAMEPAD_DPAD_RIGHT) || GetThumbLeftX(0) > +STICK_DEADZONE);
	b[R_UP][NOW] = (Keyboard_IsKeyDown(KK_UP) || GetThumbRightY(0) > +STICK_DEADZONE);
	b[R_DOWN][NOW] = (Keyboard_IsKeyDown(KK_DOWN) || GetThumbRightY(0) < -STICK_DEADZONE);
	b[R_LEFT][NOW] = (Keyboard_IsKeyDown(KK_LEFT) || GetThumbRightX(0) < -STICK_DEADZONE);
	b[R_RIGHT][NOW] = (Keyboard_IsKeyDown(KK_RIGHT) || GetThumbRightX(0) > +STICK_DEADZONE);
	b[A][NOW] = (Keyboard_IsKeyDown(KK_SPACE) || IsButtonPressed(0, XINPUT_GAMEPAD_A) || IsButtonPressed(0, XINPUT_GAMEPAD_B));//決定、ジャンプ
	//b[B][NOW] = (Keyboard_IsKeyDown(KK_ENTER));//
	b[X][NOW] = (Keyboard_IsKeyDown(KK_Q) || IsButtonPressed(0, XINPUT_GAMEPAD_X));//カメラモード
	b[Y][NOW] = (Keyboard_IsKeyDown(KK_Q) || IsButtonPressed(0, XINPUT_GAMEPAD_Y));//焼き付けの削除、焼き付け作成
	b[L1][NOW] = (Keyboard_IsKeyDown(KK_E) || IsButtonPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER));//
	b[R1][NOW] = (Keyboard_IsKeyDown(KK_ENTER) || IsButtonPressed(0, XINPUT_GAMEPAD_RIGHT_SHOULDER));//マップでの写真の貼り付け、カメラモードでの切り取り
	b[START][NOW] = (Keyboard_IsKeyDown(KK_TAB) || IsButtonPressed(0, XINPUT_GAMEPAD_START));//ポーズ

}


//指定したボタンと入力形式に応じてboolを返す
bool IsButton(BUTTON_TYPE type, ACT act)
{
	switch (act)
	{
	case PUSH:
		return b[type][NOW];
		break;
	case TRIGGER:
		if (b[type][NOW] == true && b[type][OLD] == false)
			return true;
		else
			return false;
		break;
	case RELEASE:
		if (b[type][NOW] == false && b[type][OLD] == true)
			return true;
		else
			return false;
		break;

	case ACT_MAX:
		break;
	default:
		break;
	}
}


void PlayBGM(BGM_TYPE index)
{
	PlaySound(BGM[index], -1);
}

void PlaySE(SE_TYPE index)
{
	PlaySound(SE[index], 0);
}


