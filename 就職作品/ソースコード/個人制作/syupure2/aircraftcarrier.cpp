//=============================================================================
//
// エネミーモデル処理 [aircraftcarrier.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "aircraftcarrier.h"
#include "shadow.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define	MODEL_AIRCRAFTCARRIER			"data/MODEL/airplane000.x"			// 読み込むモデル名
#define	MODEL_AIRCRAFTCARRIER	"data/MODEL/aircraftcarrier.x"		// 読み込むモデル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static AIRCRAFTCARRIER				g_AircraftCarrier[MAX_AIRCRAFTCARRIER];				// 空母

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitAircraftCarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ランダム用初期設定 */
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		g_AircraftCarrier[i].use = true;			// 使う

		// 位置・回転・スケールの初期設定
		g_AircraftCarrier[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_AircraftCarrier[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_AircraftCarrier[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		g_AircraftCarrier[i].move = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

		g_AircraftCarrier[i].pD3DTexture = NULL;
		g_AircraftCarrier[i].pD3DXMesh = NULL;
		g_AircraftCarrier[i].pD3DXBuffMat = NULL;
		g_AircraftCarrier[i].nNumMat = 0;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL_AIRCRAFTCARRIER,					// 読み込むモデルファイル名(Xファイル)
			D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
			pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
			NULL,						// 隣接性データを含むバッファへのポインタ
			&g_AircraftCarrier[i].pD3DXBuffMat,	// マテリアルデータを含むバッファへのポインタ
			NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
			&g_AircraftCarrier[i].nNumMat,		// D3DXMATERIAL構造体の数
			&g_AircraftCarrier[i].pD3DXMesh)))	// ID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_FILENAME,				// ファイルの名前
			&g_AircraftCarrier[i].pD3DTexture);		// 読み込むメモリー
#endif

		//// 影の初期化
		//D3DXVECTOR3 pos = g_AircraftCarrier[i].pos;
		//pos.y = 0.0f;
		//g_AircraftCarrier[i].shadowIdx = CreateShadow(pos, g_AircraftCarrier[i].scl);

		//g_AircraftCarrier[i].tbl_adr = NULL;
		//g_AircraftCarrier[i].tbl_cnt = 0;
		//g_AircraftCarrier[i].move_time = 0.0f;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAircraftCarrier(void)
{

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		if (g_AircraftCarrier[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_AircraftCarrier[i].pD3DTexture->Release();
			g_AircraftCarrier[i].pD3DTexture = NULL;
		}

		if (g_AircraftCarrier[i].pD3DXMesh != NULL)
		{// メッシュの開放
			g_AircraftCarrier[i].pD3DXMesh->Release();
			g_AircraftCarrier[i].pD3DXMesh = NULL;
		}

		if (g_AircraftCarrier[i].pD3DXBuffMat != NULL)
		{// マテリアルの開放
			g_AircraftCarrier[i].pD3DXBuffMat->Release();
			g_AircraftCarrier[i].pD3DXBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAircraftCarrier(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAircraftCarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		// 使われているなら処理する
		if (g_AircraftCarrier[i].use == true)
		{
			// 使われていないのならコンティニューする
			if(g_AircraftCarrier[i].use == false) continue;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_AircraftCarrier[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_AircraftCarrier[i].scl.x, g_AircraftCarrier[i].scl.y, g_AircraftCarrier[i].scl.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_AircraftCarrier[i].rot.y, g_AircraftCarrier[i].rot.x, g_AircraftCarrier[i].rot.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_AircraftCarrier[i].pos.x, g_AircraftCarrier[i].pos.y, g_AircraftCarrier[i].pos.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_AircraftCarrier[i].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_AircraftCarrier[i].pD3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_AircraftCarrier[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_AircraftCarrier[i].pD3DTexture);

				// 描画
				g_AircraftCarrier[i].pD3DXMesh->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=============================================================================
// エネミーの取得
//=============================================================================
AIRCRAFTCARRIER *GetAircraftCarrier()
{
	return &(g_AircraftCarrier[0]);
}
