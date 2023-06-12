//=============================================================================
//
// ミサイル処理 [missile.cpp]
// Author : Imai
//
//=============================================================================
#include "missile.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_MISSILE			"data/TEXTURE/missile000.png"	// 読み込むテクスチャファイル名
#define	MISSILE_SIZE_X			(50.0f)							// ビルボードの幅
#define	MISSILE_SIZE_Y			(50.0f)							// ビルボードの高さ
#define	VALUE_MOVE_MISSILE		(2.0f)							// 移動速度
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMissile(LPDIRECT3DDEVICE9 pDevice);
void SetVertexMissile(int nIdxMissile, float fSizeX, float fSizeY);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMissile = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMissile = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldMissile;				// ワールドマトリックス

MISSILE					g_aMissile[MAX_MISSILE];			// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexMissile(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_MISSILE,				// ファイルの名前
								&g_pD3DTextureMissile);	// 読み込むメモリー

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		g_aMissile[nCntMissile].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aMissile[nCntMissile].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aMissile[nCntMissile].fSizeX = MISSILE_SIZE_X;
		g_aMissile[nCntMissile].fSizeY = MISSILE_SIZE_Y;
		g_aMissile[nCntMissile].nTimer = 0;
		g_aMissile[nCntMissile].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMissile(void)
{
	if(g_pD3DTextureMissile != NULL)
	{// テクスチャの開放
		g_pD3DTextureMissile->Release();
		g_pD3DTextureMissile = NULL;
	}

	if(g_pD3DVtxBuffMissile != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffMissile->Release();
		g_pD3DVtxBuffMissile = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMissile(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	D3DXVECTOR3 posPlayer;
	// モデルの位置取得
	posPlayer = GetPositionPlayer();

	// プレイヤーを取得
	pPlayer = GetPlayer();

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(g_aMissile[nCntMissile].bUse==true)
		{
			g_aMissile[nCntMissile].pos.x += g_aMissile[nCntMissile].move.x;
			g_aMissile[nCntMissile].pos.y += g_aMissile[nCntMissile].move.y;
			g_aMissile[nCntMissile].pos.z += g_aMissile[nCntMissile].move.z;

			g_aMissile[nCntMissile].nTimer--;
			if(g_aMissile[nCntMissile].nTimer <= 0)
			{
				/*DeleteShadow(g_aMissile[nCntMissile].nIdxShadow);
				g_aMissile[nCntMissile].bUse = false;*/
			}
			else
			{
				//// 影の位置設定
				//SetPositionShadow(g_aMissile[nCntMissile].nIdxShadow, D3DXVECTOR3(g_aMissile[nCntMissile].pos.x, 0.1f, g_aMissile[nCntMissile].pos.z));

				// エフェクトの設定
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
			}
			
			if(g_aMissile[nCntMissile].pos.x < posPlayer.x - 10000.0f
			|| g_aMissile[nCntMissile].pos.x > posPlayer.x + 10000.0f
			|| g_aMissile[nCntMissile].pos.y < posPlayer.y - 10000.0f
			|| g_aMissile[nCntMissile].pos.y > posPlayer.y + 10000.0f
			|| g_aMissile[nCntMissile].pos.z < posPlayer.z - 10000.0f
			|| g_aMissile[nCntMissile].pos.z > posPlayer.z + 10000.0f)
			{
				g_aMissile[nCntMissile].bUse = false;

				//// 爆発の生成
				//SetExplosion(g_aMissile[nCntMissile].pos, 40.0f, 40.0f);

				DeleteMissile(nCntMissile);

				//// SE再生
				//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}

			float fSizeX = 8.0f + (g_aMissile[nCntMissile].pos.y - 4.0f) * 0.05f;
			if(fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aMissile[nCntMissile].pos.y - 4.0f) * 0.05f;
			if(fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}

			/*SetVertexShadow(g_aMissile[nCntMissile].nIdxShadow, fSizeX, fSizeY);*/

			float colA = (200.0f - (g_aMissile[nCntMissile].pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
		/*	SetColorShadow(g_aMissile[nCntMissile].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));*/
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(g_aMissile[nCntMissile].bUse==true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldMissile);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldMissile._11 = mtxView._11;
			g_mtxWorldMissile._12 = mtxView._21;
			g_mtxWorldMissile._13 = mtxView._31;
			g_mtxWorldMissile._21 = mtxView._12;
			g_mtxWorldMissile._22 = mtxView._22;
			g_mtxWorldMissile._23 = mtxView._32;
			g_mtxWorldMissile._31 = mtxView._13;
			g_mtxWorldMissile._32 = mtxView._23;
			g_mtxWorldMissile._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aMissile[nCntMissile].scale.x, g_aMissile[nCntMissile].scale.y, g_aMissile[nCntMissile].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldMissile, &g_mtxWorldMissile, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aMissile[nCntMissile].pos.x, g_aMissile[nCntMissile].pos.y, g_aMissile[nCntMissile].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldMissile, &g_mtxWorldMissile, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMissile);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMissile, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMissile);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntMissile * 4), NUM_POLYGON);
		}
	}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexMissile(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_MISSILE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffMissile,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMissile->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-MISSILE_SIZE_X / 2, -MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(MISSILE_SIZE_X / 2, -MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-MISSILE_SIZE_X / 2, MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(MISSILE_SIZE_X / 2, MISSILE_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffMissile->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexMissile(int nIdxMissile, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMissile->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxMissile * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffMissile->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxMissile = -1;

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(!g_aMissile[nCntMissile].bUse)
		{
			g_aMissile[nCntMissile].pos = pos;
			g_aMissile[nCntMissile].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aMissile[nCntMissile].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aMissile[nCntMissile].move = move;
			g_aMissile[nCntMissile].fSizeX = fSizeX;
			g_aMissile[nCntMissile].fSizeY = fSizeY;
			g_aMissile[nCntMissile].nTimer = nTimer;
			g_aMissile[nCntMissile].bUse = true;

			//// 影の設定
			//g_aMissile[nCntMissile].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// 影の設定

			// 頂点座標の設定
			SetVertexMissile(nCntMissile, fSizeX, fSizeY);

			nIdxMissile = nCntMissile;

			break;
		}
	}

	return nIdxMissile;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteMissile(int nIdxMissile)
{
	if(nIdxMissile >= 0 && nIdxMissile < MAX_MISSILE)
	{
		/*DeleteShadow(g_aMissile[nIdxMissile].nIdxShadow);*/
		g_aMissile[nIdxMissile].bUse = false;
	}
}

//=============================================================================
// エネミーの取得
//=============================================================================
MISSILE *GetMissile()
{
	return &(g_aMissile[0]);
}
