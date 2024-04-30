//*********************************************************
// sprite.cpp
// 作成者：岸直哉　作成日2022/06/13
//*********************************************************

#include "renderer.h"
#include "sprite.h"


//=================================================
//マクロ定義
//=================================================
#define	NUM_VERTEX	(4)		//スプライトの頂点数


#define	BOX_W	(400)	//四角形の横のサイズ
#define	BOX_H	(400)	//四角形の縦のサイズ

//=================================================
//プロトタイプ宣言
//=================================================


//=================================================
//グローバル変数
//=================================================
static	ID3D11Buffer* g_VertexBufferTriangle = NULL;	//四角形用

//float	PositionX = SCREEN_WIDTH / 2;//画面中央座標
//float	PositionY = SCREEN_HEIGHT / 2;
//float	Kakudo = 0; //四角形の回転角度



//=================================================
//三角形用頂点格納処理
//=================================================
void DrawSpriteColorRotation(float PosX, float PosY, int Size_W, int Size_H, float Kakudo,D3DXCOLOR col, float PaternNo, float uv_w, float uv_h, int NumPatern)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	static	float offset = 0.0f;
	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-Size_W/2, -Size_H/2, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f+offset, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+Size_W/2, -Size_H/2, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f + offset, 0.0f);
	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-Size_W/2, +Size_H/2,0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f + offset, 1.0);
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+Size_W/2, +Size_H/2, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f + offset, 1.0f);
	//offset += 1.0f / 200.0f;


	//UVアニメーション
	//本当は引数で指定するパラメーター
	//static	float	PaternNo = 0;	//パターン番号
	//float	uv_w = 0.5f;			//横サイズ
	//float	uv_h = 0.5f;			//縦サイズ
	//int		NumPatern = 2;			//横枚数

	//UV座標の計算
	int no = PaternNo;	//パターン番号を整数値にする 小数点以下を捨てる
	float	u = (no % NumPatern) * uv_w;
	float	v = (no / NumPatern) * uv_h;

	//UV座標の書き換え
	vertex[0].TexCoord = D3DXVECTOR2(u, v);				//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(u + uv_w, v);		//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(u, v + uv_h);		//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(u + uv_w, v + uv_h);	//RIGHT-BOTTOM

	/*PaternNo += 0.005f;
	if (PaternNo >= 4.0f) { PaternNo -= 4.0f; }*/

	//度をラジアンへ変換する
	float	rad = D3DXToRadian(Kakudo);
	float	x, y;

	for (int i = 0; i < 4; i++)
	{
		//加法定理		
		x = vertex[i].Position.x * cosf(rad) - vertex[i].Position.y * sinf(rad);
		y = vertex[i].Position.y * cosf(rad) + vertex[i].Position.x * sinf(rad);

		vertex[i].Position.x = x + PosX;	//平行移動（中心をずらす）
		vertex[i].Position.y = y + PosY;
	}

	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了


	//描画設定
	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}

//=================================================
//フォトの描画専用処理 by舘崎
// PosX, PosY, Size_W, Size_H, col
// ↑元々そのレイヤーにあった情報
// os
// 今描画したい座標
//=================================================
void DrawSpritePhoto(float PosX, float PosY, int Size_W, int Size_H, D3DXCOLOR col, D3DXVECTOR2 pos)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	//頂点バッファへの書き込み許可をもらう
	GetDeviceContext()->Map(g_VertexBufferTriangle, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//頂点構造体の型にポインター型を変換をする
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//頂点 V0をセット
	vertex[0].Position = D3DXVECTOR3(-Size_W / 2, -Size_H / 2, 0.0f);
	vertex[0].Diffuse = col;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//頂点 V1をセット
	vertex[1].Position = D3DXVECTOR3(+Size_W / 2, -Size_H / 2, 0.0f);
	vertex[1].Diffuse = col;
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	//頂点 V2をセット
	vertex[2].Position = D3DXVECTOR3(-Size_W / 2, +Size_H / 2, 0.0f);
	vertex[2].Diffuse = col;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0);
	//頂点 V3をセット
	vertex[3].Position = D3DXVECTOR3(+Size_W / 2, +Size_H / 2, 0.0f);
	vertex[3].Diffuse = col;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	//offset += 1.0f / 200.0f;

	//引数でもらってきたPosとSizeを元にTexCoordを計算する
	float LineLeft = (PosX - (Size_W / 2)) / SCREEN_WIDTH;
	float LineRight = (PosX + (Size_W / 2)) / SCREEN_WIDTH;
	float LineTop = (PosY - (Size_H / 2)) / SCREEN_HEIGHT;
	float LineBottom = (PosY + (Size_H / 2)) / SCREEN_HEIGHT;



	//UV座標の書き換え
	vertex[0].TexCoord = D3DXVECTOR2(LineLeft, LineTop);//LEFT-TOP
	vertex[1].TexCoord = D3DXVECTOR2(LineRight, LineTop);//RIGHT-TOP
	vertex[2].TexCoord = D3DXVECTOR2(LineLeft, LineBottom);//LEFT-BOTTOM
	vertex[3].TexCoord = D3DXVECTOR2(LineRight, LineBottom);//RIGHT-BOTTOM


	for (int i = 0; i < 4; i++)
	{
		vertex[i].Position.x += pos.x;	//平行移動（中心をずらす）
		vertex[i].Position.y += pos.y;
	}
	GetDeviceContext()->Unmap(g_VertexBufferTriangle, 0);//書き込み終了


	//描画設定
	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);

	{
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferTriangle, &stride, &offset);
		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	// ポリゴン描画
	GetDeviceContext()->Draw(NUM_VERTEX, 0);
}
//*********************************************************
//初期化処理
//*********************************************************

void InitSprite()
{
	{//三角形用の頂点初期化処理
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * NUM_VERTEX;//頂点1個＊頂点数のサイズで作る
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferTriangle);
		//三角形用頂点格納処理
		//SetVertexTringle(PositionX, PositionY, BOX_W, BOX_H, 0);
	}
}
//*********************************************************
//終了処理
//*********************************************************

void UninitSprite()
{
	if (g_VertexBufferTriangle)
	{
		g_VertexBufferTriangle->Release();//使い終わったので解放する
		g_VertexBufferTriangle = NULL;
	}
}


//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ー
