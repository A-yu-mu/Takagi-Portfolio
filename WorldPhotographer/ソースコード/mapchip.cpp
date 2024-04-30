//=============================================================================
//mapchip.cpp
// �쐬�ҁF���сA�݁@�쐬���F2022/10/22
//=============================================================================

#include "mapchip.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "camera.h"
#include <iostream>
#include <fstream>
#include "playerCamera.h"
#include "shell.h"
#include "mcgimmick.h"
#include "timelimit.h"

#include "player.h"

#include "layer.h"
//�����鏰�p�G�t�F�N�g
#include "player_effect.h"
#include "player_afterimage.h"
#include "io_ex.h"
using namespace std;

int g_MapChipList[CHIP_NUM_HEIGHT][CHIP_NUM_WIDTH]; //�}�b�v�`�b�v�̃��X�g���[�p
int c = 0;

CHIP g_chip[NUM_CHIP_ALL];

static PLAYER* g_player = GetPlayer();  

PLAYERCAMERA* g_pcamera = GetPlayerCamera();

TimeLimit* g_time_limit = GetTimeLimit2();

//�X�C�b�`��������Ă��邩�ǂ����̃t���O
bool g_switch_on;
//�X�C�b�`�������\�������t���O
bool g_switch_on_next;

// �`���[�g���A���\��(���E�ړ��E�W�����v)�̃t���O
bool g_tutorial_1;
// �`���[�g���A���\��(�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e)�̃t���O
bool g_tutorial_2;
// �`���[�g���A���\��(�v���C���[�Ă��t��)�̃t���O
bool g_tutorial_3;
// �`���[�g���A���\��(�J�����N��)�̃t���O
bool g_tutorial_4;

bool AI_switch_on = false;

bool g_afterImage_switch;


