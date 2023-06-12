//=============================================================================
//
// コックピット処理 [cockpit.cpp]
// Author : Imai
//
//=============================================================================
#include "cockpit.h"
#include "fade.h"
#include "camera.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FRAME_COCKPIT	"data/TEXTURE/cockpit.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME_COCKPIT2	"data/TEXTURE/rokku.png"	// 読み込むテクスチャファイル名

#define	COCKPIT_SIZE_X		(35.0f)							// タイマーの数字の幅
#define	COCKPIT_SIZE_Y		(50.0f)							// タイマーの数字の高さ
#define	COCKPIT_INTERVAL_X	(0.0f)							// タイマーの数字の表示間隔

#define	NUM_PLACE			(3)			// タイマーの桁数

#define	COCKPIT_POS_X			(SCREEN_WIDTH / 2 - ((COCKPIT_SIZE_X * NUM_PLACE + COCKPIT_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// タイマーの表示基準位置Ｘ座標
#define	COCKPIT_POS_Y			(25.0f)																						// タイマーの表示基準位置Ｙ座標

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice);
void SetTextureCockpit(int idx, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit[2] = {};		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit2[2] = {};		// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit2 = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				g_posCockpit;
D3DXVECTOR3				g_rotCockpit;

int						g_nCockpit;						// コックピット
bool					g_bEnableCockpit;					// コックピット動作ON/OFF

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCockpit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posCockpit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCockpit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// コックピットの初期化
	g_nCockpit = 30 * 60;
	g_bEnableCockpit = true;

	// 頂点情報の作成
	MakeVertexCockpit(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FRAME_COCKPIT,			// ファイルの名前
								&g_pD3DTextureCockpit[0]);	// 読み込むメモリー

// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FRAME_COCKPIT2,			// ファイルの名前
								&g_pD3DTextureCockpit2[0]);	// 読み込むメモリー	
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCockpit(void)
{
	if(g_pD3DTextureCockpit[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureCockpit[0]->Release();
		g_pD3DTextureCockpit[0] = NULL;
	}
	if(g_pD3DTextureCockpit[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureCockpit[1]->Release();
		g_pD3DTextureCockpit[1] = NULL;
	}

	if (g_pD3DTextureCockpit2[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureCockpit2[0]->Release();
		g_pD3DTextureCockpit2[0] = NULL;
	}
	if (g_pD3DTextureCockpit2[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureCockpit2[1]->Release();
		g_pD3DTextureCockpit2[1] = NULL;
	}

	if(g_pD3DVtxBuffCockpit != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffCockpit->Release();
		g_pD3DVtxBuffCockpit = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCockpit(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCockpit(void)
{
	CAMERA*camera = GetCamera();

	if (camera->fpsmode == true)
	{
		if (GetKeyboardPress(DIK_G)==true || !IsButtonPressed(0, BUTTON_CROSS_UP)==true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureCockpit[0]);

			// ポリゴンの描画
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
			}

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureCockpit[1]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
		}
	}
	else 
	{
		if (GetKeyboardPress(DIK_G) == true || !IsButtonPressed(0, BUTTON_CROSS_UP) == true)
		{



			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit2, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureCockpit2[0]);

			// ポリゴンの描画
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
			}

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureCockpit2[1]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
												FVF_VERTEX_2D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffCockpit,							// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// rhwの設定
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffCockpit->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffCockpit2,							// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffCockpit2->Lock(0, 0, (void**)&pVtx, 0);

		//// 頂点座標の設定
		//pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		//pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		//pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

				// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2- 50, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH/2+ 50, SCREEN_HEIGHT/2- 50, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(SCREEN_WIDTH/2- 50, SCREEN_HEIGHT/2+ 50, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH/2+ 50, SCREEN_HEIGHT/2+ 50, 0.0f);


		// rhwの設定
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffCockpit2->Unlock();
	}


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureCockpit(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffCockpit2->Unlock();

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffCockpit2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffCockpit2->Unlock();

}
