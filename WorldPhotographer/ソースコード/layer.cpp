//=============================================================================
//layer.cpp
// �쐬�ҁF�ڍ�@�쐬���F2022/10/22
//=============================================================================

#include "layer.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "pinto.h"

//�}�b�v�`�b�v�p
#include <fstream>
#include <iostream>

//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================
//���C���[�̒��̃}�b�v�`�b�v�̏����l�V��(Draw�����Ԃ��łœ�ڂ����݂��܂�)
HRESULT	InitLayerMapchip();
void	UninitLayerMapchip();
void	DrawLayerMapchip();
void	DrawLayerMapchipGap();
void	UpdateLayerMapchip();


//===================================
//�O���[�o���ϐ�
//===================================
static LAYER g_gb_layer;				//�w�i�̕\���p���C���[(�����ڂ����p)
static LAYER g_layer;					//���݂̕\�����C���[�i�Q�b�^�[�ŕԂ��p�j
static LAYER g_sub_layer[LAYER_MAX];	//�T�u���C���[�A���݂̖ʂ̗p�ӂ��Ă��郌�C���[�S�āi�Q�b�^�[�ł͕Ԃ��Ȃ��j

//�����B�e�\���ǂ������f����t���O
bool g_Layer_canget_flag;

//�s���g�̂����i�M���b�v�j���Ǘ�����ϐ�
float g_gap;

//�}�b�v�`�b�v�̏����ɕK�v
using namespace std;


int g_LayerMapChipList[CHIP_NUM_HEIGHT][CHIP_NUM_WIDTH];

//int g_LayerMapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];



//===================================
//������
//===================================
HRESULT InitLayer()
{

	//�w�i���C���[�̏�����
	g_gb_layer.pos.x = SCREEN_WIDTH / 2;
	g_gb_layer.pos.y = SCREEN_HEIGHT / 2;

	g_gb_layer.w = LAYER_SIZE_W;
	g_gb_layer.h = LAYER_SIZE_H;

	g_gb_layer.rot = 0.0f;
	g_gb_layer.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_gb_layer.use = true;
	g_gb_layer.texno = LoadTexture(g_LayerTextureName0);
	//���C���[�̏�����
	g_layer.pos.x = SCREEN_WIDTH / 2;
	g_layer.pos.y = SCREEN_HEIGHT / 2;

	g_layer.w = LAYER_SIZE_W;
	g_layer.h = LAYER_SIZE_H;

	g_layer.rot = 0.0f;
	g_layer.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.125f);
	g_layer.use = true;
	g_layer.texno = LoadTexture(g_LayerTextureName1);
	//�T�u���C���[�̏�����
	g_sub_layer[0].pos.x = SCREEN_WIDTH / 2;
	g_sub_layer[0].pos.y = SCREEN_HEIGHT / 2;

	g_sub_layer[0].w = LAYER_SIZE_W;
	g_sub_layer[0].h = LAYER_SIZE_H;

	g_sub_layer[0].rot = 0.0f;
	g_sub_layer[0].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.125f);
	g_sub_layer[0].use = true;
	g_sub_layer[0].texno = LoadTexture(g_LayerTextureName1);


	g_sub_layer[1].pos.x = SCREEN_WIDTH / 2;
	g_sub_layer[1].pos.y = SCREEN_HEIGHT / 2;

	g_sub_layer[1].w = LAYER_SIZE_W;
	g_sub_layer[1].h = LAYER_SIZE_H;

	g_sub_layer[1].rot = 0.0f;
	g_sub_layer[1].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.125f);
	g_sub_layer[1].use = true;
	g_sub_layer[1].texno = LoadTexture(g_LayerTextureName2);


	g_sub_layer[2].pos.x = SCREEN_WIDTH / 2;
	g_sub_layer[2].pos.y = SCREEN_HEIGHT / 2;

	g_sub_layer[2].w = LAYER_SIZE_W;
	g_sub_layer[2].h = LAYER_SIZE_H;

	g_sub_layer[2].rot = 0.0f;
	g_sub_layer[2].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.125f);
	g_sub_layer[2].use = true;
	g_sub_layer[2].texno = LoadTexture(g_LayerTextureName3);


	//�t���O�̏�����
	g_Layer_canget_flag = false;

	//�M���b�v�̏�����
	g_gap = 0.0f;

	//�}�b�v�`�b�v�̏�����
	InitLayerMapchip();

	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitLayer()
{
	//�}�b�v�`�b�v�̏�����
	UninitLayerMapchip();

}