HRESULT InitMapchip(std::string mapdata)
{
    if (mapdata == "data\\stage\\�X�e�[�W1-1\\SMC1_1.txt" || mapdata == "data\\stage\\�X�e�[�W1-2\\SMC1_2.txt" || mapdata == "data\\stage\\�X�e�[�W1-3\\SMC1_3.txt") {
        mapchip[0] = (char*)"data\\texture\\chip1.png";
        mapchip[1] = (char*)"data\\texture\\World1\\Forest_GroundMiddle_60_v01.png";
        mapchip[2] = (char*)"data\\texture\\gimmick\\Thorn_60_v01.png";
        mapchip[3] = (char*)"data\\texture\\gimmick\\cannon.png";
        mapchip[4] = (char*)"data\\texture\\gimmick\\Forest_Jump_64_v01.png";
        mapchip[5] = (char*)"data\\texture\\gimmick\\Flag_01.png";
        mapchip[6] = (char*)"data\\texture\\World1\\Forest_GroundMiddle_60_v01.png";
        mapchip[7] = (char*)"data\\texture\\gimmick\\Thorn_60_v01.png";
        mapchip[8] = (char*)"data\\texture\\World1\\Forest_GroundMiddle_60_v01.png";
        mapchip[9] = (char*)"data\\texture\\chip1.png";
        mapchip[10] = (char*)"data\\texture\\chip1.png";
        mapchip[11] = (char*)"data\\texture\\gimmick\\FallA_60_v01.png";
        mapchip[12] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[13] = (char*)"data\\texture\\gimmick\\Forest_key.png";
        mapchip[14] = (char*)"data\\texture\\gimmick\\Forest_key.png";
        mapchip[15] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[16] = (char*)"data\\texture\\gimmick\\Forest_Switch_onandoff_01_64_v01.png";
        mapchip[17] = (char*)"data\\texture\\gimmick\\Thorn_60_v01.png";
        mapchip[18] = (char*)"data\\texture\\chip1.png";
        mapchip[19] = (char*)"data\\texture\\chip1.png";
        mapchip[20] = (char*)"data\\texture\\chip1.png";
        mapchip[21] = (char*)"data\\texture\\chip1.png";
        mapchip[22] = (char*)"data\\texture\\chip1.png";
        mapchip[23] = (char*)"data\\texture\\chip1.png";
        mapchip[24] = (char*)"data\\texture\\chip1.png";
        mapchip[25] = (char*)"data\\texture\\chip1.png";
        mapchip[26] = (char*)"data\\texture\\chip1.png";
        mapchip[27] = (char*)"data\\texture\\chip1.png";
        mapchip[28] = (char*)"data\\texture\\chip1.png";
    }
    else if (mapdata == "data\\stage\\�X�e�[�W2-1\\SMC2_1.txt" || mapdata == "data\\stage\\�X�e�[�W2-2\\SMC2_2.txt" || mapdata == "data\\stage\\�X�e�[�W2-3\\SMC2_3.txt") {
        mapchip[0] = (char*)"data\\texture\\chip1.png";
        mapchip[1] = (char*)"data\\texture\\World2\\Desert_GroundMiddle_60_v01.png";
        mapchip[2] = (char*)"data\\texture\\gimmick\\Weed_60_v01.png";
        mapchip[3] = (char*)"data\\texture\\gimmick\\cannon.png";
        mapchip[4] = (char*)"data\\texture\\gimmick\\Forest_Jump_64_v01.png";
        mapchip[5] = (char*)"data\\texture\\gimmick\\Flag_01.png";
        mapchip[6] = (char*)"data\\texture\\World2\\Desert_GroundMiddle_60_v01.png";
        mapchip[7] = (char*)"data\\texture\\gimmick\\Weed_60_v01.png";
        mapchip[8] = (char*)"data\\texture\\World2\\Desert_GroundMiddle_60_v01.png";
        mapchip[9] = (char*)"data\\texture\\chip1.png";
        mapchip[10] = (char*)"data\\texture\\chip1.png";
        mapchip[11] = (char*)"data\\texture\\gimmick\\FallA_60_v01.png";
        mapchip[12] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[13] = (char*)"data\\texture\\gimmick\\Forest_key.png";
        mapchip[14] = (char*)"data\\texture\\gimmick\\Forest_key.png";
        mapchip[15] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[16] = (char*)"data\\texture\\gimmick\\Forest_Switch_onandoff_01_64_v01.png";
        mapchip[17] = (char*)"data\\texture\\gimmick\\Weed_60_v01.png";
        mapchip[18] = (char*)"data\\texture\\chip1.png";
        mapchip[19] = (char*)"data\\texture\\chip1.png";
        mapchip[20] = (char*)"data\\texture\\chip1.png";
        mapchip[21] = (char*)"data\\texture\\chip1.png";
        mapchip[22] = (char*)"data\\texture\\chip1.png";
        mapchip[23] = (char*)"data\\texture\\chip1.png";
        mapchip[24] = (char*)"data\\texture\\chip1.png";
        mapchip[25] = (char*)"data\\texture\\chip1.png";
        mapchip[26] = (char*)"data\\texture\\chip1.png";
        mapchip[27] = (char*)"data\\texture\\chip1.png";
        mapchip[28] = (char*)"data\\texture\\chip1.png";

    }
    else if (mapdata == "data\\stage\\�X�e�[�W3-1\\SMC3_1.txt" || mapdata == "data\\stage\\�X�e�[�W3-2\\SMC3_2.txt" || mapdata == "data\\stage\\�X�e�[�W3-3\\SMC3_3.txt") {
        mapchip[0] = (char*)"data\\texture\\chip1.png";
        mapchip[1] = (char*)"data\\texture\\World3\\Snow_GroundMiddle_60_v01.png";
        mapchip[2] = (char*)"data\\texture\\gimmick\\Icespike_60_v01.png";
        mapchip[3] = (char*)"data\\texture\\gimmick\\cannon.png";
        mapchip[4] = (char*)"data\\texture\\gimmick\\Forest_Jump_64_v01.png";
        mapchip[5] = (char*)"data\\texture\\gimmick\\Flag_01.png";
        mapchip[6] = (char*)"data\\texture\\World3\\Snow_GroundMiddle_60_v01.png";
        mapchip[7] = (char*)"data\\texture\\gimmick\\Icespike_60_v01.png";
        mapchip[8] = (char*)"data\\texture\\World3\\Snow_GroundMiddle_60_v01.png";
        mapchip[9] = (char*)"data\\texture\\chip1.png";
        mapchip[10] = (char*)"data\\texture\\chip1.png";
        mapchip[11] = (char*)"data\\texture\\gimmick\\FallA_60_v01.png";
        mapchip[12] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[13] = (char*)"data\\texture\\gimmick\\Forest_key.png";
        mapchip[14] = (char*)"data\\texture\\gimmick\\Ice.png";
        mapchip[15] = (char*)"data\\texture\\gimmick\\Forest_Door.png";
        mapchip[16] = (char*)"data\\texture\\gimmick\\Forest_Switch_onandoff_01_64_v01.png";
        mapchip[17] = (char*)"data\\texture\\gimmick\\Icespike_60_v01.png";
        mapchip[18] = (char*)"data\\texture\\chip1.png";
        mapchip[19] = (char*)"data\\texture\\chip1.png";
        mapchip[20] = (char*)"data\\texture\\chip1.png";
        mapchip[21] = (char*)"data\\texture\\chip1.png";
        mapchip[22] = (char*)"data\\texture\\chip1.png";
        mapchip[23] = (char*)"data\\texture\\chip1.png";
        mapchip[24] = (char*)"data\\texture\\chip1.png";
        mapchip[25] = (char*)"data\\texture\\chip1.png";
        mapchip[26] = (char*)"data\\texture\\chip1.png";
        mapchip[27] = (char*)"data\\texture\\chip1.png";
        mapchip[28] = (char*)"data\\texture\\chip1.png";
    }

   //for (int i = 0; i < 19; i++)
   //{
   //    if (mapdata == "data\\stage\\�X�e�[�W1-1\\SMC1_1.txt" || mapdata == "data\\stage\\�X�e�[�W1-2\\SMC1_2.txt" || mapdata == "data\\stage\\�X�e�[�W1-3\\SMC1_3.txt"){
   //        g_chip[i].texno = LoadTexture(stage1[i]);
   //    }
   //    else if (mapdata == "data\\stage\\�X�e�[�W2-1\\SMC2_1.txt" || mapdata == "data\\stage\\�X�e�[�W2-2\\SMC2_2.txt" || mapdata == "data\\stage\\�X�e�[�W2-3\\SMC2_3.txt"){
   //        g_chip[i].texno = LoadTexture(stage2[i]);
   //    }
   //    else if (mapdata == "data\\stage\\�X�e�[�W3-1\\SMC3_1.txt" || mapdata == "data\\stage\\�X�e�[�W3-2\\SMC3_2.txt" || mapdata == "data\\stage\\�X�e�[�W3-3\\SMC3_3.txt") {
   //        g_chip[i].texno = LoadTexture(stage3[i]);
   //    }
   //}

    for (int i = 0; i < 29; i++)
    {
        g_chip[i].texno = LoadTexture(mapchip[i]);
    }

    ifstream inputfile(mapdata); //�t�@�C���ǂݍ���

    if (!inputfile.is_open())
        cout << "Error opening file";   //�ǂݍ��݃G���[�\��

    /*cout << "�}�b�v�ǂݍ��݊J�n" << endl;*/
    for (int r = 0; r < CHIP_NUM_HEIGHT; r++) 
    {
        for (int c = 0; c < CHIP_NUM_WIDTH; c++) 
        {
            inputfile >> g_MapChipList[r][c];  //�ǂݍ��񂾃t�@�C�����}�b�v�`�b�v���X�g�ɓ����
        }
    }
    /*cout << "�}�b�v�ǂݍ��ݏI��" << endl;*/

    //������
    for (int i = 0; i < NUM_CHIP_ALL; i++)
    {

        g_chip[i].size.x = MAPCHIP_WIDTH;
        g_chip[i].size.y = MAPCHIP_HEIGHT;

        g_chip[i].Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

        g_chip[i].type = CHIP_TYPE::TYPE_1;
        
        g_chip[i].use = true;
        g_chip[i].collision = false;

        g_chip[i].move = 1;

        g_chip[i].movesp = true;

    }
    
    
    int j = 0;
    for (int y = 0; y < CHIP_NUM_HEIGHT; y++) //�`�b�v�̃|�W�V�����z�u
    {
        for (int x = 0; x < CHIP_NUM_WIDTH; x++)
        {
            g_chip[j].pos.x = (float)MAPCHIP_WIDTH * x + MAPCHIP_WIDTH / 2;
            g_chip[j].pos.y = (float)MAPCHIP_HEIGHT * y + MAPCHIP_HEIGHT / 2;

            int i = g_MapChipList[y][x];
            g_chip[j].type = (CHIP_TYPE)i;

            j++;
        }
    }

    for (int i = 0; NUM_CHIP_ALL >= i; i++) //�����`�b�v�p�A���̃`�b�v�̈ʒu
    {
        g_chip[i].originChipPos = g_chip[i].pos;
    }

    g_tutorial_1;
    g_switch_on = false;
    g_switch_on_next = false;
    AI_switch_on = false;
    g_afterImage_switch = false;
	return S_OK;
}

