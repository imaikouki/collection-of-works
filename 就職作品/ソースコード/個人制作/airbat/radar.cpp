//=============================================================================
//
// レーダー処理 [radar.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "radar.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRadar(void);
void SetVertexBou(void);
void SetTextureRadar(void);
void SetVertexRadr(void);

static RADAR radar;
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRadar = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRadarBou = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkRadar[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkRadarBou[NUM_VERTEX];		// 頂点情報格納ワーク
int radarbgmcnt = 0;

#define RADARBOU_SIZE_X		(90.0f)		//レーダー棒のサイズ		
#define RADARBOU_SIZE_Y		(90.0f)		//レーダー棒のサイズ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRadar(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	radar.pos = D3DXVECTOR3(SCREEN_WIDTH- RADARBOU_SIZE_X/2, SCREEN_HEIGHT - RADARBOU_SIZE_X/2, 0.0f);
	radar.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 temp = D3DXVECTOR2(90.0f, 90.0f);
	radar.Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
	radar.BaseAngle = atan2f(90.0f, 90.0f);	// エネミーの角度を初期化
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RADAR,				// ファイルの名前
			&g_pD3DTextureRadar);		// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RADAR_LOGO,			// ファイルの名前
			&g_pD3DTextureRadarBou);	// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexRadar();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRadar(void)
{
	if (g_pD3DTextureRadar != NULL)
	{// テクスチャの開放
		g_pD3DTextureRadar->Release();
		g_pD3DTextureRadar = NULL;
	}

	if (g_pD3DTextureRadarBou != NULL)
	{// テクスチャの開放
		g_pD3DTextureRadarBou->Release();
		g_pD3DTextureRadarBou = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRadar(void)
{
	radar.rot.z += 0.01f;
	SetVertexRadr();						// 移動後の座標で頂点を設定
	//// テクスチャ座標を設定
	//SetTextureRadar();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRadar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRadar);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRadar, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRadarBou);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRadarBou, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRadar(void)
{

	// 頂点座標の設定
	g_vertexWkRadar[0].vtx = D3DXVECTOR3(SCREEN_WIDTH-90.0f,SCREEN_HEIGHT - 90.0f, 0.0f);
	g_vertexWkRadar[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 90.0f, 0.0f);
	g_vertexWkRadar[2].vtx = D3DXVECTOR3(SCREEN_WIDTH-90.0f, SCREEN_HEIGHT, 0.0f);
	g_vertexWkRadar[3].vtx = D3DXVECTOR3(SCREEN_WIDTH ,SCREEN_HEIGHT, 0.0f);


	// テクスチャのパースペクティブコレクト用
	g_vertexWkRadar[0].rhw =
		g_vertexWkRadar[1].rhw =
		g_vertexWkRadar[2].rhw =
		g_vertexWkRadar[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRadar[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkRadar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRadar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRadar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRadar[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	//SetVertexRadr();

	// 頂点座標の設定
	g_vertexWkRadarBou[0].vtx = D3DXVECTOR3(radar.pos.x- RADARBOU_SIZE_X/2.0f, radar.pos.y - RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[1].vtx = D3DXVECTOR3(radar.pos.x+ RADARBOU_SIZE_X/2.0f, radar.pos.y - RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[2].vtx = D3DXVECTOR3(radar.pos.x - RADARBOU_SIZE_X/2.0f, radar.pos.y + RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[3].vtx = D3DXVECTOR3(radar.pos.x + RADARBOU_SIZE_X/2.0f, radar.pos.x + RADARBOU_SIZE_Y/2.0f, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkRadarBou[0].rhw =
		g_vertexWkRadarBou[1].rhw =
		g_vertexWkRadarBou[2].rhw =
		g_vertexWkRadarBou[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRadarBou[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkRadarBou[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRadarBou[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRadarBou[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRadarBou[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRadar(void)
{

		//// テクスチャ座標の設定
		//int x = 0;
		//int y = 0;
		//float sizeX = 1.0f;
		//float sizeY = 1.0f;

		//g_vertexWkRadarBou[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		//g_vertexWkRadarBou[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		//g_vertexWkRadarBou[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		//g_vertexWkRadarBou[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRadr(void)
{
	// 頂点座標の設定
	g_vertexWkRadarBou[0].vtx.x = radar.pos.x - cosf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[0].vtx.y = radar.pos.y - sinf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[0].vtx.z = 0.0f;

	g_vertexWkRadarBou[1].vtx.x = radar.pos.x + cosf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[1].vtx.y = radar.pos.y - sinf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[1].vtx.z = 0.0f;

	g_vertexWkRadarBou[2].vtx.x = radar.pos.x - cosf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[2].vtx.y = radar.pos.y + sinf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[2].vtx.z = 0.0f;

	g_vertexWkRadarBou[3].vtx.x = radar.pos.x + cosf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[3].vtx.y = radar.pos.y + sinf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[3].vtx.z = 0.0f;

	// 頂点座標の設定
	//g_vertexWkRadar[0].vtx.x = 0.0f;
	//g_vertexWkRadar[0].vtx.y = 0.0f;
	//g_vertexWkRadar[0].vtx.z = 0.0f;

	//g_vertexWkRadar[1].vtx.x = 0.0f+100.0f;
	//g_vertexWkRadar[1].vtx.y = 0.0f;
	//g_vertexWkRadar[1].vtx.z = 0.0f;

	//g_vertexWkRadar[2].vtx.x = 0.0f;
	//g_vertexWkRadar[2].vtx.y = 0.0f+100.0f;
	//g_vertexWkRadar[2].vtx.z = 0.0f;

	//g_vertexWkRadar[3].vtx.x = 0.0f+100.0f;
	//g_vertexWkRadar[3].vtx.y = 0.0f+100.0f;
	//g_vertexWkRadar[3].vtx.z = 0.0f;

}