//===================================
//�`��
//===================================
void    DrawLayer()
{
	//���C���[�\��
	if (g_gb_layer.use == true)
	{
		//�e�N�X�`���̕\��(��Ԍ��̋�)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gb_layer.texno));
		//�X�v���C�g�\��
		DrawSpriteColorRotation(
			g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
			g_gb_layer.rot, g_gb_layer.Color, 1, 1, 1, 1);

		//�s���g�̍ő吔�ɍ��킹�Ĕw�i�̕`���ς���
		if (g_layer.texno == g_sub_layer[0].texno)//���C���[�P�̏ꍇ
		{
			//�e�N�X�`���̕\��(���C���[�R)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[2].texno));
			//�X�v���C�g�\��
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);
			//�e�N�X�`���̕\��(���C���[�Q)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[1].texno));
			//�X�v���C�g�\��
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);

		}
		else if (g_layer.texno == g_sub_layer[1].texno)//���C���[�Q�̏ꍇ
		{
			//�e�N�X�`���̕\��(���C���[�R)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[2].texno));
			//�X�v���C�g�\��
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);

		}
		else if (g_layer.texno == g_sub_layer[2].texno)//���C���[�R�̏ꍇ
		{

		}


	}
	//���C���[�\��
	if (g_layer.use == true)
	{
		//�e�N�X�`���̕\��
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_layer.texno));

		//8�񂸂炵�ĕ\������
		D3DXVECTOR2 gap;
		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 0: gap = D3DXVECTOR2(-g_gap, -g_gap); break;
			case 1: gap = D3DXVECTOR2(-g_gap, +g_gap); break;
			case 2: gap = D3DXVECTOR2(+g_gap, -g_gap); break;
			case 3: gap = D3DXVECTOR2(+g_gap, +g_gap); break;
			case 4: gap = D3DXVECTOR2(0.0f, -g_gap * 2); break;
			case 5: gap = D3DXVECTOR2(0.0f, +g_gap * 2); break;
			case 6: gap = D3DXVECTOR2(-g_gap * 2, 0.0f); break;
			case 7: gap = D3DXVECTOR2(+g_gap * 2, 0.0f); break;
			default: break;
			}
			//�X�v���C�g�\��
			DrawSpriteColorRotation(
				g_layer.pos.x + gap.x, g_layer.pos.y + gap.y,
				g_layer.w, g_layer.h,
				g_layer.rot, g_layer.Color, 1, 1, 1, 1);
		}

	}
	if (g_Layer_canget_flag == true)
	{
		//�}�b�v�`�b�v�̕`��
		DrawLayerMapchip();
	}
	else
	{
		//�}�b�v�`�b�v�̕`��i�Ԃ�Łj
		DrawLayerMapchipGap();
	}

}


//===================================
//�X�V
//===================================
void    UpdateLayer()
{
	//�s���g�̏�Ԃ��m�F���ău�����ς���
	PINTO* p_pinto = GetPinto();
	float layer1 = 0.0f;	//���C���[�P�̂��傤�ǈʒu
	float layer2 = 0.0f;	//���C���[�Q�̂��傤�ǈʒu
	float layer3 = 0.0f;	//���C���[�R�̂��傤�ǈʒu
	//�s���g�̈ʒu�����傤�ǂ̈ʒu���v�Z���ċ��߂�s
	layer1 = p_pinto->change1pos / 2;
	layer2 = p_pinto->change1pos + ((p_pinto->change2pos - p_pinto->change1pos) / 2);
	layer3 = p_pinto->change2pos + ((p_pinto->maxpos - p_pinto->change2pos) / 2);

	//�����𖞂������̂݃}�b�v�`�b�v�\��
	if ((layer1 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer1 + PINTO_OKLINE / 2) ||
		(layer2 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer2 + PINTO_OKLINE / 2) ||
		(layer3 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer3 + PINTO_OKLINE / 2))
	{
		g_Layer_canget_flag = true;
		//�}�b�v�`�b�v�̍X�V
		UpdateLayerMapchip();
	}
	else
	{
		g_Layer_canget_flag = false;

	}

	//�M���b�v���v�Z����ׂɌ��݂̕\�����C���[���m�F���A���C���[�����X�V����
	if (p_pinto->nowpos <= p_pinto->change1pos)	//���C���[1�̏ꍇ
	{
		g_gap = layer1;
		g_layer = g_sub_layer[0];

	}
	else if (p_pinto->nowpos <= p_pinto->change2pos)	//���C���[2�̏ꍇ
	{
		g_gap = layer2;
		g_layer = g_sub_layer[1];

	}
	else if (p_pinto->nowpos <= p_pinto->maxpos)	//���C���[3�̏ꍇ
	{
		g_gap = layer3;
		g_layer = g_sub_layer[2];

	}
	//�M���b�v���v�Z����
	g_gap -= p_pinto->nowpos;


}