void UninitMapchip()
{
    //for (int i = 0; i < 16; i++)
    //{
    //    if (g_chip[i].texno == LoadTexture(stage1[i])) {
    //        delete stage1[i];
    //    }
    //    else if (g_chip[i].texno == LoadTexture(stage2[i])) {
    //        delete stage2[i];
    //    }
    //    else if (g_chip[i].texno == LoadTexture(stage3[i])) {
    //        delete stage3[i];
    //    }
    //}
    //map<int, char*>::iterator it = stage1.begin();
    //while (it != stage1.end()) {
    //    if (it->second == stage1.) {
    //        stage1.erase(it++);
    //    }
    //    else ++it;
    //}
   
}

void DrawMapchip()
{
    PLAYER* player = GetPlayer();

    int j = 0;
    for (int y = 0; y < CHIP_NUM_HEIGHT; y++)
    {
        for (int x = 0; x < CHIP_NUM_WIDTH; x++)
        {
            int i = (int)g_chip[j].type; //�`�b�v�̎��

            if (g_chip[j].use == true)
            {
                D3DXVECTOR2 scrpos = ScreenPos(g_chip[j].pos); //�X�N���[���������̃`�b�v�̃|�W�V����

                if (i == 6 || i == 7 || i == 8 ||i == 17||
                    player->pos.x + SCREEN_WIDTH > scrpos.x && player->pos.x - SCREEN_WIDTH < scrpos.x &&
                    player->pos.y + SCREEN_HEIGHT > scrpos.y && player->pos.y - SCREEN_HEIGHT < scrpos.y
                    ) //�v���C���[���痣�ꂽ��`���؂�
                {
                    GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_chip[i].texno));
                    //����ȕ`��ƒʏ�`��̐؂�ւ�(2�Ƃ�3��C5�S�[��12��(�J�M)15��(�X�C�b�`)16�X�C�b�`)
                    if(i != 2 && i != 3 && i != 5 && i != 12 && i != 15 && i != 16)
                    {//�ʏ�`��
                    DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, g_chip[j].Color.a),
                        1, 1, 1, 1);
                    }
                    else if (i == 2)
                    {//�Ƃ�(���)�p�\���i���̃`�b�v��0����Ȃ��������A�Ⴄ�Ȃ�t�����j
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type != 0)
                        {//�����̃}�b�v�`�b�v��0�Ȃ獶�ɔ��ˁA����ȊO�Ȃ�E�ɔ���
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 1, 1);
                        }
                        else
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, -1, 1);
                        }
                    }
                    else if (i == 3)
                    {//��C�p�\��
                        if ((int)g_chip[j - 1].type == 0)
                        {//�����̃}�b�v�`�b�v��0�Ȃ獶�ɔ��ˁA����ȊO�Ȃ�E�ɔ���
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 1, 1);
                        }
                        else
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, -1, 1, 1);
                        }
                    }
                    else if (i ==5)
                    {//�S�[���̊��`��i�c�ɘA�Ȃ�}�b�v�`�b�v�̈�Ԃ��������\��������j
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type == 5)//��i���̃`�b�v���S�[���Ȃ瓧���ȃe�N�X�`��
                        {
                            GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_chip[0].texno));
                        }
                        DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                            1, 1, 1, 1);
                    }
                    else if(i == 12)
                    {//���p�`��
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type == 12)//��i���̃`�b�v�����Ȃ�㑤�̃e�N�X�`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                2, 1, 0.5f, 1);
                        }
                        else//�Ⴄ�Ȃ牺���̃e�N�X�`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 0.5f, 1);
                        }

                    }
                   else if(i == 15)
                    {//��(�X�C�b�`)�p�`��
                        if (g_switch_on == true)//�X�C�b�`���������Ȃ甼�����ȕ`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 0, 0, 0.2f),
                                2, 1, 0.5f, 1);
                        }
                        else//�Ⴄ�Ȃ�ʏ�̕`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 0, 0, 1),
                                2, 1, 0.5f, 1);
                        }

                    }
                   else if (i == 16)
                    {//���p�`��
                        if (g_switch_on == true)//�X�C�b�`���������Ȃ牺���̃e�N�X�`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y - MAPCHIP_HEIGHT, 
                                MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 0.5f, 1);
                        }
                        else//�Ⴄ�Ȃ牺���̃e�N�X�`��
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y - MAPCHIP_HEIGHT, 
                                MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                2, 1, 0.5f, 1);
                        }

                        GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_chip[1].texno));
                        DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                            1, 1, 1, 1);
                    }
                }
            }
            j++;
        }
    }
    
}

