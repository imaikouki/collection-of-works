//=============================================================================
//
// 敵の弾処理 [enemybullet.cpp]
// Author : Imai
//
//=============================================================================
#include "enemybullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ENEMYBULLET			"data/TEXTURE/enemybullet000.png"	// 読み込むテクスチャファイル名

//#define	ENEMYBULLET_SIZE_X			(50.0f)							// ビルボードの幅
//#define	ENEMYBULLET_SIZE_Y			(50.0f)							// ビルボードの高さ
#define	VALUE_MOVE_ENEMYBULLET		(2.0f)							// 移動速度

#define ENEMYBULLETMAXPOS			(2000)							//弾の動く範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyBullet(int nIdxEnemyBullet, float fSizeX, float fSizeY);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyBullet = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyBullet = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldEnemyBullet;				// ワールドマトリックス

ENEMYBULLET					g_aEnemyBullet[MAX_ENEMYBULLET];			// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexEnemyBullet(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_ENEMYBULLET,				// ファイルの名前
								&g_pD3DTextureEnemyBullet);	// 読み込むメモリー

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		g_aEnemyBullet[nCntEnemyBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEnemyBullet[nCntEnemyBullet].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEnemyBullet[nCntEnemyBullet].fSizeX = ENEMYBULLET_SIZE_X;
		g_aEnemyBullet[nCntEnemyBullet].fSizeY = ENEMYBULLET_SIZE_Y;
		g_aEnemyBullet[nCntEnemyBullet].nTimer = 0;
		g_aEnemyBullet[nCntEnemyBullet].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyBullet(void)
{
	if(g_pD3DTextureEnemyBullet != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemyBullet->Release();
		g_pD3DTextureEnemyBullet = NULL;
	}

	if(g_pD3DVtxBuffEnemyBullet != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEnemyBullet->Release();
		g_pD3DVtxBuffEnemyBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyBullet(void)
{
	// エネミーを取得
	ENEMY *enemy = GetEnemy();

	D3DXVECTOR3 rotCamera;


	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos.x += g_aEnemyBullet[nCntEnemyBullet].move.x;
			g_aEnemyBullet[nCntEnemyBullet].pos.z += g_aEnemyBullet[nCntEnemyBullet].move.z;

			g_aEnemyBullet[nCntEnemyBullet].nTimer--;
			if(g_aEnemyBullet[nCntEnemyBullet].nTimer <= 0)
			{
				/*DeleteShadow(g_aEnemyBullet[nCntEnemyBullet].nIdxShadow);
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;*/
			}
			else
			{
				//// 影の位置設定
				//SetPositionShadow(g_aEnemyBullet[nCntEnemyBullet].nIdxShadow, D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, 0.1f, g_aEnemyBullet[nCntEnemyBullet].pos.z));

				//// エフェクトの設定
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);
			}

			//if(g_aEnemyBullet[nCntEnemyBullet].pos.x < enemy->pos.x - ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.x > enemy->pos.x + ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.z < enemy->pos.z - ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.z > enemy->pos.z + ENEMYBULLETMAXPOS)
			//{
			//	g_aEnemyBullet[nCntEnemyBullet].bUse = false;

			//	//// 爆発の生成
			//	//SetExplosion(g_aEnemyBullet[nCntEnemyBullet].pos, 40.0f, 40.0f);

			//	//DeleteEnemyBullet(nCntEnemyBullet);

			//	//// SE再生
			//	//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			//}

			if(g_aEnemyBullet[nCntEnemyBullet].pos.x - ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.x + ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.z - ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.z + ENEMYBULLETMAXPOS)
			{
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;

			}

			float fSizeX = 8.0f + (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f) * 0.05f;
			if(fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f) * 0.05f;
			if(fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}

			float colA = (200.0f - (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEnemyBullet);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldEnemyBullet._11 = mtxView._11;
			g_mtxWorldEnemyBullet._12 = mtxView._21;
			g_mtxWorldEnemyBullet._13 = mtxView._31;
			g_mtxWorldEnemyBullet._21 = mtxView._12;
			g_mtxWorldEnemyBullet._22 = mtxView._22;
			g_mtxWorldEnemyBullet._23 = mtxView._32;
			g_mtxWorldEnemyBullet._31 = mtxView._13;
			g_mtxWorldEnemyBullet._32 = mtxView._23;
			g_mtxWorldEnemyBullet._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aEnemyBullet[nCntEnemyBullet].scale.x, g_aEnemyBullet[nCntEnemyBullet].scale.y, g_aEnemyBullet[nCntEnemyBullet].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemyBullet, &g_mtxWorldEnemyBullet, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemyBullet, &g_mtxWorldEnemyBullet, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemyBullet);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureEnemyBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEnemyBullet * 4), NUM_POLYGON);
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
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_ENEMYBULLET,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffEnemyBullet,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-ENEMYBULLET_SIZE_X / 2, -ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYBULLET_SIZE_X / 2, -ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-ENEMYBULLET_SIZE_X / 2, ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYBULLET_SIZE_X / 2, ENEMYBULLET_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemyBullet(int nIdxEnemyBullet, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyBullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxEnemyBullet = -1;

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(!g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos = pos;
			g_aEnemyBullet[nCntEnemyBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyBullet[nCntEnemyBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aEnemyBullet[nCntEnemyBullet].move = move;
			g_aEnemyBullet[nCntEnemyBullet].fSizeX = fSizeX;
			g_aEnemyBullet[nCntEnemyBullet].fSizeY = fSizeY;
			g_aEnemyBullet[nCntEnemyBullet].nTimer = nTimer;
			g_aEnemyBullet[nCntEnemyBullet].bUse = true;

			//// 影の設定
			//g_aEnemyBullet[nCntEnemyBullet].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// 影の設定

			// 頂点座標の設定
			SetVertexEnemyBullet(nCntEnemyBullet, fSizeX, fSizeY);

			nIdxEnemyBullet = nCntEnemyBullet;

			break;
		}
	}

	return nIdxEnemyBullet;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteEnemyBullet(int nIdxEnemyBullet)
{
	if(nIdxEnemyBullet >= 0 && nIdxEnemyBullet < MAX_ENEMYBULLET)
	{
		/*DeleteShadow(g_aEnemyBullet[nIdxEnemyBullet].nIdxShadow);*/
		g_aEnemyBullet[nIdxEnemyBullet].bUse = false;
	}
}

//=============================================================================
// エネミーの取得
//=============================================================================
ENEMYBULLET *GetEnemyBullet()
{
	return &(g_aEnemyBullet[0]);
}