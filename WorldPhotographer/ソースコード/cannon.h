//=============================================================================
//cannon.h
// �쐬�ҁF�����[�C�@�쐬���F2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define CANNON_SIZE_W (168)
#define	CANNON_SIZE_H (64)
#define CANNON_MAX (10)
static	ID3D11ShaderResourceView* g_TextureCannon;//�摜1����1�̕ϐ����K�v
static	char* g_TextureCannonName = (char*)"data\\texture\\cannon.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct CANNON
{
	bool use;		//�\���̗��p���t���O

	D3DXVECTOR2		size;		//�|���S���̃T�C�Y			
	//float w, h;     //box�T�C�Y
	D3DXVECTOR2 pos;//�\�����W
	float rot;      //��]�p�x
	D3DXCOLOR Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	float texno;    //�e�N�X�`���C���f�b�N�X
	//bool hitCollision;
	//bool upCollision;
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitCannon();
void    UnInitCannon();
void    DrawCannon();
void    UpdateCannon();
CANNON* GetCannon(); //CANNON�\���̂̐擪�|�C���^���擾
void	SetCannon(D3DXVECTOR2 pos);