void UpdateMapchip()
{
    int j = 0; //�}�b�v�`�b�v�w��p
    
    for (int y = 0; y < CHIP_NUM_HEIGHT; y++)
    {
        for (int x = 0; x < CHIP_NUM_WIDTH; x++)
        {
            int i = (int)g_chip[j].type;
            D3DXVECTOR2 scrpos = ScreenPos(g_chip[j].pos);
            if (i == 6 || i == 7 || i == 8 || i == 17 || scrpos.x < SCREEN_WIDTH + 50 && scrpos.x > 0 - 50 && scrpos.y < SCREEN_HEIGHT + 50 && scrpos.y > 0 - 50)
            {
                int i = g_MapChipList[y][x];
                g_chip[j].type = (CHIP_TYPE)i;

                ChipGimmick(j);
            }
            j++;
        }
    }



    if ((g_switch_on_next == false && AI_switch_on == false)
        && g_switch_on == true)//�X�C�b�`��OFF
    {
        PlaySE(SE_SWITCH_OFF);
    }
    //�X�C�b�`�������\�������t���O��true�Ȃ�g_switch_on��true�ɂ���
    if (g_switch_on_next == true || AI_switch_on)
    {
        if (g_switch_on == false)//�X�C�b�`��ON
        {
            PlaySE(SE_SWITCH_ON);
        }
        g_switch_on = true;
    }
    else//�Ⴄ�Ȃ�false��
    {
        g_switch_on = false;
    }
    //�\��̏�����
    g_switch_on_next = false;


    ////�e�X�g�p
    //if (GetKeyboardPress(DIK_S))
    //{
    //    g_switch_on_next = true;
    //}
    //�e�X�g�p
}

