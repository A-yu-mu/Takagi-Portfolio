#include "texture.h"
//=============================================================================
//texture.cpp
// 作成者：岸直哉　作成日：2022/06/13
//=============================================================================


//=================================================
//マクロ定義
//=================================================
#define MAX_TEXTURE_NUM (100)

//=================================================
//プロトタイプ宣言
//=================================================


//=================================================
//グローバル変数
//=================================================
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE_NUM];//ロードしたテクスチャの情報配列
static UINT  g_textureIndex = 0;//ロードしたテクスチャの枚数を表す
static char  g_TextuerName[MAX_TEXTURE_NUM][256];//ロードしたテクスチャファイル名のバッファ


//=================================================
//textureのロード
//=================================================
int LoadTexture(char* filename)
{

	//texture名の比較
	for (int i = 0; i < g_textureIndex; i++)
	{
		if (strcmp(g_TextuerName[i], filename) == 0)

			return i;
	}

	if (g_textureIndex == MAX_TEXTURE_NUM)
	{
		return -1;
	}


	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(
		GetDevice(),
		filename,//テクスチャのファイル名
		NULL,
		NULL,
		&g_pTexture[g_textureIndex],//ロードしたテクスチャの情報
		NULL
	);

	if (hr != S_OK)
	{
		return -1; //エラーとしてマイナス値を返す
	}

	//texture名の登録
	strcpy_s(g_TextuerName[g_textureIndex], 256,filename);

	int retIndex = g_textureIndex;//現在の数を保持

	g_textureIndex++;//読み込んだ数をインクリメント

	return retIndex;//読み込んだテクスチャの番号を返す
}



//=================================================
//textureの開放
//=================================================
void UninitTexture()
{
	for (int i = 0; i < g_textureIndex; i++)
	{
		if (g_pTexture[i])
		{
			g_pTexture[i]->Release();
			g_pTexture[i] = NULL;
		}
	}
}



//=================================================
//textureの取得
//=================================================
ID3D11ShaderResourceView** GetTexture(int index)
{
	if (index < 0)//０未満の時
	{
		return NULL;
	}
	if (index >= g_textureIndex)//読み込み数オーバー
	{
		return NULL;
	}

	return &g_pTexture[index];//indexが表す配列のポインタ

}
