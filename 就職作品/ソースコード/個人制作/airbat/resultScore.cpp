//=============================================================================
//
// ポリゴン処理 [resultScore.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "score.h"
#include "resultScore.h"
#include "ranking.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultScore(void);
void SetTextureResultScore(void);
void SetVertexResultScore(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
/*進んだ距離*/
LPDIRECT3DTEXTURE9		g_pD3DTextureResultScore[RESULTSCORE_DIGITS];	// テクスチャへのポインタ
VERTEX_2D				g_vertexWkResultScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				g_posResultScore[RESULTSCORE_DIGITS];					// 数字の位置

/*倒した敵の数*/
LPDIRECT3DTEXTURE9		g_pD3DTextureBeatScore[RESULTSCORE_DIGITS];	// テクスチャへのポインタ
VERTEX_2D				g_vertexWkBeatScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				g_posBeatScore[RESULTSCORE_DIGITS];					// 数字の位置

/*総スコア*/
LPDIRECT3DTEXTURE9		g_pD3DTextureAllScore[RESULTSCORE_DIGITS];	// テクスチャへのポインタ
VERTEX_2D				g_vertexWkAllScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// 頂点情報格納ワーク
D3DXVECTOR3				g_posAllScore[RESULTSCORE_DIGITS];					// 数字の位置

static int g_scoreNum = 0;

static bool saveScore;		// スコアをランキング用に保存したか否か

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posResultScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), RESULTSCORE_POS_Y, 0.0f);
	}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posBeatScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), BEATSCORE_POS_Y, 0.0f);
	}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posAllScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), ALLSCORE_POS_Y, 0.0f);
	}

	g_scoreNum = 0;
	saveScore = false;

	// テクスチャの読み込み  
	if (type == 0)	// 初回のみ読み込む
	{
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
				TEXTURE_GAME_RESULTSCORE,				// ファイルの名前
				&g_pD3DTextureResultScore[i]);			// 読み込むメモリのポインタ
		}
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
				TEXTURE_GAME_RESULTSCORE,				// ファイルの名前
				&g_pD3DTextureBeatScore[i]);			// 読み込むメモリのポインタ
		}
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
				TEXTURE_GAME_RESULTSCORE,				// ファイルの名前
				&g_pD3DTextureAllScore[i]);			// 読み込むメモリのポインタ
		}

	}

	MakeVertexResultScore();

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitResultScore(void)
{

	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		if (g_pD3DTextureResultScore[i] != NULL)
		{
			g_pD3DTextureResultScore[i]->Release();
			g_pD3DTextureResultScore[i] = NULL;
		}

		if (g_pD3DTextureResultScore[i] != NULL)
		{
			g_pD3DTextureBeatScore[i]->Release();
			g_pD3DTextureBeatScore[i] = NULL;
		}

		if (g_pD3DTextureAllScore[i] != NULL)
		{
			g_pD3DTextureAllScore[i]->Release();
			g_pD3DTextureAllScore[i] = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultScore(void)
{
	SetTextureResultScore();
}


//=============================================================================
// スコア描画処理
//=============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	// テクスチャの設定 
	//	pDevice->SetTexture(0, g_pD3DTextureResultScore[i]);

	//	// ポリゴンの描画
	//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultScore[i], sizeof(VERTEX_2D));
	//}
	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	// テクスチャの設定 
	//	pDevice->SetTexture(0, g_pD3DTextureBeatScore[i]);

	//	// ポリゴンの描画
	//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBeatScore[i], sizeof(VERTEX_2D));
	//}
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		// テクスチャの設定 
		pDevice->SetTexture(0, g_pD3DTextureAllScore[i]);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkAllScore[i], sizeof(VERTEX_2D));
	}

}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexResultScore();

	for (int no = 0; no < RESULTSCORE_DIGITS; no++)
	{
		// 数字の頂点座標の設定
		// 進んだ距離
		g_vertexWkResultScore[no][0].rhw =
			g_vertexWkResultScore[no][1].rhw =
			g_vertexWkResultScore[no][2].rhw =
			g_vertexWkResultScore[no][3].rhw = 1.0f;

		g_vertexWkResultScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkResultScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkResultScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkResultScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkResultScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);

		// 数字の頂点座標の設定
		// 倒した敵の数
		g_vertexWkBeatScore[no][0].rhw =
			g_vertexWkBeatScore[no][1].rhw =
			g_vertexWkBeatScore[no][2].rhw =
			g_vertexWkBeatScore[no][3].rhw = 1.0f;

		g_vertexWkBeatScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkBeatScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkBeatScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkBeatScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkBeatScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);

		// 数字の頂点座標の設定
		// 総スコア
		g_vertexWkAllScore[no][0].rhw =
			g_vertexWkAllScore[no][1].rhw =
			g_vertexWkAllScore[no][2].rhw =
			g_vertexWkAllScore[no][3].rhw = 1.0f;

		g_vertexWkAllScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkAllScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkAllScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkAllScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkAllScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureResultScore(void)
{
	PLAYER *player = GetPlayer();
	int allScore = *GetScore();		// 総スコア

	//player->distanceScore = (int)(player->maxDistance / 20);
	//int beatNum = player->beatEnemyNum;
	//int allScore = player->distanceScore + beatNum * 50;
	
	//int allScore = 1000;												// 総スコア

	if (saveScore != true)
	{
		SaveRankingScore(allScore);
		saveScore = true;
	}
	////テクスチャ座標の設定
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	/*進んだ距離*/
	//	float tx1 = (float)(allScore % 10) - 1.0f;		//10で割ったあまりがその桁の数字になる
	//	g_vertexWkResultScore[i][0].tex = D3DXVECTOR2(tx1 * 0.1f, 0.0f);
	//	g_vertexWkResultScore[i][1].tex = D3DXVECTOR2((tx1 + 1) *0.1f, 0.0f);
	//	g_vertexWkResultScore[i][2].tex = D3DXVECTOR2(tx1 * 0.1f, 1.0f);
	//	g_vertexWkResultScore[i][3].tex = D3DXVECTOR2((tx1 + 1) * 0.1f, 1.0f);
	//	allScore /= 10;							//桁を右に一つ移動
	//}
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	/*倒した敵の数*/
	//	float tx2 = (float)(allScore % 10) - 1.0f;		//10で割ったあまりがその桁の数字になる
	//	g_vertexWkBeatScore[i][0].tex = D3DXVECTOR2(tx2 * 0.1f, 0.0f);
	//	g_vertexWkBeatScore[i][1].tex = D3DXVECTOR2((tx2 + 1) *0.1f, 0.0f);
	//	g_vertexWkBeatScore[i][2].tex = D3DXVECTOR2(tx2 * 0.1f, 1.0f);
	//	g_vertexWkBeatScore[i][3].tex = D3DXVECTOR2((tx2 + 1) * 0.1f, 1.0f);
	//	allScore /= 10;							//桁を右に一つ移動
	//}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		/*総スコア*/
		float tx3 = (float)(allScore % 10) - 1.0f;		//10で割ったあまりがその桁の数字になる
		g_vertexWkAllScore[i][0].tex = D3DXVECTOR2(tx3 * 0.1f, 0.0f);
		g_vertexWkAllScore[i][1].tex = D3DXVECTOR2((tx3 + 1) *0.1f, 0.0f);
		g_vertexWkAllScore[i][2].tex = D3DXVECTOR2(tx3 * 0.1f, 1.0f);
		g_vertexWkAllScore[i][3].tex = D3DXVECTOR2((tx3 + 1) * 0.1f, 1.0f);
		allScore /= 10;							//桁を右に一つ移動
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexResultScore(void)
{
	/*数字のテクスチャ*/
	for (int no = 0; no < RESULTSCORE_DIGITS; no++)
	{
		/*進んだ距離*/
		g_vertexWkResultScore[no][0].vtx.x = g_posResultScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][0].vtx.y = g_posResultScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][0].vtx.z = 0.0f;

		g_vertexWkResultScore[no][1].vtx.x = g_posResultScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][1].vtx.y = g_posResultScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][1].vtx.z = 0.0f;

		g_vertexWkResultScore[no][2].vtx.x = g_posResultScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][2].vtx.y = g_posResultScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][2].vtx.z = 0.0f;

		g_vertexWkResultScore[no][3].vtx.x = g_posResultScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][3].vtx.y = g_posResultScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][3].vtx.z = 0.0f;

		/*倒した敵の数*/
		g_vertexWkBeatScore[no][0].vtx.x = g_posBeatScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][0].vtx.y = g_posBeatScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][0].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][1].vtx.x = g_posBeatScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][1].vtx.y = g_posBeatScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][1].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][2].vtx.x = g_posBeatScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][2].vtx.y = g_posBeatScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][2].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][3].vtx.x = g_posBeatScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][3].vtx.y = g_posBeatScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][3].vtx.z = 0.0f;

		/*総スコア*/
		g_vertexWkAllScore[no][0].vtx.x = g_posAllScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][0].vtx.y = g_posAllScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][0].vtx.z = 0.0f;

		g_vertexWkAllScore[no][1].vtx.x = g_posAllScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][1].vtx.y = g_posAllScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][1].vtx.z = 0.0f;

		g_vertexWkAllScore[no][2].vtx.x = g_posAllScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][2].vtx.y = g_posAllScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][2].vtx.z = 0.0f;

		g_vertexWkAllScore[no][3].vtx.x = g_posAllScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][3].vtx.y = g_posAllScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][3].vtx.z = 0.0f;

	}

}