CHIP* GetChip()
{
    return g_chip;
}


int* GetMapChipList(int n, int w)
{

    return &g_MapChipList[n][w];
}


void ChipGimmick(int i)
{
    D3DXVECTOR2 scrpos = ScreenPos(g_chip[i].pos);
    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //���̋��
        g_chip[i].use = false;

        break;

    case CHIP_TYPE::TYPE_1: //����
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_2: //��
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_3: //��C
        g_chip[i].collision = true;
        if (NowCameraFlag() == false)
        {
            if (0 < scrpos.x && scrpos.x < SCREEN_WIDTH) //��ʊO�Ƀ`�b�v������Ƃ��M�~�b�N�̓�����~
            {
                
                if (CountShell(i))   //3�b���Ƃɔ���
                {
                    if ((int)g_chip[i - 1].type == 0)
                    {//�����̃}�b�v�`�b�v��0�Ȃ獶�ɔ��ˁA����ȊO�Ȃ�E�ɔ���
                        SetShell(D3DXVECTOR2(g_chip[i].pos.x - MAPCHIP_WIDTH / 2, g_chip[i].pos.y), -1);
                    }
                    else
                    {
                        SetShell(D3DXVECTOR2(g_chip[i].pos.x - MAPCHIP_WIDTH / 2, g_chip[i].pos.y), 1);
                    }
                }
            }
        }

        break;


    case CHIP_TYPE::TYPE_4: //�W�����v
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_5: //�S�[��
        g_chip[i].collision = false;

        break;

    case CHIP_TYPE::TYPE_6: //������
        g_chip[i].collision = true;
        MoveChipX(i, 300, 3);

        break;

    case CHIP_TYPE::TYPE_7: //������(�c)
        g_chip[i].collision = true;
        MoveChipY(i, 100, 3);

        break;
    case CHIP_TYPE::TYPE_8: //������
        g_chip[i].collision = true;
        MoveChipX(i, 50, 1);

        break;

    case CHIP_TYPE::TYPE_9: //�X�N���[���X�g�b�v
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_10: //�X�N���[���X�g�b�v
        g_chip[i].collision = false;

        break;

    case CHIP_TYPE::TYPE_11: //�����鏰
                //���l��0�ȏ�Ȃ�true�ɂ���&&�����Ă����Ȃ����
        if (g_chip[i].Color.a > 0.0f)
        {
            g_chip[i].collision = true;
            //���߂鏈��
            if (SkeletonBlonkDo(i))
            {
                g_chip[i].Color.a -= (1.0f / 120.0f);
                if (g_chip[i].Color.a <= 0.0f)//0�ɂȂ����^�C�~���O�ŉ���炷
                {
                    PlaySE(SE_SKELETON_DELETE);
                }
            }

        }
        //���l��0�Ȃ�false�ɂ���
        else
        {
            if (SkeletonBlonkReborn(i))//�������Ă悢�Ȃ烿�l��߂�
            {
                g_chip[i].Color.a = 1.0f;
                SetPlayerJumpEffect(scrpos.x, scrpos.y - MAPCHIP_HEIGHT, 0.5f);
                PlaySE(SE_SKELETON_REBORN);
            }
            else
            {
                g_chip[i].collision = false;

            }
            
        }
        break;
    case CHIP_TYPE::TYPE_12: //��
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_13: // ��
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_14:
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_15: //���i�X�C�b�`�j
        //�X�C�b�`��on�Ȃ瓖���蔻��͖�����
        if (g_switch_on == true)
        {
            g_chip[i].collision = false;
        }
        else
        {
        g_chip[i].collision = true;

        }
        break;

    case CHIP_TYPE::TYPE_16: //�X�C�b�`
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_17: //������(��)
        g_chip[i].collision = true;
        MoveChipX(i, 100, 2);
        break;

    case CHIP_TYPE::TYPE_18: //����
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_19: //�v���C���[�̊J�n�ʒu
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_21: // �`���[�g���A���\�� (���E�ړ��E�W�����v�J�n)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_22: // �`���[�g���A���\�� (���E�ړ��E�W�����v�I��)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_23: // �`���[�g���A���\�� (�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�J�n)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_24: // �`���[�g���A���\�� (�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�I��)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_25: // �`���[�g���A���\�� (�v���C���[�Ă��t���J�n)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_26: // �`���[�g���A���\�� (�v���C���[�Ă��t���I��)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_27: // �`���[�g���A���\�� (�J�����N���J�n)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_28: // �`���[�g���A���\�� (�J�����N���I��)
        g_chip[i].collision = false;
        break;

    default:
        break;
    }

    if (g_chip[i].type != CHIP_TYPE::TYPE_0) //0�ȊO�̎g�p�t���O��true��
    {
        g_chip[i].use = true;
    }


}

