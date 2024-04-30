//#include "Mapcollision.h"
//#include "player.h"
//#include "mapchip.h"
//#include "playerCamera.h"
//void HitCollision()//チップ１つと別のオブジェクトの当たり判定を取る関数
//{
//	PLAYER* player = GetPlayer();
//	CHIP* chip = GetChip();  
//
//	for (int i = 0; i < NUM_CHIP_ALL; i++)
//	{
//		D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);
//		if (chip[i].collision)
//		{
//
//			if (scrpos.y - chip[i].size.y / 2 < player->pos.y + player->size.y / 2 &&
//				scrpos.y - chip[i].size.y / 2 > player->oldpos.y + player->size.y / 2)//ブロックの上とプレイヤーの下
//			{
//				if (scrpos.x - chip[i].size.x / 2 < player->pos.x + player->size.x / 2 &&//横の範囲
//					scrpos.x - chip[i].size.x / 2 > player->pos.x - player->size.x / 2)
//				{
//					player->Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//					player->pos = player->oldpos;
//					player->upCollision = true;
//					break;
//				}
//
//				//break;
//			}
//	
//
//			if (scrpos.y - chip[i].size.y / 2 > player->pos.y + player->size.y / 2 &&
//				scrpos.y - chip[i].size.y / 2 < player->oldpos.y + player->size.y / 2)//ブロックの下とプレイヤーの上
//			{
//				if (scrpos.x - chip[i].size.x / 2 < player->pos.x + player->size.x / 2 &&//横の範囲
//					scrpos.x - chip[i].size.x / 2 > player->pos.x - player->size.x / 2)
//				{
//					player->Color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
//					player->pos = player->oldpos;
//					break;
//
//
//				}
//			}
//
//
//			if (scrpos.x - chip[i].size.x / 2 < player->pos.x + player->size.x / 2 &&
//				scrpos.x - chip[i].size.x / 2 > player->oldpos.x + player->size.x / 2)//ブロックの左とプレイヤーの右
//			{
//				if (scrpos.y - chip[i].size.y / 2 < player->pos.y + player->size.y / 2 &&//横の範囲
//					scrpos.y - chip[i].size.y / 2 > player->pos.y - player->size.y / 2)
//				{
//					player->Color = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
//					player->pos = player->oldpos;
//					break;
//
//				}
//			}
//
//			if (scrpos.x + chip[i].size.x / 2 > player->pos.x - player->size.x / 2 &&
//				scrpos.x + chip[i].size.x / 2 < player->oldpos.x - player->size.x / 2)//ブロックの右とプレイヤーの左
//			{
//				if (scrpos.y - chip[i].size.y / 2 < player->pos.y + player->size.y / 2 &&//横の範囲
//					scrpos.y - chip[i].size.y / 2 > player->pos.y - player->size.y / 2)
//				{
//					player->Color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
//					player->pos = player->oldpos;
//					break;
//
//
//				}
//			}
//		}
//		player->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//
//
//	}
//
//
//
//}
