//=============================================================================
//
// レーダー敵処理 [enemy.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "radarenemy.h"
#include "player.h"
#include "enemybullet.h"
#include "enemy.h"
#include "radar.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRadarEnemy( int no );
void SetTextureRadarEnemy( int no, int cntPattern );
void SetVertexRadarEnemy( int no );
int e_pos = 30;
//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureRadarEnemy = NULL;		// テクスチャへのポリゴン

static RADARENEMY					g_RadarEnemy[MAX_ENEMY];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRadarEnemy(int type)
{

		LPDIRECT3DDEVICE9	pDevice = GetDevice();

		// テクスチャーの初期化を行う？
		if (type == 0)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,						// デバイスのポインタ
				RADARENEMY_TEXTURE,										// ファイルの名前
				&g_pD3DTextureRadarEnemy);								// 読み込むメモリのポインタ
		}


		// エネミーの初期化処理
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			g_RadarEnemy[i].use = true;										// 使用
			g_RadarEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
			g_RadarEnemy[i].ppos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 座標データを初期化
			g_RadarEnemy[i].vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 座標データを初期化
			g_RadarEnemy[i].distance = 0.0f;
			g_RadarEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
			g_RadarEnemy[i].PatternAnim = 0;									// アニメパターン番号をランダムで初期化
			g_RadarEnemy[i].CountAnim = 0;									// アニメカウントを初期化

			D3DXVECTOR2 temp = D3DXVECTOR2(RADARENEMY_TEXTURE_SIZE_X, RADARENEMY_TEXTURE_SIZE_Y);
			g_RadarEnemy[i].Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
			g_RadarEnemy[i].BaseAngle = atan2f(RADARENEMY_TEXTURE_SIZE_Y, RADARENEMY_TEXTURE_SIZE_X);	// エネミーの角度を初期化
			g_RadarEnemy[i].Texture = g_pD3DTextureRadarEnemy;
			MakeVertexRadarEnemy(i);											// 頂点情報の作成
		}
	

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRadarEnemy(void)
{
		if (g_pD3DTextureRadarEnemy != NULL)
		{	// テクスチャの開放
			g_pD3DTextureRadarEnemy->Release();
			g_pD3DTextureRadarEnemy = NULL;
		}
	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRadarEnemy(void)
{

	ENEMY*enemy = GetEnemy();		// エネミーのポインターを初期化
	PLAYER*player = GetPlayer();	//プレイヤーのポインターを初期化

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//プレイヤーと敵の位置を計算
		g_RadarEnemy[i].ppos = (player->pos - enemy[i].pos) / 300;
		//g_RadarEnemy[i].vec = Transform(D3DXVECTOR3(g_RadarEnemy[i].ppos.x,0.0f,g_RadarEnemy[i].ppos.z), player->quorot);
		g_RadarEnemy[i].vec = Transform(D3DXVECTOR3(g_RadarEnemy[i].ppos.x, g_RadarEnemy[i].ppos.y, g_RadarEnemy[i].ppos.z), player->quorot);
		g_RadarEnemy[i].distance = D3DXVec2Length(&D3DXVECTOR2(g_RadarEnemy[i].ppos.x, g_RadarEnemy[i].ppos.z));

			//if (g_RadarEnemy[i]. distance <= 25.0f)
			{
				if (enemy[i].use == true)
				{
					g_RadarEnemy[i].pos.x = g_RadarEnemy[i].vec.x;
					g_RadarEnemy[i].pos.y = g_RadarEnemy[i].vec.z;
					g_RadarEnemy[i].pos.z = g_RadarEnemy[i].vec.y;

					SetVertexRadarEnemy(i);							// 移動後の座標で頂点を設定
				}
			}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRadarEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_RadarEnemy[i].distance <= 35.0f)
		{
			if (g_RadarEnemy[i].use == true)			// 使用している状態なら描画する
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_RadarEnemy[i].Texture);

				// ポリゴンの描画
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_RadarEnemy[i].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRadarEnemy( int i )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		// 頂点座標の設定
		SetVertexRadarEnemy(i);

		// rhwの設定
		g_RadarEnemy[i].vertexWk[0].rhw =
			g_RadarEnemy[i].vertexWk[1].rhw =
			g_RadarEnemy[i].vertexWk[2].rhw =
			g_RadarEnemy[i].vertexWk[3].rhw = 1.0f;

			g_RadarEnemy[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		g_RadarEnemy[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_RadarEnemy[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_RadarEnemy[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y);
		g_RadarEnemy[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X, 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRadarEnemy( int i, int cntPattern )
{
		// テクスチャ座標の設定
		int x = cntPattern % RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		int y = cntPattern / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y;

		g_RadarEnemy[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_RadarEnemy[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		g_RadarEnemy[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		g_RadarEnemy[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRadarEnemy( int i )
{
	// 頂点座標の設定
	g_RadarEnemy[i].vertexWk[0].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x - RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y - RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[1].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x + RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y - RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[2].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x - RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y + RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[3].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x + RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y + RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
}