void ChipGimmickColUp(int i)
{
    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //���̋��
        g_player->PlayerLandingEffect = false;
        break;

    case CHIP_TYPE::TYPE_1: //����
        noGravity();
        break;

    case CHIP_TYPE::TYPE_2: //��
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_3: //��C
        noGravity();
        break;

    case CHIP_TYPE::TYPE_4: //�W�����v
        JunpPowerUp();
        break;

    case CHIP_TYPE::TYPE_5://�S�[��
        ScrollStopGoal(i);
        break;

    case CHIP_TYPE::TYPE_6://������
        noGravity();
        ColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_7://������(�c)
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_8://������
        noGravity();
        ColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_9://�X�N���[�����b�N
        ScrollStop(i);
        AfterImageReset();

        break;
    case CHIP_TYPE::TYPE_10://�X�N���[�����b�N����
        ScrollStopLift(i);
        AfterImageReset();
        break;

    case CHIP_TYPE::TYPE_11://�����鏰

                            //���̓����x�������Ă����烿�l�����炵�ē����蔻���t����
        if (g_chip[i].Color.a > 0.0f)
        {
            noGravity();
            SkeletonBlonkStart(i);
            //�����g�p�ύX�ɂ��R�����g
            //g_chip[i].Color.a -= (1.0f / 90.0f);
            //if (g_chip[i].Color.a <= 0.0f)//0�ɂȂ����^�C�~���O�ŉ���炷��
            //{
            //    PlaySE(SE_SKELETON_DELETE);
            //}
        }
        //������Ή������Ȃ�
        else
        {
            g_chip[i].Color.a = 0.0f;
        }
        break;
    case CHIP_TYPE::TYPE_12: //��
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;�@//�J�����̎g�p���킩���������
        noGravity();
        break;
    case CHIP_TYPE::TYPE_13: //�J�M
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;�@//�J�����̎g�p���킩���������
        //noGravity();
        //�J�M�͏ォ���������������o����悤�ɂ��̊֐����Ăт܂�
        ChipGimmickColOthers(i);
        break;

    case CHIP_TYPE::TYPE_14:
        noGravity();
        IceBlock();


    case CHIP_TYPE::TYPE_15: //��(�X�C�b�`)
        break;
    case CHIP_TYPE::TYPE_16: //�X�C�b�`
        noGravity();
        //�X�C�b�`�̏�ɂ���Ȃ�t���O��on�ɂ���\��inext�j������
        g_switch_on_next = true;
        //SetSwitchOn(true);

        break;

    case CHIP_TYPE::TYPE_17: //������(��)
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_18: //����
        g_player->life = -1;
        PlaySE(SE_DAMAGE);
        break;

    case CHIP_TYPE::TYPE_19: //�v���C���[�̊J�n�ʒu
        g_player->PlayerLandingEffect = false;
        break;

    default:
        break;
    }
}