//===================================
//�v���C���[�\���̂̐擪�|�C���^���擾
//===================================
LAYER* GetLayer()
{
	return &g_layer;
}

bool GetLayerCanGet()
{
	return g_Layer_canget_flag;
}


//���C���[���̃}�b�v�`�b�v�̏����͂�����艺�ɏ����Ă���
HRESULT InitLayerMapchip()
{
	//�C�j�b�g�ł̓T�u���C���[�̂ݏ���������
	//�T�u���C���[�P
	{
		ifstream inputfile(g_LayerMapchipName1); //�t�@�C���ǂݍ���
		if (!inputfile.is_open())
			cout << "Error opening file";   //�ǂݍ��݃G���[�\��
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[0].mapChipList[r][c];  //�ǂݍ��񂾃t�@�C�����}�b�v�`�b�v���X�g�ɓ����
				g_sub_layer[0].chip[chip_type].type = (CHIP_TYPE)g_sub_layer[0].mapChipList[r][c];
				chip_type++;
			}
		}
		for (int i = 0; i < NUM_CHIP_ALL; i++)
		{
			g_sub_layer[0].chip[i].pos.x = 0;
			g_sub_layer[0].chip[i].pos.y = 0;

			g_sub_layer[0].chip[i].size.x = MAPCHIP_WIDTH;
			g_sub_layer[0].chip[i].size.y = MAPCHIP_HEIGHT;

			g_sub_layer[0].chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//g_sub_layer[0].chip[i].type = CHIP_TYPE::TYPE_1;
			/*g_sub_layer[0].chip[i].texno = LoadTexture(g_TextureNameChip);*/

			g_sub_layer[0].chip[i].use = true;
			g_sub_layer[0].chip[i].collision = false;
		}
	}

	//�T�u���C���[�Q
	{
		ifstream inputfile(g_LayerMapchipName2); //�t�@�C���ǂݍ���
		if (!inputfile.is_open())
			cout << "Error opening file";   //�ǂݍ��݃G���[�\��
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[1].mapChipList[r][c];  //�ǂݍ��񂾃t�@�C�����}�b�v�`�b�v���X�g�ɓ����
				g_sub_layer[1].chip[chip_type].type = (CHIP_TYPE)g_sub_layer[1].mapChipList[r][c];
				chip_type++;
			}
		}
		for (int i = 0; i < NUM_CHIP_ALL; i++)
		{
			g_sub_layer[1].chip[i].pos.x = 0;
			g_sub_layer[1].chip[i].pos.y = 0;

			g_sub_layer[1].chip[i].size.x = MAPCHIP_WIDTH;
			g_sub_layer[1].chip[i].size.y = MAPCHIP_HEIGHT;

			g_sub_layer[1].chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//g_sub_layer[1].chip[i].type = CHIP_TYPE::TYPE_1;
			/*g_sub_layer[1].chip[i].texno = LoadTexture(g_TextureNameChip);*/

			g_sub_layer[1].chip[i].use = true;
			g_sub_layer[1].chip[i].collision = false;
		}
	}
	//�T�u���C���[�R
	{
		ifstream inputfile(g_LayerMapchipName3); //�t�@�C���ǂݍ���
		if (!inputfile.is_open())
			cout << "Error opening file";   //�ǂݍ��݃G���[�\��
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[2].mapChipList[r][c];  //�ǂݍ��񂾃t�@�C�����}�b�v�`�b�v���X�g�ɓ����
				g_sub_layer[2].chip[chip_type].type = (CHIP_TYPE)g_sub_layer[2].mapChipList[r][c];
				chip_type++;
			}
		}
		for (int i = 0; i < NUM_CHIP_ALL; i++)
		{
			g_sub_layer[2].chip[i].pos.x = 0;
			g_sub_layer[2].chip[i].pos.y = 0;

			g_sub_layer[2].chip[i].size.x = MAPCHIP_WIDTH;
			g_sub_layer[2].chip[i].size.y = MAPCHIP_HEIGHT;

			g_sub_layer[2].chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//g_sub_layer[2].chip[i].type = CHIP_TYPE::TYPE_1;
			/*g_sub_layer[2].chip[i].texno = LoadTexture(g_TextureNameChip);*/

			g_sub_layer[2].chip[i].use = true;
			g_sub_layer[2].chip[i].collision = false;
		}
	}



	/*for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		g_layer.chip[i].pos.x = 0;
		g_layer.chip[i].pos.y = 0;

		g_layer.chip[i].size.x = MAPCHIP_WIDTH;
		g_layer.chip[i].size.y = MAPCHIP_HEIGHT;

		g_layer.chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_layer.chip[i].type = CHIP_TYPE::TYPE_1;
		g_layer.chip[i].texno = LoadTexture(g_TextureNameAir);

		g_layer.chip[i].use = true;
		g_layer.chip[i].collision = false;
	}*/

	return S_OK;

}
void UninitLayerMapchip()
{
}

