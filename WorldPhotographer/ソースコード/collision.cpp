//=============================================================================
//collision.cpp
//
// �쐬�ҁF���їǑ��@�쐬���F2022/11/01
//=============================================================================

//�����撣���č��܂���

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

//���킹��M�~�b�N�悤�ɉ��Œǉ�
//��荇�����̃��A�N�V�����p�ł�
#include "photo.h"

//��������������������������
//�v���g�^�C�v�錾�i����cpp���̂݁j
//��������������������������

const int COL_PLAYER_SIZE_W = (int)PLAYER_SIZE_W - 0;

//��������������������������������������������
// �l�p�`���m�̓����蔻��
// in ���S���W�P�C���S���W�Q�A�T�C�Y�P�A�T�C�Y�Q
// out true:�Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�
//��������������������������������������������


bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);


//��������������������������������������������
// �~�Ɖ~���m�̓����蔻��
// in ���S���W�P�C���S���W�Q�A���a�P�A���a�Q
// out true:�Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�
//��������������������������������������������

bool CollosionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);


//��������������������������
//�����蔻�菈��
//��������������������������
void UpdateCollision()
{
	//�v���C���[�@�΁@�G�L�����@BB����
//bool CollosionBB();

	PLAYER* player = GetPlayer();
	BLOCK* block = GetBlock();
	CHIP* chip = GetChip();
	SHELL* shell = GetShell();

	//�����Ă���ʐ^�̏����擾
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

					if (after_imageHit && !player_after->col)//�Ă��t���p�̓����蔻��
					{
						if (scrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player_after->oldpos.y)// chip�ɏォ�瓖�����Ă���
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
						else //�ォ�瓖�����Ă��Ȃ��Ƃ�
						{
							if (scrpos.x >= player_after->pos.x)
							{
								if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player_after->oldpos.x)//�`�b�v�ɍ����瓖�����Ă���
								{
									if (chip[i].collision)
									{
										player_after->pos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
									}
								}
							}

							if (scrpos.x <= player_after->pos.x) //�`�b�v�ɉE���瓖�����Ă��邩�m�F
							{
								if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player_after->oldpos.x)//�`�b�v�ɉE���瓖�����Ă���
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
					if (scrpos.y >= player->pos.y) //�`�b�v�ɏォ�瓖�����Ă��邩�m�F
					{
						if (oldscrpos.y - ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) >= player->oldpos.y)// chip�ɏォ�瓖�����Ă���
						{

							if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
							else //�`�b�v�̐^�ׂɂ���Ƃ���ɏ��Ȃ��i����������Ȃ��j
							{
								if (chip[i].collision)
								{
									//�v���C���[���n�G�t�F�N�g����
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
						else //�ォ�瓖�����Ă��Ȃ��Ƃ��i�v���C���[���`�b�v�̏�𑖂��Ă��Ă��Ƃ܂�Ȃ��j
						{


							if (scrpos.x >= player->pos.x) //�`�b�v�ɍ����瓖�����Ă��邩�m�F
							{
								if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//�`�b�v�ɍ����瓖�����Ă���
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2 );
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//�X�N���[�����`�b�v���E���瓖�����Ă���i�`�b�v�ɍ����瓖�����Ă���j
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2);
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
							}

							if (scrpos.x <= player->pos.x) //�`�b�v�ɉE���瓖�����Ă��邩�m�F
							{
								if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) >= player->oldpos.x)//�`�b�v�ɉE���瓖�����Ă���
								{
									if (chip[i].collision)
									{
										player->oldpos.x = scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2 );
										player->pos.x = player->oldpos.x;
									}
									ChipGimmickColOthers(i);
								}
								else if (scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) <= player->oldpos.x)//�X�N���[�����`�b�v�������瓖�����Ă���i�`�b�v�ɉE���瓖�����Ă���j
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
					else if (scrpos.y <= player->pos.y) //�`�b�v�ɉ����瓖�����Ă��邩�m�F
					{

						if (oldscrpos.y + ((PLAYER_SIZE_H + MAPCHIP_HEIGHT) / 2) <= player->oldpos.y)// chip�ɉ����瓖�����Ă���
						{
							if (scrpos.x - ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x || scrpos.x + ((colPlayerSize.x + MAPCHIP_WIDTH) / 2) == player->oldpos.x) {}
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
//��������������������������������������������
// �l�p�`���m�̓����蔻��
// in ���S���W�P�C���S���W�Q�A�T�C�Y�P�A�T�C�Y�Q
// out true:�Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�
//��������������������������������������������
bool CheckHit(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2 min1, min2; //�l�p�`�ŏ����W�@����
	D3DXVECTOR2 max1, max2;//�l�p�`�ő���W�@�E��


	//�l�p�`�P����
	min1.x = pos1.x - size1.x / 2;
	min1.y = pos1.y - size1.y / 2;

	//�l�p�`�P�E��
	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	//�l�p�`�Q����
	min2.x = pos2.x - size2.x / 2;
	min2.y = pos2.y - size2.y / 2;

	//�l�p�`�Q�E��
	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//�Փ˂̔���
	if (max1.x < min2.x) return false;
	if (max1.y < min2.y) return false;
	if (max2.x < min1.x) return false;
	if (max2.y < min1.y) return false;

	return true;//�Փ˂��Ă���
}



//��������������������������������������������
// �~�Ɖ~���m�̓����蔻��
// in ���S���W�P�C���S���W�Q�A���a�P�A���a�Q
// out true:�Փ˂��Ă���@false:�Փ˂��Ă��Ȃ�
//��������������������������������������������

bool CollosionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
	//���S���m�̃x�N�g��
	D3DXVECTOR2 vDistance = pos1 - pos2;

	//�x�N�g���̒��������
	float Length;
	Length = D3DXVec2LengthSq(&vDistance);//���[�g���g��Ȃ���
	//Length = D3DXVec2LengthS(&vDistance);//���[�g���g���Łi���m�Ȓ����j

	//���a�̑��a
	float size = (size1 + size2) * (size1 + size2);//���݂�2��
	//Length��size���g���ďՓ˔���
	if (Length < size)
	{
		return true; //�Փ˂��Ă���
	}
	else
	{
		return false;//�Փ˂��Ă��Ȃ�
	}

}