void ChipGimmickColOthers(int i)
{
    //�}�b�v�`�b�v���������ɕK�v
    int j = 0;
    PLAYER* player = GetPlayer();
    bool Break = true;

    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //���̋��

        break;

    case CHIP_TYPE::TYPE_1: //����
        break;

    case CHIP_TYPE::TYPE_2: //�����蔻��̂Ȃ��u���b�N
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_3: //��C
        break;

    case CHIP_TYPE::TYPE_4: //�W�����v
        break;

    case CHIP_TYPE::TYPE_5://�S�[��
        //SetScene(SCENE_RESULT);
        ScrollStopGoal(i);

        break;

    case CHIP_TYPE::TYPE_6://������
        break;

    case CHIP_TYPE::TYPE_7://������(�c)
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_8://������
        break;

    case CHIP_TYPE::TYPE_9://�X�N���[���X�g�b�v
        ScrollStop(i);
        SetLayerNextMC09();

        break;

    case CHIP_TYPE::TYPE_10:
        ScrollStopLift(i);
        SetLayerNextMC10();
        break;
    case CHIP_TYPE::TYPE_12://��
        //for���Ŕ��̃}�b�v�`�b�v�̈ʒu��T��
        j = 0;
        Break = true;
        //�v���C���[�̃J�M�t���O��true�̎������������s��
        if (player->keyuse == true)
        {
            for (int y = 0; y < CHIP_NUM_HEIGHT && Break == true; y++)
            {
                for (int x = 0; x < CHIP_NUM_WIDTH && Break == true; x++)
                {
                    //�J�M�̏ꏊ�܂ŗ�����}�b�v�`�b�v��0�ɂ���break����
                    if (j == i)
                    {
                        g_MapChipList[y][x] = 0;
                        //�v���C���[�̃J�M�t���O��false�ɂ���
                        player->keyuse_next = false;
                        //break;
                        Break = false;
                        PlaySE(SE_USE_KYE);
                        //1�i�����`�b�v12�Ȃ炻����0�ɂ���
                        if (g_MapChipList[y + 1][x] == 12)
                        {
                            g_MapChipList[y + 1][x] = 0;
                        }
                    }
                    j++;
                }
            }
        }


        break;
    case CHIP_TYPE::TYPE_13://��
        j = 0;
        Break = true;
        for (int y = 0; y < CHIP_NUM_HEIGHT && Break == true; y++)
        {
            for (int x = 0; x < CHIP_NUM_WIDTH && Break == true; x++)
            {
                //���̏ꏊ�܂ŗ�����}�b�v�`�b�v��0�ɂ���break����
                if (j == i)
                {
                    g_MapChipList[y][x]  = 0;
                    //�v���C���[�̃J�M�t���O��true�ɂ���
                    player->keyuse = true;
                    player->keyuse_next = true;
                    //break;
                    Break = false;                    
                    PlaySE(SE_GET_KEY);
                }
                j++;
            }
        }
        break;

    case CHIP_TYPE::TYPE_15://������
        
        break;
    case CHIP_TYPE::TYPE_17: //������(��)
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_18: //����
        g_player->life = -1;
        PlaySE(SE_DAMAGE);
        break;

    case CHIP_TYPE::TYPE_19: //�v���C���[�̊J�n�ʒu

        break;

    case CHIP_TYPE::TYPE_20:
        AfterImageReset();
        SetAISwitch(false);
        break;

    case CHIP_TYPE::TYPE_21: // �`���[�g���A���\�� (���E�ړ��E�W�����v�J�n)
        g_tutorial_1 = true;
        break;

    case CHIP_TYPE::TYPE_22: // �`���[�g���A���\�� (���E�ړ��E�W�����v�I��)
        g_tutorial_1 = false;
        break;

    case CHIP_TYPE::TYPE_23: // �`���[�g���A���\�� (�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�J�n)
        g_tutorial_2 = true;
        break;

    case CHIP_TYPE::TYPE_24: // �`���[�g���A���\�� (�J�����s���g�����E�B�e�ʒu�����E�ʐ^�B�e�I��)
        g_tutorial_2 = false;
        break;

    case CHIP_TYPE::TYPE_25: // �`���[�g���A���\�� (���C���[�Ă��t���J�n)
        g_tutorial_3 = true;
        break;

    case CHIP_TYPE::TYPE_26: // �`���[�g���A���\�� (���C���[�Ă��t���I��)
        g_tutorial_3 = false;
        break;

    case CHIP_TYPE::TYPE_27: // �`���[�g���A���\�� (�J�����N���J�n)
        g_tutorial_4 = true;
        break;

    case CHIP_TYPE::TYPE_28: // �`���[�g���A���\�� (�J�����N���I��)
        g_tutorial_4 = false;

    default:
        break;
    }
}

