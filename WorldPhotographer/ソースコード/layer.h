//=============================================================================
//layer.h
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#pragma once

#include "main.h"
#include "renderer.h"

#include "mapchip.h"
//====================================
//�}�N����`
//====================================
#define LAYER_MAX (3)					//���C���[�̍ő喇��

#define LAYER_SIZE_W (SCREEN_WIDTH)		//���C���[�̉���
#define	LAYER_SIZE_H (SCREEN_HEIGHT)	//���C���[�̏c��

#define	LAYER_CHIP_NUM_HEIGHT (SCREEN_HEIGHT / MAPCHIP_HEIGHT)	//���C���[�̏c�̃`�b�v�� 18
#define	LAYER_CHIP_NUM_WIDTH (SCREEN_WIDTH / MAPCHIP_WIDTH)	//���C���[�̉��̃`�b�v�� 32

//====================================
//�}�N����`(���C���[�̔w�i�ƃ}�b�v�`�b�v�̒�`)
//====================================
#define LAYER_BG_01_00 ((char*)"data\\texture\\World1\\BG_Forest_Sky.png")	//�w�i�f�[�^(��Ԍ��̋�)			
#define LAYER_BG_01_01 ((char*)"data\\texture\\World1\\BG_Forest_Forward.png")	//�w�i�f�[�^�i���C���[�P�j		
#define LAYER_BG_01_02 ((char*)"data\\texture\\World1\\BG_Forest_Middle.png")	//�w�i�f�[�^�i���C���[�Q�j
#define LAYER_BG_01_03 ((char*)"data\\texture\\World1\\BG_Forest_Behind.png")	//�w�i�f�[�^�i���C���[�R�j

#define LAYER_BG_02_00 ((char*)"data\\texture\\World2\\BG_Desert_Sky.png")	//�w�i�f�[�^(��Ԍ��̋�)				
#define LAYER_BG_02_01 ((char*)"data\\texture\\World2\\BG_Desert_Forward.png")	//�w�i�f�[�^�i���C���[�P�j			
#define LAYER_BG_02_02 ((char*)"data\\texture\\World2\\BG_Desert_Middle.png")	//�w�i�f�[�^�i���C���[�Q�j
#define LAYER_BG_02_03 ((char*)"data\\texture\\World2\\BG_Desert_Behind.png")	//�w�i�f�[�^�i���C���[�R�j

#define LAYER_BG_03_00 ((char*)"data\\texture\\World3\\BG_Snow_Sky.png")	//�w�i�f�[�^(��Ԍ��̋�)				
#define LAYER_BG_03_01 ((char*)"data\\texture\\World3\\BG_Snow_Forward.png")	//�w�i�f�[�^�i���C���[�P�j		
#define LAYER_BG_03_02 ((char*)"data\\texture\\World3\\BG_Snow_Middle.png")	//�w�i�f�[�^�i���C���[�Q�j
#define LAYER_BG_03_03 ((char*)"data\\texture\\World3\\BG_Snow_Behind.png")	//�w�i�f�[�^�i���C���[�R�j



static	ID3D11ShaderResourceView* g_LayerTexture;//�摜1����1�̕ϐ����K�v
static	char* g_LayerTextureName0 = LAYER_BG_01_00;//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_LayerTextureName1 = LAYER_BG_01_01;//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_LayerTextureName2 = LAYER_BG_01_02;//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_LayerTextureName3 = LAYER_BG_01_03;//�e�N�X�`���t�@�C���p�X JPG BMP PNG



//=============================================
//��ʃJ�����̃��C���[
//=============================================
#define LAYER_MC_1_1_01 ((char*)"data\\stage\\�X�e�[�W1-1\\CMC1_1_1.txt")	//���C���[�f�[�^
#define LAYER_MC_1_1_02 ((char*)"data\\stage\\�X�e�[�W1-1\\CMC1_1_2.txt")	
#define LAYER_MC_1_1_03 ((char*)"data\\stage\\�X�e�[�W1-1\\CMC1_1_3.txt")	

#define LAYER_MC_1_2_01 ((char*)"data\\stage\\�X�e�[�W1-2\\CMC1_2_1.txt")	
#define LAYER_MC_1_2_02 ((char*)"data\\stage\\�X�e�[�W1-2\\CMC1_2_2.txt")	
#define LAYER_MC_1_2_03 ((char*)"data\\stage\\�X�e�[�W1-2\\CMC1_2_3.txt")	

