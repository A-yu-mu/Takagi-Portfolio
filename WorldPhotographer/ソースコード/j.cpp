for (int i = 0; i < NUM_CHIP_ALL; i++)
	{
		D3DXVECTOR2 scrpos = ScreenPos(chip[i].pos);

		if (chip[i].use)
		{
			bool hit = CheckHit(player->pos, scrpos, colPlayerSize, chip->size);

			if (hit)
			{
				if (scrpos.y >= player->pos.y) //�`�b�v�ɏォ�瓖�����Ă��邩�m�F
				{
					if (scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player->oldpos.y)// chip�ɏォ�瓖�����Ă���
					{
						if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x){}

						else //�`�b�v�̐^�ׂɂ���Ƃ���ɏ��Ȃ��i����������Ȃ��j
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
					else //�ォ�瓖�����Ă��Ȃ��Ƃ��i�v���C���[���`�b�v�̏�𑖂��Ă��Ă��Ƃ܂�Ȃ��j
					{
						if (scrpos.x >= player->pos.x) //�`�b�v�ɍ����瓖�����Ă��邩�m�F
						{
							if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//�`�b�v�ɍ����瓖�����Ă���
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//�X�N���[�����`�b�v���E���瓖�����Ă���i�`�b�v�ɍ����瓖�����Ă���j
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
						}

						if (scrpos.x <= player->pos.x) //�`�b�v�ɉE���瓖�����Ă��邩�m�F
						{
							if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//�`�b�v�ɉE���瓖�����Ă���
							{
								if (chip[i].collision)
								{
									player->oldpos.x = scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2);
									player->pos.x = player->oldpos.x;
								}
								ChipGimmickColOthers(i);
							}
							else if (scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//�X�N���[�����`�b�v�������瓖�����Ă���i�`�b�v�ɉE���瓖�����Ă���j
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
				else if (scrpos.y <= player->pos.y) //�`�b�v�ɉ����瓖�����Ă��邩�m�F
				{

					if (scrpos.y + ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) <= player->oldpos.y)// chip�ɉ����瓖�����Ă���
					{
						if (scrpos.x - ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((COL_PLAYER_SIZE_W + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
						else //�`�b�v�̐^�ׂɂ���Ƃ������炠����Ȃ��i����������Ȃ��j
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
