//=============================================================================
//
// エネミーモデル処理 [enemy.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "enemy.h"
#include "shadow.h"
#include "game.h"
#include "enemybullet.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_BALLOON			"data/MODEL/husen.x"			// 読み込むモデル名

#define	VALUE_MOVE			(5.0f)							// 移動量
#define	VALUE_ROTATE		(D3DX_PI * 0.02f)				// 回転量
#define	VALUE_MOVE_BULLET	(20.5f)							// 弾の移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

static ENEMY				g_Enemy[MAX_ENEMY];				// エネミー

float move_time = 0;										//往復の時間

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ランダム用初期設定 */
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].use = true;			// 使う

		// 位置・回転・スケールの初期設定
		g_Enemy[i].randx = rand() % 10000;
		g_Enemy[i].randy = rand() % 5000;
		g_Enemy[i].randz = rand() % 10000;		g_Enemy[i].randz = rand() % 7000;
		g_Enemy[i].pos = D3DXVECTOR3((FLOAT)g_Enemy[i].randx, (FLOAT)g_Enemy[i].randy, (FLOAT)g_Enemy[i].randz);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_Enemy[i].scl = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

		g_Enemy[i].move = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

		g_Enemy[i].pD3DTexture = NULL;
		g_Enemy[i].pD3DXMesh = NULL;
		g_Enemy[i].pD3DXBuffMat = NULL;
		g_Enemy[i].nNumMat = 0;
		g_Enemy[i].life = 10;
		g_Enemy[i].recnt = 0;
		g_Enemy[i].posplus = 0.0f;
		g_Enemy[i].pospluscnt = 0;
		g_Enemy[i].posplususe = true;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(MODEL_BALLOON,					// 読み込むモデルファイル名(Xファイル)
			D3DXMESH_SYSTEMMEM,			// メッシュの作成オプションを指定
			pDevice,					// IDirect3DDevice9インターフェイスへのポインタ
			NULL,						// 隣接性データを含むバッファへのポインタ
			&g_Enemy[i].pD3DXBuffMat,	// マテリアルデータを含むバッファへのポインタ
			NULL,						// エフェクトインスタンスの配列を含むバッファへのポインタ
			&g_Enemy[i].nNumMat,		// D3DXMATERIAL構造体の数
			&g_Enemy[i].pD3DXMesh)))	// ID3DXMeshインターフェイスへのポインタのアドレス
		{
			return E_FAIL;
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			TEXTURE_FILENAME,				// ファイルの名前
			&g_Enemy[i].pD3DTexture);		// 読み込むメモリー
#endif

		//// 影の初期化
		//D3DXVECTOR3 pos = g_Enemy[i].pos;
		//pos.y = 0.0f;
		//g_Enemy[i].shadowIdx = CreateShadow(pos, g_Enemy[i].scl);

		//g_Enemy[i].tbl_adr = NULL;
		//g_Enemy[i].tbl_cnt = 0;
		//g_Enemy[i].move_time = 0.0f;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].pD3DTexture != NULL)
		{// テクスチャの開放
			g_Enemy[i].pD3DTexture->Release();
			g_Enemy[i].pD3DTexture = NULL;
		}

		if (g_Enemy[i].pD3DXMesh != NULL)
		{// メッシュの開放
			g_Enemy[i].pD3DXMesh->Release();
			g_Enemy[i].pD3DXMesh = NULL;
		}

		if (g_Enemy[i].pD3DXBuffMat != NULL)
		{// マテリアルの開放
			g_Enemy[i].pD3DXBuffMat->Release();
			g_Enemy[i].pD3DXBuffMat = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER*player = GetPlayer();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// 使われているなら処理する
		if (g_Enemy[i].use == true)
		{

			// ０番だけプレイヤーをホーミングするようにしてみる
			D3DXVECTOR3 pos = GetPlayer()->pos - g_Enemy[i].pos;
			float rot = atan2f(pos.z,pos.x);


			g_Enemy[i].rot.y = atan2f(pos.z, pos.x) - D3DX_PI / 2.0f;

			//D3DXVECTOR3 leng = player->pos - g_Enemy->pos;

			float vleng = D3DXVec3Length(&D3DXVECTOR3(player->pos - g_Enemy->pos));
			
			
				if (g_Enemy[i].posplususe == true)
				{
					g_Enemy[i].posplus += 0.02f;
					g_Enemy[i].pospluscnt += 1;

					if (g_Enemy[i].pospluscnt > 100)
					{
						g_Enemy[i].pospluscnt = 0;
						g_Enemy[i].posplus = 0.0f;
						g_Enemy[i].posplususe = false;
					}
				}
				else if(g_Enemy[i].posplususe == false)
				{
					g_Enemy[i].posplus -= 0.02f;
					g_Enemy[i].pospluscnt += 1;

					if (g_Enemy[i].pospluscnt > 100)
					{
						g_Enemy[i].pospluscnt = 0;
						g_Enemy[i].posplus = 0.0f;
						g_Enemy[i].posplususe = true;
					}
				}
			

			g_Enemy[i].pos.y += g_Enemy[i].posplus;

			//if (0.0f <= vleng < 20.0f && 0.0f > vleng > 20.0f)
			//{
			//	g_Enemy[i].pos.x += cosf(rot) * g_Enemy[i].move.x+pos.x/5000;
			//	g_Enemy[i].pos.y += cosf(rot) * g_Enemy[i].move.y+pos.y/5000;
			//	g_Enemy[i].pos.z += sinf(rot) * g_Enemy[i].move.z+pos.z/5000;
			//}

			//// 弾発射
			//if (GetKeyboardPress(DIK_SPACE) || IsButtonPressed(0, BUTTON_R2) || IsMouseRightPressed())
			//{
			//	D3DXVECTOR3 pos;
			//	D3DXVECTOR3 move;

			//	pos.x = g_Enemy[i].pos.x - sinf(g_Enemy[i].rot.y) * 10.0f;
			//	pos.y = g_Enemy[i].pos.y;
			//	pos.z = g_Enemy[i].pos.z - cosf(g_Enemy[i].rot.y) * 10.0f;

			//	move.x = -sinf(g_Enemy[i].rot.y) * VALUE_MOVE_BULLET;
			//	move.y = 0.0f;
			//	move.z = -cosf(g_Enemy[i].rot.y) * VALUE_MOVE_BULLET;

			//	SetEnemyBullet(pos, move, 4.0f, 4.0f, 60 * 4);
			//}

		}
		else
		{
			if (g_Enemy[i].recnt < 0)
			{
				g_Enemy[i].recnt--;
			}
			else
			{
				g_Enemy[i].randx = rand() % 10000;
				g_Enemy[i].randy = rand() % 5000;
				g_Enemy[i].randz = rand() % 10000;

				g_Enemy[i].use = true;
				g_Enemy[i].pos = D3DXVECTOR3((FLOAT)g_Enemy[i].randx, 100, (FLOAT)g_Enemy[i].randz);
				g_Enemy[i].life = 10;

			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// 使われているなら処理する
		if (g_Enemy[i].use == true)
		{
			// 使われていないのならコンティニューする
			if(g_Enemy[i].use == false) continue;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[i].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_Enemy[i].pD3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_Enemy[i].pD3DTexture);

				// 描画
				g_Enemy[i].pD3DXMesh->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=============================================================================
// エネミーの取得
//=============================================================================
ENEMY *GetEnemy()
{
	return &(g_Enemy[0]);
}