#define LAYER_MC_1_3_01 ((char*)"data\\stage\\�X�e�[�W1-3\\CMC1_3_1.txt")	
#define LAYER_MC_1_3_02 ((char*)"data\\stage\\�X�e�[�W1-3\\CMC1_3_2.txt")	
#define LAYER_MC_1_3_03 ((char*)"data\\stage\\�X�e�[�W1-3\\CMC1_3_3.txt")	

#define LAYER_MC_2_1_01 ((char*)"data\\stage\\�X�e�[�W2-1\\CMC2_1_1.txt")	
#define LAYER_MC_2_1_02 ((char*)"data\\stage\\�X�e�[�W2-1\\CMC2_1_2.txt")	
#define LAYER_MC_2_1_03 ((char*)"data\\stage\\�X�e�[�W2-1\\CMC2_1_3.txt")

#define LAYER_MC_2_2_01 ((char*)"data\\stage\\�X�e�[�W2-2\\CMC2_2_1.txt")	
#define LAYER_MC_2_2_02 ((char*)"data\\stage\\�X�e�[�W2-2\\CMC2_2_2.txt")	
#define LAYER_MC_2_2_03 ((char*)"data\\stage\\�X�e�[�W2-2\\CMC2_2_3.txt")	

#define LAYER_MC_2_3_01 ((char*)"data\\stage\\�X�e�[�W2-3\\CMC2_3_1.txt")	
#define LAYER_MC_2_3_02 ((char*)"data\\stage\\�X�e�[�W2-3\\CMC2_3_2.txt")	
#define LAYER_MC_2_3_03 ((char*)"data\\stage\\�X�e�[�W2-3\\CMC2_3_3.txt")	

#define LAYER_MC_3_1_01 ((char*)"data\\stage\\�X�e�[�W3-1\\CMC3_1_1.txt")	
#define LAYER_MC_3_1_02 ((char*)"data\\stage\\�X�e�[�W3-1\\CMC3_1_2.txt")	
#define LAYER_MC_3_1_03 ((char*)"data\\stage\\�X�e�[�W3-1\\CMC3_1_3.txt")	

#define LAYER_MC_3_2_01 ((char*)"data\\stage\\�X�e�[�W3-2\\CMC3_2_1.txt")	
#define LAYER_MC_3_2_02 ((char*)"data\\stage\\�X�e�[�W3-2\\CMC3_2_2.txt")	
#define LAYER_MC_3_2_03 ((char*)"data\\stage\\�X�e�[�W3-2\\CMC3_2_3.txt")	

#define LAYER_MC_3_3_01 ((char*)"data\\stage\\�X�e�[�W3-3\\CMC3_3_1.txt")	
#define LAYER_MC_3_3_02 ((char*)"data\\stage\\�X�e�[�W3-3\\CMC3_3_2.txt")	
#define LAYER_MC_3_3_03 ((char*)"data\\stage\\�X�e�[�W3-3\\CMC3_3_3.txt")	

//=============================================
//�Œ�J�����̃��C���[
//=============================================

#define K_LAYER_MC_1_1_01 ((char*)"data\\stage\\�X�e�[�W1-1\\KMC1_1_1_1.txt")	//���C���[�f�[�^
#define K_LAYER_MC_1_1_02 ((char*)"data\\stage\\�X�e�[�W1-1\\KMC1_1_2_1.txt")	

#define K_LAYER_MC_1_2_01 ((char*)"data\\stage\\�X�e�[�W1-2\\KMC1_2_1_1.txt")	
#define K_LAYER_MC_1_2_02 ((char*)"data\\stage\\�X�e�[�W1-2\\KMC1_2_2_1.txt")	


#define K_LAYER_MC_1_3_01 ((char*)"data\\stage\\�X�e�[�W1-3\\KMC1_3_1_1.txt")	
#define K_LAYER_MC_1_3_02 ((char*)"data\\stage\\�X�e�[�W1-3\\KMC1_3_2_1.txt")	


#define K_LAYER_MC_2_1_01 ((char*)"data\\stage\\�X�e�[�W2-1\\KMC2_1_1_1.txt")	
#define K_LAYER_MC_2_1_02 ((char*)"data\\stage\\�X�e�[�W2-1\\KMC2_1_1_2.txt")	
#define K_LAYER_MC_2_1_03 ((char*)"data\\stage\\�X�e�[�W2-1\\KMC2_1_2_1.txt")	
#define K_LAYER_MC_2_1_04 ((char*)"data\\stage\\�X�e�[�W2-1\\KMC2_1_2_2.txt")	


