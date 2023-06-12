//=============================================================================
//
// エネミーモデル処理 [aircraftcarrier.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAX_AIRCRAFTCARRIER		(1)					// エネミーの数

#define AIRCRAFTCARRIER_SIZE_X       (150.0f)				//エネミーの大きさ
#define AIRCRAFTCARRIER_SIZE_Y       (150.0f)				//エネミーの大きさ
#define AIRCRAFTCARRIER_SIZE_Z       (150.0f)				//エネミーの大きさ

struct AIRCRAFTCARRIER
{
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			rot;				// モデルの向き(回転)
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			move;				// モデルの移動量

	LPDIRECT3DTEXTURE9	pD3DTexture;		// テクスチャへのポインタ
	LPD3DXMESH			pD3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER		pD3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD				nNumMat;			// マテリアル情報の数

	D3DXMATRIX			mtxWorld;			// ワールドマトリックス

	bool				use;				//使用中かどうか
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitAircraftCarrier(void);
void UninitAircraftCarrier(void);
void UpdateAircraftCarrier(void);
void DrawAircraftCarrier(void);

AIRCRAFTCARRIER *GetAircraftCarrier();