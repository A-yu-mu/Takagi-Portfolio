//=============================================================================
//shell.h
// �쐬�ҁF�����[�C�@�쐬���F2022/10/28
//=============================================================================
#include "main.h"
#include "renderer.h"
//====================================
//�}�N����`
//====================================
#define SHELL_SIZE_W (25)
#define	SHELL_SIZE_H (25)
#define SHELL_MAX (100)
static	ID3D11ShaderResourceView* g_TextureShell;//�摜1����1�̕ϐ����K�v
static	char* g_TextureShellName = (char*)"data\\texture\\shell.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG
struct SHELL
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
	D3DXVECTOR2 spd;//�ړ����x
	float time;		//�������Ă���̎���
};


//====================================
//�v���g�^�C�v�錾
//====================================
HRESULT InitShell();
void    UnInitShell();
void    DrawShell();
void    UpdateShell();
SHELL* GetShell(); //SHELL�\���̂̐擪�|�C���^���擾
void	SetShell(D3DXVECTOR2 pos, int puramai);

bool	CountShell(int chipnum);
