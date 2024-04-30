//=============================================================================
//mapchip.cpp
// 作成者：小林、岸　作成日：2022/10/22
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
//消える床用エフェクト
#include "player_effect.h"
#include "player_afterimage.h"
#include "io_ex.h"
using namespace std;

int g_MapChipList[CHIP_NUM_HEIGHT][CHIP_NUM_WIDTH]; //マップチップのリスト収納用
int c = 0;

CHIP g_chip[NUM_CHIP_ALL];

static PLAYER* g_player = GetPlayer();  

PLAYERCAMERA* g_pcamera = GetPlayerCamera();

TimeLimit* g_time_limit = GetTimeLimit2();

//スイッチが押されているかどうかのフラグ
bool g_switch_on;
//スイッチが押す予約をするフラグ
bool g_switch_on_next;

// チュートリアル表示(左右移動・ジャンプ)のフラグ
bool g_tutorial_1;
// チュートリアル表示(カメラピント調整・撮影位置調整・写真撮影)のフラグ
bool g_tutorial_2;
// チュートリアル表示(プレイヤー焼き付け)のフラグ
bool g_tutorial_3;
// チュートリアル表示(カメラ起動)のフラグ
bool g_tutorial_4;

bool AI_switch_on = false;

bool g_afterImage_switch;


