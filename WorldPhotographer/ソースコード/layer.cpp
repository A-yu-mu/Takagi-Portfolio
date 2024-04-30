//=============================================================================
//layer.cpp
// 作成者：舘崎　作成日：2022/10/22
//=============================================================================

#include "layer.h"
#include "sprite.h"
#include "texture.h"
#include "inputx.h"
//#include "explosion.h"

#include "pinto.h"

//マップチップ用
#include <fstream>
#include <iostream>

//===================================
//マクロ定義
//===================================

//===================================
//プロトタイプ宣言
//===================================
//レイヤーの中のマップチップの処理四天王(Drawだけぶれる版で二個目が存在します)
HRESULT	InitLayerMapchip();
void	UninitLayerMapchip();
void	DrawLayerMapchip();
void	DrawLayerMapchipGap();
void	UpdateLayerMapchip();


//===================================
//グローバル変数
//===================================
static LAYER g_gb_layer;				//背景の表示用レイヤー(見た目だけ用)
static LAYER g_layer;					//現在の表示レイヤー（ゲッターで返す用）
static LAYER g_sub_layer[LAYER_MAX];	//サブレイヤー、現在の面の用意してあるレイヤー全て（ゲッターでは返さない）

//今が撮影可能かどうか判断するフラグ
bool g_Layer_canget_flag;

//ピントのずれ具合（ギャップ）を管理する変数
float g_gap;

//マップチップの処理に必要
using namespace std;


int g_LayerMapChipList[CHIP_NUM_HEIGHT][CHIP_NUM_WIDTH];

//int g_LayerMapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];



//===================================
//初期化
//===================================
HRESULT InitLayer()
{

	//背景レイヤーの初期化
	g_gb_layer.pos.x = SCREEN_WIDTH / 2;
	g_gb_layer.pos.y = SCREEN_HEIGHT / 2;

	g_gb_layer.w = LAYER_SIZE_W;
	g_gb_layer.h = LAYER_SIZE_H;

	g_gb_layer.rot = 0.0f;
	g_gb_layer.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_gb_layer.use = true;
	g_gb_layer.texno = LoadTexture(g_LayerTextureName0);
	//レイヤーの初期化
	g_layer.pos.x = SCREEN_WIDTH / 2;
	g_layer.pos.y = SCREEN_HEIGHT / 2;

	g_layer.w = LAYER_SIZE_W;
	g_layer.h = LAYER_SIZE_H;

	g_layer.rot = 0.0f;
	g_layer.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.125f);
	g_layer.use = true;
	g_layer.texno = LoadTexture(g_LayerTextureName1);
	//サブレイヤーの初期化
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


	//フラグの初期化
	g_Layer_canget_flag = false;

	//ギャップの初期化
	g_gap = 0.0f;

	//マップチップの初期化
	InitLayerMapchip();

	return S_OK;
}

//===================================
//終了
//===================================
void    UnInitLayer()
{
	//マップチップの初期化
	UninitLayerMapchip();

}


//===================================
//描画
//===================================
void    DrawLayer()
{
	//レイヤー表示
	if (g_gb_layer.use == true)
	{
		//テクスチャの表示(一番後ろの空)
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_gb_layer.texno));
		//スプライト表示
		DrawSpriteColorRotation(
			g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
			g_gb_layer.rot, g_gb_layer.Color, 1, 1, 1, 1);

		//ピントの最大数に合わせて背景の描画を変える
		if (g_layer.texno == g_sub_layer[0].texno)//レイヤー１の場合
		{
			//テクスチャの表示(レイヤー３)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[2].texno));
			//スプライト表示
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);
			//テクスチャの表示(レイヤー２)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[1].texno));
			//スプライト表示
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);

		}
		else if (g_layer.texno == g_sub_layer[1].texno)//レイヤー２の場合
		{
			//テクスチャの表示(レイヤー３)
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_sub_layer[2].texno));
			//スプライト表示
			DrawSpriteColorRotation(
				g_gb_layer.pos.x, g_gb_layer.pos.y, g_gb_layer.w, g_gb_layer.h,
				g_gb_layer.rot, g_gb_layer.Color, 1, 0.5f, 1, 1);

		}
		else if (g_layer.texno == g_sub_layer[2].texno)//レイヤー３の場合
		{

		}


	}
	//レイヤー表示
	if (g_layer.use == true)
	{
		//テクスチャの表示
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_layer.texno));

		//8回ずらして表示する
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
			//スプライト表示
			DrawSpriteColorRotation(
				g_layer.pos.x + gap.x, g_layer.pos.y + gap.y,
				g_layer.w, g_layer.h,
				g_layer.rot, g_layer.Color, 1, 1, 1, 1);
		}

	}
	if (g_Layer_canget_flag == true)
	{
		//マップチップの描画
		DrawLayerMapchip();
	}
	else
	{
		//マップチップの描画（ぶれ版）
		DrawLayerMapchipGap();
	}

}


