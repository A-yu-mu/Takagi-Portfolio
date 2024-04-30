for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);

		if (chip[i].use)
		{
			bool hit = CheckHit(player->pos, scrpos, colPlayerSize, chip->size);

			if (hit)
			{
				if (scrpos.y >= player->pos.y) //チップに上から当たっているか確認
				{
					if (scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player->oldpos.y)// chipに上から当たっている
					{
						if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x){}

						else //チップの真隣にいるとき上に乗らない（引っかからない）
						{
							if (chip[i].collision)
							{
								player->oldpos.y = scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2);
								player->pos.y = player->oldpos.y;
							}

							ChipGimmickColUp(i);

							break;
						}
					}
					else //上から当たっていないとき（プレイヤーがチップの上を走っていてもとまらない）
					{
						if (scrpos.x >= player->pos.x) //チップに左から当たっているか確認
						{
							if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//チップに左から当たっている
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//スクロール中チップが右から当たっている（チップに左から当たっている）
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
						}

						if (scrpos.x <= player->pos.x) //チップに右から当たっているか確認
						{
							if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//チップに右から当たっている
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//スクロール中チップが左から当たっている（チップに右から当たっている）
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
						}
					}
				}
				else if (scrpos.y <= player->pos.y) //チップに下から当たっているか確認
				{

					if (scrpos.y + ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) <= player->oldpos.y)// chipに下から当たっている
					{
						if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
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
							if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
						}

						if (scrpos.x < player->pos.x)
						{
							if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
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