#define K_LAYER_MC_2_2_01 ((char*)"data\\stage\\�X�e�[�W2-2\\KMC2_2_1_1.txt")	
#define K_LAYER_MC_2_2_02 ((char*)"data\\stage\\�X�e�[�W2-2\\KMC2_2_1_2.txt")	
#define K_LAYER_MC_2_2_03 ((char*)"data\\stage\\�X�e�[�W2-2\\KMC2_2_2_1.txt")	
#define K_LAYER_MC_2_2_04 ((char*)"data\\stage\\�X�e�[�W2-2\\KMC2_2_2_2.txt")	

#define K_LAYER_MC_2_3_01 ((char*)"data\\stage\\�X�e�[�W2-3\\KMC2_3_1_1.txt")	
#define K_LAYER_MC_2_3_02 ((char*)"data\\stage\\�X�e�[�W2-3\\KMC2_3_1_2.txt")	
#define K_LAYER_MC_2_3_03 ((char*)"data\\stage\\�X�e�[�W2-3\\KMC2_3_2_1.txt")
#define K_LAYER_MC_2_3_04 ((char*)"data\\stage\\�X�e�[�W2-3\\KMC2_3_2_2.txt")	

#define K_LAYER_MC_3_1_01 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_1_1.txt")	
#define K_LAYER_MC_3_1_02 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_1_2.txt")	
#define K_LAYER_MC_3_1_03 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_1_3.txt")
#define K_LAYER_MC_3_1_04 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_2_1.txt")	
#define K_LAYER_MC_3_1_05 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_2_2.txt")	
#define K_LAYER_MC_3_1_06 ((char*)"data\\stage\\�X�e�[�W3-1\\KMC3_1_2_3.txt")	

#define K_LAYER_MC_3_2_01 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_1_1.txt")	
#define K_LAYER_MC_3_2_02 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_1_2.txt")	
#define K_LAYER_MC_3_2_03 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_1_3.txt")
#define K_LAYER_MC_3_2_04 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_2_1.txt")	
#define K_LAYER_MC_3_2_05 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_2_2.txt")	
#define K_LAYER_MC_3_2_06 ((char*)"data\\stage\\�X�e�[�W3-2\\KMC3_2_2_3.txt")	

#define K_LAYER_MC_3_3_01 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_1_1.txt")	
#define K_LAYER_MC_3_3_02 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_1_2.txt")	
#define K_LAYER_MC_3_3_03 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_1_3.txt")
#define K_LAYER_MC_3_3_04 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_2_1.txt")	
#define K_LAYER_MC_3_3_05 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_2_2.txt")	
#define K_LAYER_MC_3_3_06 ((char*)"data\\stage\\�X�e�[�W3-3\\KMC3_3_2_3.txt")	




static	char* g_LayerMapchipName1 = LAYER_MC_1_1_01;//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_LayerMapchipName2 = LAYER_MC_1_1_01;//�e�N�X�`���t�@�C���p�X JPG BMP PNG
static	char* g_LayerMapchipName3 = LAYER_MC_1_1_01;//�e�N�X�`���t�@�C���p�X JPG BMP PNG

struct LAYER
{
	bool use;		//�\���̗��p���t���O
	float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f);
	float texno;    //�e�N�X�`���C���f�b�N�X

	//�}�b�v�`�b�v��������
	CHIP chip[NUM_CHIP_ALL];
	int mapChipList[LAYER_CHIP_NUM_HEIGHT][LAYER_CHIP_NUM_WIDTH];
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitLayer();
void    UnInitLayer();
void    DrawLayer();
void    UpdateLayer();
LAYER* GetLayer(); //LAYER�\���̂̐擪�|�C���^���擾
bool	GetLayerCanGet();//���݂��ʐ^���B��邩�ǂ�����Ԃ�

void	SetLayerBGMC(char* name0, char* name1, char* name2, char* name3, char* name4, char* name5, char* name6);
void	SetLayerBG(char* name0, char* name1, char* name2, char* name3);

void	SetLayerMC_01(char* name1);
void	SetLayerMC_02(char* name1, char* name2);
void	SetLayerMC_03(char* name1, char* name2, char* name3);

//�}�b�v�`�b�v9�Ԃ̃X�N���[���X�g�b�v�̃^�C�~���O��
//���C���[��؂�ւ���֐�
//��ʃ��C���[���Œ背�C���[
void	SetLayerNextMC09();

//�}�b�v�`�b�v10�Ԃ̃X�N���[���X�g�b�v�����̃^�C�~���O��
//���C���[��؂�ւ���֐�
//�Œ背�C���[����ʃ��C���[
void	SetLayerNextMC10();

