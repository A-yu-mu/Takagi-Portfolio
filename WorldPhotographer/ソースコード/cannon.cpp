//=============================================================================
//cannon.cpp		��C
// �쐬�ҁF�����[�C�@�쐬���F2022/10/28
//=============================================================================



//�v���C���[�̃��C�t���s���Ď��S�t���O�����������A��C����ʉE�ɓ����悤�ɂȂ��Ă��܂��B
//���S�����Ƃ����̂����Ă킩��悤�ɂ��邽�߂Ȃ̂ł̂��ɏ����\��





#include "cannon.h"
#include "sprite.h"
#include "texture.h"
//#include "explosion.h"

#include "player.h"
#include "shell.h"
//===================================
//�}�N����`
//===================================

//===================================
//�v���g�^�C�v�錾
//===================================


//===================================
//�O���[�o���ϐ�
//===================================
int yubiori;

static CANNON g_cannon[CANNON_MAX];

//===================================
//������
//===================================
HRESULT InitCannon()
{
	///*int texNo= LoadTexture(g_TextureCannonName);*/
	yubiori = 0;
	//�J�m���̏�����
	for (int i = 0; i < CANNON_MAX; i++)
	{
		g_cannon[i].pos.x = 0 + 42;
		g_cannon[i].pos.y = 0 + 16;

		/*g_cannon.w = CANNON_SIZE_W;
		g_cannon.h = CANNON_SIZE_H;*/
		g_cannon[i].size = D3DXVECTOR2(CANNON_SIZE_W, CANNON_SIZE_H);

		g_cannon[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_cannon[i].rot = 0.0f;
		g_cannon[i].use = false;
		/*g_cannon[i].texno = texNo;*/
		//g_cannon[i].hitCollision = false;
		//g_cannon[i].upCollision = false;
		

	}
	return S_OK;
}

//===================================
//�I��
//===================================
void    UnInitCannon()
{

}


//===================================
//�`��
//===================================
void    DrawCannon()
{
	//�J�m���\��
	//for (int  i = 0; i < CANNON_MAX; i++)
	//{
	//	if(g_cannon[i].use==true)
	//	{
	//	//�e�N�X�`���̕\��
	//	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_cannon[i].texno));
	//	}
	//}
	
}

//===================================
//�X�V
//===================================
void    UpdateCannon()
{
	yubiori++;
	PLAYER* pPlayer = GetPlayer();
	SHELL* pShell = GetShell();
	/*for (int i = 0; i < CANNON_MAX; i++)
	{
		if (pPlayer->DeathFlag==true)
		{
			g_cannon[i].pos.x += 1.0f;
		}
		if (g_cannon[i].use == true)
		{
			if (yubiori % 60 == 0)
			{
				SetShell(g_cannon[i].pos - D3DXVECTOR2(96.0f,16.0f));
				
			}
		}
	}*/



}

//===================================
//�J�m���\���̂̐擪�|�C���^���擾
//===================================
CANNON* GetCannon()
{
	return &g_cannon[0];
}

void SetCannon(D3DXVECTOR2 pos)
{
	for (int i = 0; i < CANNON_MAX; i++) {
		if (g_cannon[i].use == false)
		{
			g_cannon[i].pos = pos;
			g_cannon[i].use = true;
			return;
		}
	}
}