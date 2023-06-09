//=============================================================================
//
// スコア処理 [score.cpp]
//
//=============================================================================
#include "main.h"
#include "score.h"
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;			// テクスチャへのポリゴン
static VERTEX_2D				g_vertexWk[SCORE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

static D3DXVECTOR3				g_posScore;						// ポリゴンの移動量

static int						g_Score;						// スコア

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_SCORE,					// ファイルの名前
			&g_pD3DTexture);					// 読み込むメモリのポインタ
	}

	g_posScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	g_Score = 0;

	// 頂点情報の作成
	MakeVertexScore();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if( g_pD3DTexture != NULL )
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	// 毎フレーム実行される処理を記述する


	SetTextureScore();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

	// テクスチャの設定
	pDevice->SetTexture( 0, g_pD3DTexture );

	// スコア
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, &g_vertexWk[i][0], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(void)
{
	int i;
	float habaX = TEXTURE_SCORE_SIZE_X;	// 数字の横幅
	
	// 桁数分処理する
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// 頂点座標の設定
		g_vertexWk[i][0].vtx.x = -habaX * i + g_posScore.x;
		g_vertexWk[i][0].vtx.y = g_posScore.y;
		g_vertexWk[i][0].vtx.z = 0.0f;
		g_vertexWk[i][1].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE_SIZE_X;
		g_vertexWk[i][1].vtx.y = g_posScore.y;
		g_vertexWk[i][1].vtx.z = 0.0f;
		g_vertexWk[i][2].vtx.x = -habaX * i + g_posScore.x;
		g_vertexWk[i][2].vtx.y = g_posScore.y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWk[i][2].vtx.z = 0.0f;
		g_vertexWk[i][3].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE_SIZE_X;
		g_vertexWk[i][3].vtx.y = g_posScore.y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWk[i][3].vtx.z = 0.0f;

		// rhwの設定
		g_vertexWk[i][0].rhw =
		g_vertexWk[i][1].rhw =
		g_vertexWk[i][2].rhw =
		g_vertexWk[i][3].rhw = 1.0f;

		// 反射光の設定
		g_vertexWk[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWk[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		g_vertexWk[i][0].tex = D3DXVECTOR2( 0.0f, 0.0f );
		g_vertexWk[i][1].tex = D3DXVECTOR2( 1.0f, 0.0f );
		g_vertexWk[i][2].tex = D3DXVECTOR2( 0.0f, 1.0f );
		g_vertexWk[i][3].tex = D3DXVECTOR2( 1.0f, 1.0f );
	}

	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetTextureScore(void)
{
	int i;
	int number = g_Score;
	
	for( i = 0; i < SCORE_DIGIT; i++ )
	{
		// テクスチャ座標の設定
		float x = (float)(number % 10);
		g_vertexWk[i][0].tex = D3DXVECTOR2( 0.1f * x, 0.0f );
		g_vertexWk[i][1].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 0.0f );
		g_vertexWk[i][2].tex = D3DXVECTOR2( 0.1f * x, 1.0f );
		g_vertexWk[i][3].tex = D3DXVECTOR2( 0.1f * ( x + 1 ),	 1.0f );
		number /= 10;
	}

}
//=============================================================================
// HPデータをセットする
// 引数:add :追加する点数。マイナスも可能、初期化などに。
//=============================================================================
void AddScore( int add )
{
	g_Score += add;
	if( g_Score > SCORE_MAX )
	{
		g_Score = SCORE_MAX;
	}

}

int *GetScore(void)
{
	return &g_Score;
}