void PlayerAfterChipGimmick(int i) //�Ă��t���p�̏���
{
    //PLAYER* pl = GetPlayer();
    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //���̋��

        break;

    case CHIP_TYPE::TYPE_1: //����
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_2: //��
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_3: //��C
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_4: //�W�����v
        break;

    case CHIP_TYPE::TYPE_5://�S�[��
        break;

    case CHIP_TYPE::TYPE_6://������
        afterimageGravity();
        AIColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_7://������
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_8://������
        afterimageGravity();
        AIColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_9://�X�N���[�����b�N
        break;
    case CHIP_TYPE::TYPE_10://�X�N���[�����b�N����
        break;

    case CHIP_TYPE::TYPE_11://�����鏰

                            //���̓����x�������Ă����烿�l�����炵�ē����蔻���t����
        if (g_chip[i].Color.a > 0.0f)
        {
            afterimageGravity();
            g_chip[i].Color.a -= (1.0f / 60.0f);
        }
        //������Ή������Ȃ�
        else
        {
            g_chip[i].Color.a = 0.0f;

        }
        break;
    case CHIP_TYPE::TYPE_12: //��
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;�@//�J�����̎g�p���킩���������
        afterimageGravity();
        break;
    case CHIP_TYPE::TYPE_13: //�J�M
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;�@//�J�����̎g�p���킩���������
        //noGravity();
        //�J�M�͏ォ���������������o����悤�ɂ��̊֐����Ăт܂�
        break;
    case CHIP_TYPE::TYPE_14: //�X
        break;

    case CHIP_TYPE::TYPE_15: //��(�X�C�b�`)
        afterimageGravity();
        break;
    case CHIP_TYPE::TYPE_16: //�X�C�b�`
        afterimageGravity();
        //�X�C�b�`�̏�ɂ���Ȃ�t���O��on�ɂ���\��inext�j������
        AI_switch_on = true;
        //SetSwitchOn(true);
        break;
    case CHIP_TYPE::TYPE_17: //������(��)
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_18: //����
        break;
    case CHIP_TYPE::TYPE_19: //�v���C���[�̊J�n�ʒu
        break;

    default:
        break;
    }
}

bool GetSwitchOn()
{
    return g_switch_on;
}

bool GetTutorial1()
{
    return g_tutorial_1;
}

bool GetTutorial2()
{
    return g_tutorial_2;
}

bool GetTutorial3()
{
    return g_tutorial_3;
}

bool GetTutorial4()
{
    return g_tutorial_4;
}

void SetTutorial1(bool set_tutorial_1)
{
    g_tutorial_1 = set_tutorial_1;
}

void SetTutorial2(bool set_tutorial_2)
{
    g_tutorial_2 = set_tutorial_2;
}

void SetTutorial3(bool set_tutorial_3)
{
    g_tutorial_3 = set_tutorial_3;
}

void SetTutorial4(bool set_tutorial_4)
{
    g_tutorial_4 = set_tutorial_4;
}

void SetSwitchOn(bool b)
{
    g_switch_on = b;
}

void SetAISwitch(bool b)
{
    AI_switch_on = b;
}