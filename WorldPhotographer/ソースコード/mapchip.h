#pragma once

#include "main.h"
#include "string"
#include <map>

//====================================
//�}�N����`
//====================================

const int MAPCHIP_WIDTH = 30;				// �}�b�v�`�b�v�̉���
const int MAPCHIP_HEIGHT = 30;					// �}�b�v�`�b�v�̏c��
const int CHIP_NUM_WIDTH = 500;		// MAP�̉���(�l�̓`�b�v��)
const int CHIP_NUM_HEIGHT = 500;		// MAP�̏c��(�l�̓`�b�v��) <18
const int MAP_SIZE_WIDTH = CHIP_NUM_WIDTH * MAPCHIP_WIDTH;
const int MAP_SIZE_HEIGHT = CHIP_NUM_HEIGHT * MAPCHIP_HEIGHT;
const int NUM_CHIP_ALL = CHIP_NUM_WIDTH * CHIP_NUM_HEIGHT; //<162 
static	ID3D11ShaderResourceView* g_TextureChip;//�摜1����1�̕ϐ����K�v
static	ID3D11ShaderResourceView* g_TextureChip1;
static	ID3D11ShaderResourceView* g_TextureChip2;
static	ID3D11ShaderResourceView* g_TextureChip3;
static	ID3D11ShaderResourceView* g_TextureChip4;
static	ID3D11ShaderResourceView* g_TextureChip5;
static	ID3D11ShaderResourceView* g_TextureChip6;
static	ID3D11ShaderResourceView* g_TextureChip7;
static	ID3D11ShaderResourceView* g_TextureChip8;
static	ID3D11ShaderResourceView* g_TextureChip9;


static std::map <int, char*> mapchip;




static	char* g_TextureNameAir = (char*)"data\\texture\\chip1.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_TextureNameGrassChip = (char*)"data\\texture\\Forest_GroundTopM_64_v01.png";
static	char* g_TextureNameCannon = (char*)"data\\texture\\cannon.png";
static	char* g_TextureNameJumppad = (char*)"data\\texture\\Forest_Jump_64_v01.png";
static	char* g_TextureNameSpike = (char*)"data\\texture\\Forest_Spike02_64_v01.png";
static	char* g_TextureNameDoor = (char*)"data\\texture\\Forest_Door.png";
static	char* g_TextureNameKey = (char*)"data\\texture\\Forest_key.png";
static	char* g_TextureNameSwitch = (char*)"data\\texture\\Forest_Switch_onandoff_01_64_v01.png";
static	char* g_TextureGoal = (char*)"data\\texture\\Flag_01.png";




enum class CHIP_TYPE
{
	TYPE_0 = 0,
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_4,
	TYPE_5,
	TYPE_6,
	TYPE_7,
	TYPE_8,
	TYPE_9,
	TYPE_10,
	TYPE_11,
	TYPE_12,
	TYPE_13,
	TYPE_14,
	TYPE_15,
	TYPE_16,
	TYPE_17,
	TYPE_18,
	TYPE_19,
	TYPE_20,
	TYPE_21,//���E�ړ��E�W�����v�J�n
	TYPE_22,//���E�ړ��E�W�����v�I��
	TYPE_23,//�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�J�n
	TYPE_24,//�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�I��
	TYPE_25,////�v���C���[�Ă��t���J�n
	TYPE_26,////�v���C���[�Ă��t���I��
	TYPE_27,//�J�����N���J�n
	TYPE_28,//�J�����N���I��
	TYPE_MAX
};

struct CHIP//�`�b�v�\����
{
	D3DXVECTOR2 pos;    //���W
	D3DXVECTOR2 originChipPos; //���̍��W
	D3DXVECTOR2 size;  //�T�C�Y
	CHIP_TYPE type;
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;
	bool use;
	bool collision;

	bool movesp;

	int move;
};





//====================================
//�v���g�^�C�v�錾
//====================================

HRESULT InitMapchip(std::string mapdata);
void UninitMapchip();
void    DrawMapchip();
void    UpdateMapchip();


CHIP* GetChip();
int* GetMapChipList(int n, int w);		//�񎟌��z��̃Q�b�^�[�͍��Ȃ��̂Ŏw�肵���s��Ԃ��悤�ɂ��܂���

void ChipGimmick(int i);
void ChipGimmickColUp(int i);
void ChipGimmickColOthers(int i);
void PlayerAfterChipGimmick(int i);
bool GetSwitchOn();
bool GetTutorial1();
bool GetTutorial2();
bool GetTutorial3();
bool GetTutorial4();
void SetTutorial1(bool set_tutorial_1);
void SetTutorial2(bool set_tutorial_2);
void SetTutorial3(bool set_tutorial_3);
void SetTutorial4(bool set_tutorial_4);
void SetSwitchOn(bool b);
void SetAISwitch(bool b);