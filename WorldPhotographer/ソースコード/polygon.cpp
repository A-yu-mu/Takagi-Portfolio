/*==============================================================================

   頂点管理 [polygon.cpp]								Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "polygon.h"
#include "sprite.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX_LINESTRIP (64)	//ラインストリップ頂点最大数

#define	BOX_W	(80)	//四角形の横のサイズ
#define	BOX_H	(80)	//四角形の縦のサイズ

#define FIELD_W (SCREEN_WIDTH)
#define FIELD_H (SCREEN_HEIGHT / 2 + 120)



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void	SetVertexLineStrip(int);							//ラインストリップ頂点格納処理
void	SetVertexLine(float, float, float, float,float);			//直線用頂点格納処理
void	SetVertexCircle(float, float, float, int, D3DXCOLOR);	//多角形の表示


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static	ID3D11Buffer		*g_VertexBufferLineStrip = NULL;//ラインストリップ用
static	ID3D11Buffer		*g_VertexBufferLine = NULL;		//直線用

static	ID3D11Buffer		*g_VertexBufferCircle = NULL;	//多角形用



float	PositionX = SCREEN_WIDTH / 2;//画面中央座標
float	PositionY = SCREEN_HEIGHT / 2;
float	Kakudo = 0; //四角形の回転角度

float	StartPositionX = 0;				//直線のスタート座標
float	StartPositionY = 0;
float	EndPositionX = SCREEN_WIDTH;	//直線の終了座標
float	EndPositionY = SCREEN_HEIGHT;


//テクスチャ情報の保存変数


static	ID3D11ShaderResourceView* g_TextureBG;//画像1枚で1つの変数が必要
static	char    * g_TextureNameBG = BG_01;//テクスチャファイルパス JPG BMP PNG


D3DXVECTOR3 Goal = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
D3DXVECTOR3 Speed;
D3DXVECTOR3 Start;


//キャラクター構造体

typedef struct
{
	D3DXVECTOR3 Position; //表示座標
	D3DXCOLOR   Color;    //表示色
	float       Rotation; //角度
	D3DXVECTOR2 size;	  //ポリゴンのサイズ

}PLAYER;

PLAYER mario;//プレイヤーキャラクター構造体

typedef struct
{
	D3DXVECTOR3 Position; //表示座標
	D3DXCOLOR   Color;    //表示色
	float       Rotation; //角度
	D3DXVECTOR2 size;	  //ポリゴンのサイズ
}BG;

BG *Bg;//背景構造体のポインタ変数

//textureのインデックス

static int g_textureNo = 0;
static int g_textureNoBG = 0;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolygon(void)
{
	//乱数の初期化
	srand(timeGetTime());
	//ポリゴンの表示座標をランダムに決定
	PositionX = rand() % SCREEN_WIDTH;
	PositionY = rand() % SCREEN_HEIGHT;
	
	Start.x = PositionX;
	Start.y = PositionY;
	Start.z = 0.0f;

	//目的地までのベクトルを作る
	Speed = Goal - Start;
	//正規化して長さを１にする
	D3DXVec3Normalize(&Speed, &Speed);
	//ベクトルを任意の長さにする
	Speed *= 10.0f;


	ID3D11Device *pDevice = GetDevice();

	//textureのロード
	g_textureNoBG = LoadTexture(g_TextureNameBG);
	if (g_textureNo == -1)
	{//ロードエラー
		exit(999);//強制終了
	}
	



	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX_LINESTRIP;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLineStrip);
		// 頂点バッファ更新
		SetVertexLineStrip(4);
	}
	
	{//直線用
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 2;			//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferLine);
		//直線用頂点格納処理
		SetVertexLine(StartPositionX, StartPositionY, EndPositionX, EndPositionY,30.0f);
	}
	{//多角形用
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 64;	//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferCircle);

		//多角形用頂点格納処理
		D3DXCOLOR	col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		SetVertexCircle(300.0f, 500.0f, 100.0f, 32, col);

	}

	InitSprite();

	//背景の初期化
	Bg = new BG;//背景のインスタンス作成
	Bg->Position.x = SCREEN_WIDTH / 2;
	Bg->Position.y = SCREEN_HEIGHT / 2;
	Bg->Position.z = 0;

	Bg->size.x = SCREEN_WIDTH;
	Bg->size.y = SCREEN_HEIGHT;

	Bg->Rotation = 0.0f;

	Bg->Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	// 頂点バッファの解放
	if (g_VertexBufferLineStrip)
	{
		g_VertexBufferLineStrip->Release();//使い終わったので解放する
		g_VertexBufferLineStrip = NULL;
	}

	if (g_VertexBufferLine)
	{
		g_VertexBufferLine->Release();//使い終わったので解放する
		g_VertexBufferLine = NULL;
	}

	if (g_VertexBufferCircle)
	{
		g_VertexBufferCircle->Release();//使い終わったので解放する
		g_VertexBufferCircle = NULL;
	}

	////テクスチャの解放
	//if (g_Texture)
	//{
	//	g_Texture->Release();
	//	g_Texture = NULL;
	//}

	//if (g_TextureBG)
	//{
	//	g_TextureBG->Release();
	//	g_TextureBG = NULL;
	//}

	UninitTexture();

	UninitSprite();

	//BG構造体の開放
	if (Bg)
	{
		delete Bg;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{
	Start += Speed;//移動する

	PositionX = Start.x;
	PositionY = Start.y;

	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	// ２Ｄ表示をするためのマトリクスを設定
	SetWorldViewProjection2D();	
	
	{   //背景の描画

		GetDeviceContext()->PSSetShaderResources(0, 1,GetTexture(g_textureNoBG));
		D3DXCOLOR col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		//三角形の頂点データを格納
		DrawSpriteColorRotation(Bg->Position.x, Bg->Position.y, Bg->size.x, Bg->size.y, Bg->Rotation, Bg->Color,1,0.5f,1,1);

	}


}
//=============================================================================
// 頂点データ設定
//=============================================================================
void SetVertexLineStrip(int	NumVertex)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferLineStrip, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//一本目の直線の頂点をセット
	vertex[0].Position = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//二本目の直線の頂点をセット
	vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f + 50.0f, 0.0f);
	vertex[2].Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50.0f, 0.0f);
	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	GetDeviceContext()->Unmap(g_VertexBufferLineStrip, 0);
}
//===============================
//直線の頂点を格納
//in
//  開始座標X, 開始座標Y, 終了座標X, 終了座標Y
//
void	SetVertexLine(float StartX, float StartY, float EndX, float EndY,float kakudo)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferLine, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(StartX, StartY, 0.0f);
	vertex[0].Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(EndX, EndY, 0.0f);
	vertex[1].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//角度をラジアンに変更する
	float rad = D3DXToRadian(kakudo);
	float x, y;

	x = vertex[1].Position.x * cosf(rad);
	y = vertex[1].Position.x * sinf(rad);

	vertex[1].Position.x += x + StartX;
	vertex[1].Position.y += y + StartY;


	GetDeviceContext()->Unmap(g_VertexBufferLine, 0);//書き込み終了

}

//==============================
//ラインで多角形の表示
//in
//　表示座標X, 表示座標Y, 半径, 頂点数, 色
//
void	SetVertexCircle(float PosX, float PosY, float Rad, int NumVertex, D3DXCOLOR col)
{

	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferCircle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	float	kakudo = 0;
	for (int i = 0; i < NumVertex; i++)
	{
		vertex[i].Position.x = cosf(D3DXToRadian(kakudo)) * Rad + PosX;
		vertex[i].Position.y = sinf(D3DXToRadian(kakudo)) * Rad + PosY;
		vertex[i].Position.z = 0.0f;
		vertex[i].Diffuse = col;
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		kakudo += (360.0f / NumVertex);
	}
	//最後の頂点に最初の頂点をコピーして図形を閉じる
	vertex[NumVertex].Position = vertex[0].Position;
	vertex[NumVertex].Diffuse = vertex[0].Diffuse;
	vertex[NumVertex].TexCoord = vertex[0].TexCoord;

	GetDeviceContext()->Unmap(g_VertexBufferCircle, 0);//書き込み終了
}


//背景のセット
void SetBGTexture(char* name)
{
	//textureのロード
	g_textureNoBG = LoadTexture(name);
	if (g_textureNo == -1)
	{//ロードエラー
		exit(999);//強制終了
	}
}