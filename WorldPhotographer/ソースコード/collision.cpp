//=============================================================================
//collision.cpp
//
// 作成者：小林良太　作成日：2022/11/01
//=============================================================================

//無茶頑張って作りました

#include "collision.h"
#include "main.h"
#include "player.h"
#include "block.h"
#include "mapchip.h"
#include "mcgimmick.h"
#include "playerCamera.h"
#include "player_effect.h"
#include <algorithm>


#include "player_afterimage.h"


#include "shell.h"
#include "io_ex.h"

//合わせるギミックように仮で追加
//取り合えすのリアクション用です
#include "photo.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//プロトタイプ宣言（このcpp内のみ）
//＝＝＝＝＝＝＝＝＝＝＝＝＝

const int COL_PLAYER_SIZE_W = (int)PLAYER_SIZE_W - 0;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 四角形同士の当たり判定
// in 中心座標１，中心座標２、サイズ１、サイズ２
// out true:衝突している　false:衝突していない
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝


bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 円と円同士の当たり判定
// in 中心座標１，中心座標２、半径１、半径２
// out true:衝突している　false:衝突していない
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

bool CollosionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//＝＝＝＝＝＝＝＝＝＝＝＝＝
//当たり判定処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void UpdateCollision()
{
	//プレイヤー　対　敵キャラ　BB判定
//bool CollosionBB();

	PLAYER* player = GetPlayer();
	BLOCK* block = GetBlock();
	CHIP* chip = GetChip();
	SHELL* shell = GetShell();

	//持っている写真の情報を取得
	PHOTO* p_photo = GetPhotoStock();

	AfterImage* player_after = GetAfterImage();

	D3DXVECTOR2 colPlayerSize = D3DXVECTOR2(player->size.x - 30, player->size.y);
	D3DXVECTOR2 colafterSize = D3DXVECTOR2(player_after->size.x - 30, player_after->size.y);

	for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);
		if (scrpos.x < SCREEN_WIDTH + 50 && scrpos.x > 0 - 50 && scrpos.y < SCREEN_HEIGHT + 50 && scrpos.y > 0 - 50)
		{
			if (chip[i].use)
			{
				if (player_after->use)
				{
					bool	after_imageHit = CheckHit(player_after->pos, scrpos, colafterSize, chip->size);

					if (after_imageHit && !player_after->col)//焼き付け用の当たり判定
					{
						if (scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player_after->oldpos.y)// chipに上から当たっている
						{
							if (scrpos.x - ((colafterSize.x + MAPCHIP_WIDTH) / 2) == player_after->oldpos.x || scrpos.x + ((colafterSize.x + MAPCHIP_WIDTH) / 2) == player_after->oldpos.x) {}
							else {
								if (chip[i].collision)
								{
									player_after->pos.y = scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2);

									player_after->col = true;
								}
								PlayerAfterChipGimmick(i);
							}
						}
						else //上から当たっていないとき
						{
							if (scrpos.x >= player_after->pos.x)
							{
								if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player_after->oldpos.x)//チップに左から当たっている
								{
									if (chip[i].collision)
									{
										player_after->pos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
									}
								}
							}

							if (scrpos.x <= player_after->pos.x) //チップに右から当たっているか確認
							{
								if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player_after->oldpos.x)//チップに右から当たっている
								{
									if (chip[i].collision)
									{
										player_after->pos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
									}
								}
							}

						}
						
					}
				}
			}
		}
	}

	for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);
		D3DXVECTOR2 oldscrpos = OldScreenPos(chip[i].pos);
		if (scrpos.x < SCREEN_WIDTH + 50 && scrpos.x > 0 - 50 && scrpos.y < SCREEN_HEIGHT + 50 && scrpos.y > 0 - 50)
		{
			if (chip[i].use)
			{
				bool hit = CheckHit(player->pos, scrpos, colPlayerSize, chip->size);


				player->PlayerJumpEffect = true;
				player->PlayerWalk = false;


				if (hit)
				{
					if (scrpos.y >= player->pos.y) //チップに上から当たっているか確認
					{
						if (oldscrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player->oldpos.y)// chipに上から当たっている
						{

							if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
							else //チップの真隣にいるとき上に乗らない（引っかからない）
							{
								if (chip[i].collision)
								{
									//プレイヤー着地エフェクト処理
									if (!player->PlayerWalk && !player->PlayerCamera && !player->PlayerGoal
										&& ((int)chip[i].type != 9 && (int)chip[i].type != 10))
									{
										if (player->PlayerLandingEffect == false)
										{
											SetPlayerLandingEffect(player->pos.x, player->pos.y, 0.5f);
											PlaySE(SE_LANDING);
											player->PlayerLandingEffect = true;
										}
									}
									
									player->oldpos.y = scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2);
									player->pos.y = player->oldpos.y;
									
									player->PlayerJumpEffect = true;

								}
								ChipGimmickColUp(i);

								break;
							}
						}
						else //上から当たっていないとき（プレイヤーがチップの上を走っていてもとまらない）
						{


							if (scrpos.x >= player->pos.x) //チップに左から当たっているか確認
							{
								if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//チップに左から当たっている
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2 );
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//スクロール中チップが右から当たっている（チップに左から当たっている）
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
							}

							if (scrpos.x <= player->pos.x) //チップに右から当たっているか確認
							{
								if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//チップに右から当たっている
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2 );
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//スクロール中チップが左から当たっている（チップに右から当たっている）
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2 );
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
							}


						}
					}
					else if (scrpos.y <= player->pos.y) //チップに下から当たっているか確認
					{

						if (oldscrpos.y + ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) <= player->oldpos.y)// chipに下から当たっている
						{
							if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
							else //チップの真隣にいるとき下からあたらない（引っかからない）
							{
								if (chip[i].collision)
								{
									player->oldpos.y = scrpos.y + ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2);
									player->pos.y = player->oldpos.y;
								}
								ChipGimmickColOthers(i);
							}
						}
						else
						{

							if (scrpos.x > player->pos.x)
							{
								if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
							}

							if (scrpos.x < player->pos.x)
							{
								if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
							}
						}
					}

				}

			}


		}

	}

	for (int i = 0; i < SHELL_MAX; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(shell[i].pos);
		if (shell[i].use)
		{
			bool damage = CheckHit(player->pos, scrpos, player->size, shell[i].size);
			if (damage)
			{
				shell[i].use = false;
				LifeDamage();
			}
		}
	}

}
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 四角形同士の当たり判定
// in 中心座標１，中心座標２、サイズ１、サイズ２
// out true:衝突している　false:衝突していない
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, min2; //四角形最小座標　左上
	D3DXVECTOR2 max1, max2;//四角形最大座標　右下


	//四角形１左上
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;

	//四角形１右下
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	//四角形２左上
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;

	//四角形２右下
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//衝突の判定
	if (max1.x < min2.x) return false;
	if (max1.y < min2.y) return false;
	if (max2.x < min1.x) return false;
	if (max2.y < min1.y) return false;

	return true;//衝突している
}



//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 円と円同士の当たり判定
// in 中心座標１，中心座標２、半径１、半径２
// out true:衝突している　false:衝突していない
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

bool CollosionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//中心同士のベクトル
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//ベクトルの長さを作る
	float Length;
	Length = D3DXVec2LengthSq(&vDistance);//ルートを使わない版
	//Length = D3DXVec2LengthS(&vDistance);//ルートを使う版（正確な長さ）

	//半径の総和
	float size = (size1 + size2) * (size1 + size2);//お互い2乗
	//Lengthとsizeを使って衝突判定
	if (Length < size)
	{
		return true; //衝突している
	}
	else
	{
		return false;//衝突していない
	}

}