void DrawLayerMapchip()
{
	CHIP* chip = GetChip();
	int j = 0;
	for (int y = 0; y < LAYER_CHIP_NUM_HEIGHT; y++)
	{
		for (int x = 0; x < LAYER_CHIP_NUM_WIDTH; x++)
		{
			int i = g_layer.mapChipList[y][x];
			g_layer.chip[j].pos.x = (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH / 2;
			g_layer.chip[j].pos.y = (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT / 2;

			if (g_layer.chip[j].use == true)
			{


				D3DXVECTOR2 scrpos = D3DXVECTOR2(0.0f, 0.0f);//ScreenPos(g_chip[j].pos);


				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(chip[i].texno));
				DrawSpriteColorRotation(
					g_layer.chip[j].pos.x,
					g_layer.chip[j].pos.y,
					MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0,
					D3DXCOLOR(1, 1, 1, 1),
					1, 1, 1, 1);

			}
			j++;
		}
	}

}

void DrawLayerMapchipGap()
{
	CHIP* chip = GetChip();
	int j = 0;
	for (int y = 0; y < LAYER_CHIP_NUM_HEIGHT; y++)
	{
		for (int x = 0; x < LAYER_CHIP_NUM_WIDTH; x++)
		{
			int i = g_layer.mapChipList[y][x];
			g_layer.chip[j].pos.x = (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH / 2;
			g_layer.chip[j].pos.y = (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT / 2;

			if (g_layer.chip[j].use == true)
			{


				D3DXVECTOR2 scrpos = D3DXVECTOR2(0.0f, 0.0f);//ScreenPos(g_chip[j].pos);

			//case CHIP_TYPE::TYPE_2:
			///*	if (IsMouseLeftTriggered())
			//	{

			//	}*/
			//	break;

			//case CHIP_TYPE::TYPE_3:


				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(chip[i].texno));
				//DrawSpriteColorRotation(
				//	g_layer.chip[j].pos.x,
				//	g_layer.chip[j].pos.y,
				//	MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0,
				//	D3DXCOLOR(1, 1, 1, 1),
				//	1, 1, 1, 1);
				//8�񂸂炵�ĕ\������
				D3DXVECTOR2 gap;
				for (int i = 0; i < 8; i++)
				{
					switch (i)
					{
					case 0: gap = D3DXVECTOR2(-g_gap, -g_gap); break;
					case 1: gap = D3DXVECTOR2(-g_gap, +g_gap); break;
					case 2: gap = D3DXVECTOR2(+g_gap, -g_gap); break;
					case 3: gap = D3DXVECTOR2(+g_gap, +g_gap); break;
					case 4: gap = D3DXVECTOR2(0.0f, -g_gap * 2); break;
					case 5: gap = D3DXVECTOR2(0.0f, +g_gap * 2); break;
					case 6: gap = D3DXVECTOR2(-g_gap * 2, 0.0f); break;
					case 7: gap = D3DXVECTOR2(+g_gap * 2, 0.0f); break;
					default: break;
					}
					//�X�v���C�g�\��
					DrawSpriteColorRotation(
						g_layer.chip[j].pos.x + gap.x,
						g_layer.chip[j].pos.y + gap.y,
						MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0,
						D3DXCOLOR(1, 1, 1, 0.07f),
						1, 1, 1, 1);
				}

			}
			j++;
		}
	}

}

void UpdateLayerMapchip()
{
	//int j = 0;
	//for (int y = 0; y < LAYER_CHIP_NUM_HEIGHT; y++)
	//{
	//	for (int x = 0; x < LAYER_CHIP_NUM_WIDTH; x++)
	//	{

	//		int i = g_layer.mapChipList[y][x];
	//		g_layer.chip[j].type = (CHIP_TYPE)i;

	//		switch (g_layer.chip[j].type)
	//		{
	//		case CHIP_TYPE::TYPE_0:
	//			g_layer.chip[j].use = false;
	//			break;

	//		case CHIP_TYPE::TYPE_1:
	//			g_layer.chip[j].collision = true;
	//			break;

	//		case CHIP_TYPE::TYPE_2:
	//			if (IsMouseLeftTriggered())
	//			{

	//			}
	//			break;

	//		case CHIP_TYPE::TYPE_3:

	//			break;

	//		default:
	//			break;
	//		}
	//		j++;
	//	}
	//}

}



//===================================
//���C���[�̔w�i�ƃ}�b�v�`�b�v���Z�b�g���ď���������
// name1,2,3 �w�i�̃f�[�^�̃t�@�C���p�X�t���̖��O
// name4,5,6 �}�b�v�`�b�v�̃f�[�^�̃t�@�C���p�X�t���̖��O
//===================================
void	SetLayerBGMC(char* name0, char* name1, char* name2, char* name3,
	char* name4, char* name5, char* name6)
{
	//�󂯎������񂪌��݂̏��ƈ�ł��Ⴆ�Ώ��������ď���������
	if (g_LayerTextureName0 != name0 ||
		g_LayerTextureName1 != name1 ||
		g_LayerTextureName2 != name2 ||
		g_LayerTextureName3 != name3 ||
		g_LayerMapchipName1 != name4 ||
		g_LayerMapchipName2 != name5 ||
		g_LayerMapchipName3 != name6
		)
	{
		g_LayerTextureName0 = name0;
		g_LayerTextureName1 = name1;
		g_LayerTextureName2 = name2;
		g_LayerTextureName3 = name3;

		g_LayerMapchipName1 = name4;
		g_LayerMapchipName2 = name5;
		g_LayerMapchipName3 = name6;

		InitLayer();
	}

}


void	SetLayerBG(char* name0, char* name1, char* name2, char* name3)
{
	SetLayerBGMC(name0, name1, name2, name3,
		g_LayerMapchipName1,
		g_LayerMapchipName2,
		g_LayerMapchipName3
	);
}

void	SetLayerMC_01(char* name1)
{
	SetLayerBGMC(g_LayerTextureName0, g_LayerTextureName1, g_LayerTextureName2, g_LayerTextureName3,
		name1, g_LayerMapchipName2, g_LayerMapchipName3
	);
	SetLimit(1);
}
void	SetLayerMC_02(char* name1, char* name2)
{
	SetLayerBGMC(g_LayerTextureName0, g_LayerTextureName1, g_LayerTextureName2, g_LayerTextureName3,
		name1, name2, g_LayerMapchipName3
	);
	SetLimit(2);

}
void	SetLayerMC_03(char* name1, char* name2, char* name3)
{
	SetLayerBGMC(g_LayerTextureName0, g_LayerTextureName1, g_LayerTextureName2, g_LayerTextureName3,
		name1, name2, name3
	);
	SetLimit(3);

}


//�}�b�v�`�b�v9�Ԃ̃X�N���[���X�g�b�v�̃^�C�~���O��
//���C���[��؂�ւ���֐�
//��ʃ��C���[�ˌŒ背�C���[
void	SetLayerNextMC09()
{
	//���݃Z�b�g����Ă��郌�C���[�̖��O���画�f����
	//���̃��C���[���Z�b�g����
	if (g_LayerMapchipName1 == LAYER_MC_1_1_01)//�G���A1
		SetLayerMC_01(K_LAYER_MC_1_1_01);
	else if (g_LayerMapchipName1 == LAYER_MC_1_1_02)
		SetLayerMC_01(K_LAYER_MC_1_1_02);
	else if (g_LayerMapchipName1 == LAYER_MC_1_2_01)
		SetLayerMC_01(K_LAYER_MC_1_2_01);
	else if (g_LayerMapchipName1 == LAYER_MC_1_2_02)
		SetLayerMC_01(K_LAYER_MC_1_2_02);
	else if (g_LayerMapchipName1 == LAYER_MC_1_3_01)
		SetLayerMC_01(K_LAYER_MC_1_3_01);
	else if (g_LayerMapchipName1 == LAYER_MC_1_3_02)
		SetLayerMC_01(K_LAYER_MC_1_3_02);
	else if (g_LayerMapchipName1 == LAYER_MC_2_1_01)//�G���A2
		 SetLayerMC_02(K_LAYER_MC_2_1_01, K_LAYER_MC_2_1_02);
	else if (g_LayerMapchipName1 == LAYER_MC_2_1_02)
		 SetLayerMC_02(K_LAYER_MC_2_1_03, K_LAYER_MC_2_1_04);
	else if (g_LayerMapchipName1 == LAYER_MC_2_2_01)
		SetLayerMC_02(K_LAYER_MC_2_2_01, K_LAYER_MC_2_2_02);
	else if (g_LayerMapchipName1 == LAYER_MC_2_2_02)
		SetLayerMC_02(K_LAYER_MC_2_2_03, K_LAYER_MC_2_2_04);
	else if (g_LayerMapchipName1 == LAYER_MC_2_3_01)
		SetLayerMC_02(K_LAYER_MC_2_3_01, K_LAYER_MC_2_3_02);
	else if (g_LayerMapchipName1 == LAYER_MC_2_3_02)
		SetLayerMC_02(K_LAYER_MC_2_3_03, K_LAYER_MC_2_3_04);
	else if (g_LayerMapchipName1 == LAYER_MC_3_1_01)//�G���A3
		SetLayerMC_03(K_LAYER_MC_3_1_01, K_LAYER_MC_3_1_02,K_LAYER_MC_3_1_03);
	else if (g_LayerMapchipName1 == LAYER_MC_3_1_02)
		SetLayerMC_03(K_LAYER_MC_3_1_04, K_LAYER_MC_3_1_05,K_LAYER_MC_3_1_06);
	else if (g_LayerMapchipName1 == LAYER_MC_3_2_01)
		SetLayerMC_03(K_LAYER_MC_3_2_01, K_LAYER_MC_3_2_02, K_LAYER_MC_3_2_03);
	else if (g_LayerMapchipName1 == LAYER_MC_3_2_02)
		SetLayerMC_03(K_LAYER_MC_3_2_04, K_LAYER_MC_3_2_05, K_LAYER_MC_3_2_06);
	else if (g_LayerMapchipName1 == LAYER_MC_3_3_01)
		SetLayerMC_03(K_LAYER_MC_3_3_01, K_LAYER_MC_3_3_02, K_LAYER_MC_3_3_03);
	else if (g_LayerMapchipName1 == LAYER_MC_3_3_02)
		SetLayerMC_03(K_LAYER_MC_3_3_04, K_LAYER_MC_3_3_05, K_LAYER_MC_3_3_06);


}

//�}�b�v�`�b�v10�Ԃ̃X�N���[���X�g�b�v�����̃^�C�~���O��
//���C���[��؂�ւ���֐�
//�Œ背�C���[�ˈ�ʃ��C���[
void	SetLayerNextMC10()
{
	//���݃Z�b�g����Ă��郌�C���[�̖��O���画�f����
	//���̃��C���[���Z�b�g����
	if (g_LayerMapchipName1 == K_LAYER_MC_1_1_01)//�G���A1
		SetLayerMC_01(LAYER_MC_1_1_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_1_1_02)
		SetLayerMC_01(LAYER_MC_1_1_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_1_2_01)
		SetLayerMC_01(LAYER_MC_1_2_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_1_2_02)
		SetLayerMC_01(LAYER_MC_1_2_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_1_3_01)
		SetLayerMC_01(LAYER_MC_1_3_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_1_3_02)
		SetLayerMC_01(LAYER_MC_1_3_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_1_01)//�G���A2
		SetLayerMC_01(LAYER_MC_2_1_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_1_03)
		SetLayerMC_01(LAYER_MC_2_1_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_2_01)
		SetLayerMC_01(LAYER_MC_2_2_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_2_03)
		SetLayerMC_01(LAYER_MC_2_2_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_3_01)
		SetLayerMC_01(LAYER_MC_2_3_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_3_03)
		SetLayerMC_01(LAYER_MC_2_3_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_1_01)//�G���A3
		SetLayerMC_01(LAYER_MC_3_1_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_1_04)
		SetLayerMC_01(LAYER_MC_3_1_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_2_01)
		SetLayerMC_01(LAYER_MC_3_2_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_2_04)
		SetLayerMC_01(LAYER_MC_3_2_03);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_3_01)
		SetLayerMC_01(LAYER_MC_3_3_02);
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_3_04)
		SetLayerMC_01(LAYER_MC_3_3_03);


}