//===================================
//更新
//===================================
void    UpdateLayer()
{
	//ピントの状態を確認してブレ具合を変える
	PINTO* p_pinto = GetPinto();
	float layer1 = 0.0f;	//レイヤー１のちょうど位置
	float layer2 = 0.0f;	//レイヤー２のちょうど位置
	float layer3 = 0.0f;	//レイヤー３のちょうど位置
	//ピントの位置がちょうどの位置を計算して求めるs
	layer1 = p_pinto->change1pos / 2;
	layer2 = p_pinto->change1pos + ((p_pinto->change2pos - p_pinto->change1pos) / 2);
	layer3 = p_pinto->change2pos + ((p_pinto->maxpos - p_pinto->change2pos) / 2);

	//条件を満たす時のみマップチップ表示
	if ((layer1 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer1 + PINTO_OKLINE / 2) ||
		(layer2 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer2 + PINTO_OKLINE / 2) ||
		(layer3 - PINTO_OKLINE / 2 <= p_pinto->nowpos && p_pinto->nowpos <= layer3 + PINTO_OKLINE / 2))
	{
		g_Layer_canget_flag = true;
		//マップチップの更新
		UpdateLayerMapchip();
	}
	else
	{
		g_Layer_canget_flag = false;

	}

	//ギャップを計算する為に現在の表示レイヤーを確認し、レイヤー情報を更新する
	if (p_pinto->nowpos <= p_pinto->change1pos)	//レイヤー1の場合
	{
		g_gap = layer1;
		g_layer = g_sub_layer[0];

	}
	else if (p_pinto->nowpos <= p_pinto->change2pos)	//レイヤー2の場合
	{
		g_gap = layer2;
		g_layer = g_sub_layer[1];

	}
	else if (p_pinto->nowpos <= p_pinto->maxpos)	//レイヤー3の場合
	{
		g_gap = layer3;
		g_layer = g_sub_layer[2];

	}
	//ギャップを計算する
	g_gap -= p_pinto->nowpos;


}

//===================================
//プレイヤー構造体の先頭ポインタを取得
//===================================
LAYER* GetLayer()
{
	return &g_layer;
}

bool GetLayerCanGet()
{
	return g_Layer_canget_flag;
}


//レイヤー内のマップチップの処理はここより下に書いておく
HRESULT InitLayerMapchip()
{
	//イニットではサブレイヤーのみ初期化する
	//サブレイヤー１
	{
		ifstream inputfile(g_LayerMapchipName1); //ファイル読み込み
		if (!inputfile.is_open())
			cout << "Error opening file";   //読み込みエラー表示
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[0].mapChipList[r][c];  //読み込んだファイルをマップチップリストに入れる
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

	//サブレイヤー２
	{
		ifstream inputfile(g_LayerMapchipName2); //ファイル読み込み
		if (!inputfile.is_open())
			cout << "Error opening file";   //読み込みエラー表示
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[1].mapChipList[r][c];  //読み込んだファイルをマップチップリストに入れる
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
	//サブレイヤー３
	{
		ifstream inputfile(g_LayerMapchipName3); //ファイル読み込み
		if (!inputfile.is_open())
			cout << "Error opening file";   //読み込みエラー表示
		int chip_type = 0;
		for (int r = 0; r < LAYER_CHIP_NUM_HEIGHT; r++)
		{
			for (int c = 0; c < LAYER_CHIP_NUM_WIDTH; c++)
			{
				inputfile >> g_sub_layer[2].mapChipList[r][c];  //読み込んだファイルをマップチップリストに入れる
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
				//8回ずらして表示する
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
					//スプライト表示
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
//レイヤーの背景とマップチップをセットして初期化する
// name1,2,3 背景のデータのファイルパス付きの名前
// name4,5,6 マップチップのデータのファイルパス付きの名前
//===================================
void	SetLayerBGMC(char* name0, char* name1, char* name2, char* name3,
	char* name4, char* name5, char* name6)
{
	//受け取った情報が現在の情報と一つでも違えば書き換えて初期化する
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


//マップチップ9番のスクロールストップのタイミングで
//レイヤーを切り替える関数
//一般レイヤー⇒固定レイヤー
void	SetLayerNextMC09()
{
	//現在セットされているレイヤーの名前から判断して
	//次のレイヤーをセットする
	if (g_LayerMapchipName1 == LAYER_MC_1_1_01)//エリア1
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
	else if (g_LayerMapchipName1 == LAYER_MC_2_1_01)//エリア2
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
	else if (g_LayerMapchipName1 == LAYER_MC_3_1_01)//エリア3
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

//マップチップ10番のスクロールストップ解除のタイミングで
//レイヤーを切り替える関数
//固定レイヤー⇒一般レイヤー
void	SetLayerNextMC10()
{
	//現在セットされているレイヤーの名前から判断して
	//次のレイヤーをセットする
	if (g_LayerMapchipName1 == K_LAYER_MC_1_1_01)//エリア1
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
	else if (g_LayerMapchipName1 == K_LAYER_MC_2_1_01)//エリア2
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
	else if (g_LayerMapchipName1 == K_LAYER_MC_3_1_01)//エリア3
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