HRESULT InitMapchip(std::string mapdata)
{
    if (mapdata == "data\\stage\\ステージ1-1\\SMC1_1.txt" || mapdata == "data\\stage\\ステージ1-2\\SMC1_2.txt" || mapdata == "data\\stage\\ステージ1-3\\SMC1_3.txt") {
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
    else if (mapdata == "data\\stage\\ステージ2-1\\SMC2_1.txt" || mapdata == "data\\stage\\ステージ2-2\\SMC2_2.txt" || mapdata == "data\\stage\\ステージ2-3\\SMC2_3.txt") {
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
    else if (mapdata == "data\\stage\\ステージ3-1\\SMC3_1.txt" || mapdata == "data\\stage\\ステージ3-2\\SMC3_2.txt" || mapdata == "data\\stage\\ステージ3-3\\SMC3_3.txt") {
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
   //    if (mapdata == "data\\stage\\ステージ1-1\\SMC1_1.txt" || mapdata == "data\\stage\\ステージ1-2\\SMC1_2.txt" || mapdata == "data\\stage\\ステージ1-3\\SMC1_3.txt"){
   //        g_chip[i].texno = LoadTexture(stage1[i]);
   //    }
   //    else if (mapdata == "data\\stage\\ステージ2-1\\SMC2_1.txt" || mapdata == "data\\stage\\ステージ2-2\\SMC2_2.txt" || mapdata == "data\\stage\\ステージ2-3\\SMC2_3.txt"){
   //        g_chip[i].texno = LoadTexture(stage2[i]);
   //    }
   //    else if (mapdata == "data\\stage\\ステージ3-1\\SMC3_1.txt" || mapdata == "data\\stage\\ステージ3-2\\SMC3_2.txt" || mapdata == "data\\stage\\ステージ3-3\\SMC3_3.txt") {
   //        g_chip[i].texno = LoadTexture(stage3[i]);
   //    }
   //}

    for (int i = 0; i < 29; i++)
    {
        g_chip[i].texno = LoadTexture(mapchip[i]);
    }

    ifstream inputfile(mapdata); //ファイル読み込み

    if (!inputfile.is_open())
        cout << "Error opening file";   //読み込みエラー表示

    /*cout << "マップ読み込み開始" << endl;*/
    for (int r = 0; r < CHIP_NUM_HEIGHT; r++) 
    {
        for (int c = 0; c < CHIP_NUM_WIDTH; c++) 
        {
            inputfile >> g_MapChipList[r][c];  //読み込んだファイルをマップチップリストに入れる
        }
    }
    /*cout << "マップ読み込み終了" << endl;*/

    //初期化
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
    for (int y = 0; y < CHIP_NUM_HEIGHT; y++) //チップのポジション配置
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

    for (int i = 0; NUM_CHIP_ALL >= i; i++) //動くチップ用、元のチップの位置
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
            int i = (int)g_chip[j].type; //チップの種類

            if (g_chip[j].use == true)
            {
                D3DXVECTOR2 scrpos = ScreenPos(g_chip[j].pos); //スクロールした時のチップのポジション

                if (i == 6 || i == 7 || i == 8 ||i == 17||
                    player->pos.x + SCREEN_WIDTH > scrpos.x && player->pos.x - SCREEN_WIDTH < scrpos.x &&
                    player->pos.y + SCREEN_HEIGHT > scrpos.y && player->pos.y - SCREEN_HEIGHT < scrpos.y
                    ) //プレイヤーから離れたら描画を切る
                {
                    GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_chip[i].texno));
                    //特殊な描画と通常描画の切り替え(2とげ3大砲5ゴール12扉(カギ)15扉(スイッチ)16スイッチ)
                    if(i != 2 && i != 3 && i != 5 && i != 12 && i != 15 && i != 16)
                    {//通常描画
                    DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, g_chip[j].Color.a),
                        1, 1, 1, 1);
                    }
                    else if (i == 2)
                    {//とげ(つらら)用表示（下のチップが0じゃない正向き、違うなら逆向き）
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type != 0)
                        {//左側のマップチップが0なら左に発射、それ以外なら右に発射
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
                    {//大砲用表示
                        if ((int)g_chip[j - 1].type == 0)
                        {//左側のマップチップが0なら左に発射、それ以外なら右に発射
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
                    {//ゴールの旗描画（縦に連なるマップチップの一番しただけ表示をする）
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type == 5)//一段下のチップもゴールなら透明なテクスチャ
                        {
                            GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_chip[0].texno));
                        }
                        DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                            1, 1, 1, 1);
                    }
                    else if(i == 12)
                    {//扉用描画
                        if ((int)g_chip[j + CHIP_NUM_WIDTH].type == 12)//一段下のチップも扉なら上側のテクスチャ
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                2, 1, 0.5f, 1);
                        }
                        else//違うなら下側のテクスチャ
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 0.5f, 1);
                        }

                    }
                   else if(i == 15)
                    {//扉(スイッチ)用描画
                        if (g_switch_on == true)//スイッチが押されるなら半透明な描画
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 0, 0, 0.2f),
                                2, 1, 0.5f, 1);
                        }
                        else//違うなら通常の描画
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y, MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 0, 0, 1),
                                2, 1, 0.5f, 1);
                        }

                    }
                   else if (i == 16)
                    {//扉用描画
                        if (g_switch_on == true)//スイッチが押されるなら下側のテクスチャ
                        {
                            DrawSpriteColorRotation(scrpos.x, scrpos.y - MAPCHIP_HEIGHT, 
                                MAPCHIP_WIDTH, MAPCHIP_HEIGHT, 0, D3DXCOLOR(1, 1, 1, 1),
                                1, 1, 0.5f, 1);
                        }
                        else//違うなら下側のテクスチャ
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
    int j = 0; //マップチップ指定用
    
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
        && g_switch_on == true)//スイッチ音OFF
    {
        PlaySE(SE_SWITCH_OFF);
    }
    //スイッチが押す予約をするフラグがtrueならg_switch_onをtrueにする
    if (g_switch_on_next == true || AI_switch_on)
    {
        if (g_switch_on == false)//スイッチ音ON
        {
            PlaySE(SE_SWITCH_ON);
        }
        g_switch_on = true;
    }
    else//違うならfalseに
    {
        g_switch_on = false;
    }
    //予約の初期化
    g_switch_on_next = false;


    ////テスト用
    //if (GetKeyboardPress(DIK_S))
    //{
    //    g_switch_on_next = true;
    //}
    //テスト用
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
    case CHIP_TYPE::TYPE_0: //無の空間
        g_chip[i].use = false;

        break;

    case CHIP_TYPE::TYPE_1: //足場
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_2: //棘
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_3: //大砲
        g_chip[i].collision = true;
        if (NowCameraFlag() == false)
        {
            if (0 < scrpos.x && scrpos.x < SCREEN_WIDTH) //画面外にチップがあるときギミックの動作を停止
            {
                
                if (CountShell(i))   //3秒ごとに発射
                {
                    if ((int)g_chip[i - 1].type == 0)
                    {//左側のマップチップが0なら左に発射、それ以外なら右に発射
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


    case CHIP_TYPE::TYPE_4: //ジャンプ
        g_chip[i].collision = true;

        break;

    case CHIP_TYPE::TYPE_5: //ゴール
        g_chip[i].collision = false;

        break;

    case CHIP_TYPE::TYPE_6: //動く床
        g_chip[i].collision = true;
        MoveChipX(i, 300, 3);

        break;

    case CHIP_TYPE::TYPE_7: //動く棘(縦)
        g_chip[i].collision = true;
        MoveChipY(i, 100, 3);

        break;
    case CHIP_TYPE::TYPE_8: //動く床
        g_chip[i].collision = true;
        MoveChipX(i, 50, 1);

        break;

    case CHIP_TYPE::TYPE_9: //スクロールストップ
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_10: //スクロールストップ
        g_chip[i].collision = false;

        break;

    case CHIP_TYPE::TYPE_11: //消える床
                //α値が0以上ならtrueにする&&消していいなら消す
        if (g_chip[i].Color.a > 0.0f)
        {
            g_chip[i].collision = true;
            //薄める処理
            if (SkeletonBlonkDo(i))
            {
                g_chip[i].Color.a -= (1.0f / 120.0f);
                if (g_chip[i].Color.a <= 0.0f)//0になったタイミングで音を鳴らす
                {
                    PlaySE(SE_SKELETON_DELETE);
                }
            }

        }
        //α値が0ならfalseにする
        else
        {
            if (SkeletonBlonkReborn(i))//復活してよいならα値を戻す
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
    case CHIP_TYPE::TYPE_12: //扉
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_13: // 鍵
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_14:
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_15: //扉（スイッチ）
        //スイッチがonなら当たり判定は無くす
        if (g_switch_on == true)
        {
            g_chip[i].collision = false;
        }
        else
        {
        g_chip[i].collision = true;

        }
        break;

    case CHIP_TYPE::TYPE_16: //スイッチ
        g_chip[i].collision = true;
        break;

    case CHIP_TYPE::TYPE_17: //動く棘(横)
        g_chip[i].collision = true;
        MoveChipX(i, 100, 2);
        break;

    case CHIP_TYPE::TYPE_18: //即死
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_19: //プレイヤーの開始位置
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_21: // チュートリアル表示 (左右移動・ジャンプ開始)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_22: // チュートリアル表示 (左右移動・ジャンプ終了)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_23: // チュートリアル表示 (カメラピント調整・撮影位置調整・写真撮影開始)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_24: // チュートリアル表示 (カメラピント調整・撮影位置調整・写真撮影終了)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_25: // チュートリアル表示 (プレイヤー焼き付け開始)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_26: // チュートリアル表示 (プレイヤー焼き付け終了)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_27: // チュートリアル表示 (カメラ起動開始)
        g_chip[i].collision = false;
        break;

    case CHIP_TYPE::TYPE_28: // チュートリアル表示 (カメラ起動終了)
        g_chip[i].collision = false;
        break;

    default:
        break;
    }

    if (g_chip[i].type != CHIP_TYPE::TYPE_0) //0以外の使用フラグをtrueに
    {
        g_chip[i].use = true;
    }


}

void ChipGimmickColUp(int i)
{
    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //無の空間
        g_player->PlayerLandingEffect = false;
        break;

    case CHIP_TYPE::TYPE_1: //足場
        noGravity();
        break;

    case CHIP_TYPE::TYPE_2: //棘
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_3: //大砲
        noGravity();
        break;

    case CHIP_TYPE::TYPE_4: //ジャンプ
        JunpPowerUp();
        break;

    case CHIP_TYPE::TYPE_5://ゴール
        ScrollStopGoal(i);
        break;

    case CHIP_TYPE::TYPE_6://動く床
        noGravity();
        ColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_7://動く棘(縦)
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_8://動く床
        noGravity();
        ColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_9://スクロールロック
        ScrollStop(i);
        AfterImageReset();

        break;
    case CHIP_TYPE::TYPE_10://スクロールロック解除
        ScrollStopLift(i);
        AfterImageReset();
        break;

    case CHIP_TYPE::TYPE_11://消える床

                            //床の透明度が見えていたらα値を減らして当たり判定を付ける
        if (g_chip[i].Color.a > 0.0f)
        {
            noGravity();
            SkeletonBlonkStart(i);
            //消す使用変更につきコメント
            //g_chip[i].Color.a -= (1.0f / 90.0f);
            //if (g_chip[i].Color.a <= 0.0f)//0になったタイミングで音を鳴らすを
            //{
            //    PlaySE(SE_SKELETON_DELETE);
            //}
        }
        //無ければ何もしない
        else
        {
            g_chip[i].Color.a = 0.0f;
        }
        break;
    case CHIP_TYPE::TYPE_12: //扉
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;　//カメラの使用がわかったら解禁
        noGravity();
        break;
    case CHIP_TYPE::TYPE_13: //カギ
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;　//カメラの使用がわかったら解禁
        //noGravity();
        //カギは上から乗った時も所得出来るようにこの関数を呼びます
        ChipGimmickColOthers(i);
        break;

    case CHIP_TYPE::TYPE_14:
        noGravity();
        IceBlock();


    case CHIP_TYPE::TYPE_15: //扉(スイッチ)
        break;
    case CHIP_TYPE::TYPE_16: //スイッチ
        noGravity();
        //スイッチの上にいるならフラグをonにする予約（next）をする
        g_switch_on_next = true;
        //SetSwitchOn(true);

        break;

    case CHIP_TYPE::TYPE_17: //動く棘(横)
        noGravity();
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_18: //即死
        g_player->life = -1;
        PlaySE(SE_DAMAGE);
        break;

    case CHIP_TYPE::TYPE_19: //プレイヤーの開始位置
        g_player->PlayerLandingEffect = false;
        break;

    default:
        break;
    }
}

void ChipGimmickColOthers(int i)
{
    //マップチップ書き換えに必要
    int j = 0;
    PLAYER* player = GetPlayer();
    bool Break = true;

    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //無の空間

        break;

    case CHIP_TYPE::TYPE_1: //足場
        break;

    case CHIP_TYPE::TYPE_2: //当たり判定のないブロック
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_3: //大砲
        break;

    case CHIP_TYPE::TYPE_4: //ジャンプ
        break;

    case CHIP_TYPE::TYPE_5://ゴール
        //SetScene(SCENE_RESULT);
        ScrollStopGoal(i);

        break;

    case CHIP_TYPE::TYPE_6://動く床
        break;

    case CHIP_TYPE::TYPE_7://動く棘(縦)
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_8://動く床
        break;

    case CHIP_TYPE::TYPE_9://スクロールストップ
        ScrollStop(i);
        SetLayerNextMC09();

        break;

    case CHIP_TYPE::TYPE_10:
        ScrollStopLift(i);
        SetLayerNextMC10();
        break;
    case CHIP_TYPE::TYPE_12://扉
        //for文で扉のマップチップの位置を探す
        j = 0;
        Break = true;
        //プレイヤーのカギフラグがtrueの時だけ処理を行う
        if (player->keyuse == true)
        {
            for (int y = 0; y < CHIP_NUM_HEIGHT && Break == true; y++)
            {
                for (int x = 0; x < CHIP_NUM_WIDTH && Break == true; x++)
                {
                    //カギの場所まで来たらマップチップを0にしてbreakする
                    if (j == i)
                    {
                        g_MapChipList[y][x] = 0;
                        //プレイヤーのカギフラグをfalseにする
                        player->keyuse_next = false;
                        //break;
                        Break = false;
                        PlaySE(SE_USE_KYE);
                        //1段下もチップ12ならそこも0にする
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
    case CHIP_TYPE::TYPE_13://鍵
        j = 0;
        Break = true;
        for (int y = 0; y < CHIP_NUM_HEIGHT && Break == true; y++)
        {
            for (int x = 0; x < CHIP_NUM_WIDTH && Break == true; x++)
            {
                //扉の場所まで来たらマップチップを0にしてbreakする
                if (j == i)
                {
                    g_MapChipList[y][x]  = 0;
                    //プレイヤーのカギフラグをtrueにする
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

    case CHIP_TYPE::TYPE_15://ｽｲｯﾁ扉
        
        break;
    case CHIP_TYPE::TYPE_17: //動く棘(横)
        LifeDamage();
        break;

    case CHIP_TYPE::TYPE_18: //即死
        g_player->life = -1;
        PlaySE(SE_DAMAGE);
        break;

    case CHIP_TYPE::TYPE_19: //プレイヤーの開始位置

        break;

    case CHIP_TYPE::TYPE_20:
        AfterImageReset();
        SetAISwitch(false);
        break;

    case CHIP_TYPE::TYPE_21: // チュートリアル表示 (左右移動・ジャンプ開始)
        g_tutorial_1 = true;
        break;

    case CHIP_TYPE::TYPE_22: // チュートリアル表示 (左右移動・ジャンプ終了)
        g_tutorial_1 = false;
        break;

    case CHIP_TYPE::TYPE_23: // チュートリアル表示 (カメラピント調整・撮影位置調整・写真撮影開始)
        g_tutorial_2 = true;
        break;

    case CHIP_TYPE::TYPE_24: // チュートリアル表示 (カメラピント調整・撮影位置調整・写真撮影終了)
        g_tutorial_2 = false;
        break;

    case CHIP_TYPE::TYPE_25: // チュートリアル表示 (レイヤー焼き付け開始)
        g_tutorial_3 = true;
        break;

    case CHIP_TYPE::TYPE_26: // チュートリアル表示 (レイヤー焼き付け終了)
        g_tutorial_3 = false;
        break;

    case CHIP_TYPE::TYPE_27: // チュートリアル表示 (カメラ起動開始)
        g_tutorial_4 = true;
        break;

    case CHIP_TYPE::TYPE_28: // チュートリアル表示 (カメラ起動終了)
        g_tutorial_4 = false;

    default:
        break;
    }
}

void PlayerAfterChipGimmick(int i) //焼き付け用の処理
{
    //PLAYER* pl = GetPlayer();
    switch (g_chip[i].type)
    {
    case CHIP_TYPE::TYPE_0: //無の空間

        break;

    case CHIP_TYPE::TYPE_1: //足場
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_2: //棘
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_3: //大砲
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_4: //ジャンプ
        break;

    case CHIP_TYPE::TYPE_5://ゴール
        break;

    case CHIP_TYPE::TYPE_6://動く床
        afterimageGravity();
        AIColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_7://動く棘
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_8://動く床
        afterimageGravity();
        AIColMoveChipX(i);
        break;

    case CHIP_TYPE::TYPE_9://スクロールロック
        break;
    case CHIP_TYPE::TYPE_10://スクロールロック解除
        break;

    case CHIP_TYPE::TYPE_11://消える床

                            //床の透明度が見えていたらα値を減らして当たり判定を付ける
        if (g_chip[i].Color.a > 0.0f)
        {
            afterimageGravity();
            g_chip[i].Color.a -= (1.0f / 60.0f);
        }
        //無ければ何もしない
        else
        {
            g_chip[i].Color.a = 0.0f;

        }
        break;
    case CHIP_TYPE::TYPE_12: //扉
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;　//カメラの使用がわかったら解禁
        afterimageGravity();
        break;
    case CHIP_TYPE::TYPE_13: //カギ
        //SetScene(SCENE_RESULT);
        //g_chip[i].type = CHIP_TYPE::TYPE_13;　//カメラの使用がわかったら解禁
        //noGravity();
        //カギは上から乗った時も所得出来るようにこの関数を呼びます
        break;
    case CHIP_TYPE::TYPE_14: //氷
        break;

    case CHIP_TYPE::TYPE_15: //扉(スイッチ)
        afterimageGravity();
        break;
    case CHIP_TYPE::TYPE_16: //スイッチ
        afterimageGravity();
        //スイッチの上にいるならフラグをonにする予約（next）をする
        AI_switch_on = true;
        //SetSwitchOn(true);
        break;
    case CHIP_TYPE::TYPE_17: //動く棘(横)
        afterimageGravity();
        break;

    case CHIP_TYPE::TYPE_18: //即死
        break;
    case CHIP_TYPE::TYPE_19: //プレイヤーの開始位置
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