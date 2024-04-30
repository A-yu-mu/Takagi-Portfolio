//=============================================================================
// mcgimmick.h
// �쐬�ҁF���ؕ����@�쐬���F2022/10/28
//=============================================================================

#ifndef MCGIMICK_H_
#define MCGIMICK_H_

#include "main.h"
#include "renderer.h"



//====================================
//�v���g�^�C�v�錾
//====================================


void LifeDamage(void);
void JunpPowerUp(void);
void noGravity(void);
void afterimageGravity();

void ColMoveChipX(int chipno);
void AIColMoveChipX(int chipno);
void ColMoveChipY(int chipno);
void AIColMoveChipY(int chipno);
void MoveChipX(int chipno, float distance, int sp);
void MoveChipY(int chipno, float distance, int sp);

void IceBlock();

void SkeletonBlonkStart(int chipnum);
bool SkeletonBlonkDo(int chipnum);
bool SkeletonBlonkReborn(int chipnum);

void InitMcGimmick();

#endif // !SPINES_H_
