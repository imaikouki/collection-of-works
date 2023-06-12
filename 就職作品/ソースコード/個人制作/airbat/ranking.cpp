//=============================================================================
//
// ポリゴン処理 [ranking.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "score.h"
#include "ranking.h"
#include "titleselection.h"
#include "input.h"
#include "getScore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRankingScore(void);
void SetTextureRankingScore(void);
void SetVertexRankingScore(void);

void SortRanking(void);

HRESULT MakeVertexRankingBG(void);
void SetVertexRankingBG(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
/*総スコア*/
RANKINGNUM g_rankingNum[RANKINGSCORE_DIGITS][RANKING_MAX];
RANKINGNUM g_rank[RANKING_MAX];

static LPDIRECT3DTEXTURE9	g_pD3DTextureRankingScore = NULL;		// テクスチャのポインタ
static LPDIRECT3DTEXTURE9	g_pD3DTextureRankingBG = NULL;

static D3DXVECTOR3			g_posRankingBG;

static VERTEX_2D			g_vertexWkRankingBG[NUM_VERTEX];

int							g_rankingScore[RANKING_MAX];			// ランキング用スコア保存

bool						g_appearRanking = false;				// ランキングを表示するか否か
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRankingScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み  
	if (type == 0)	// 初回のみ読み込む
	{
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANKINGSCORE,				// ファイルの名前
			&g_pD3DTextureRankingScore);			// 読み込むメモリのポインタ

		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANKINGBG,				// ファイルの名前
			&g_pD3DTextureRankingBG);			// 読み込むメモリのポインタ

		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK1,				// ファイルの名前
			&g_rank[0].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK2,				// ファイルの名前
			&g_rank[1].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK3,				// ファイルの名前
			&g_rank[2].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK4,				// ファイルの名前
			&g_rank[3].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK5,				// ファイルの名前
			&g_rank[4].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK6,				// ファイルの名前
			&g_rank[5].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK7,				// ファイルの名前
			&g_rank[6].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK8,				// ファイルの名前
			&g_rank[7].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK9,				// ファイルの名前
			&g_rank[8].texture);			// 読み込むメモリのポインタ
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RANK10,				// ファイルの名前
			&g_rank[9].texture);			// 読み込むメモリのポインタ


		// ランキングスコアの初期化
		for (int i = 0; i < RANKING_MAX; i++)
		{
			g_rankingScore[i] = 0;
		}
	}

	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			g_rankingNum[i][j].texture = g_pD3DTextureRankingScore;					// テクスチャの読み込み
			g_rankingNum[i][j].pos = D3DXVECTOR3(FIRST_RANKINGSCORE_POS_X + TEXTURE_RANKINGSCORE_SIZE_X * 2 * ((RANKINGSCORE_DIGITS - i) + 1),
				FIRST_RANKINGSCORE_POS_Y + (RANKINGSCORE_INTERVAL_Y * j), 0.0f);	// 位置座標の設定
			g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].pos = D3DXVECTOR3(RANK_POS_X, g_rankingNum[0][i].pos.y, 0.0f);
		g_rank[i].oldPos = g_rank[i].pos;
	}

	g_posRankingBG = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y, 0.0f);
	g_appearRanking = false;

	MakeVertexRankingScore();
	MakeVertexRankingBG();

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void UninitRankingScore(void)
{
	if (g_pD3DTextureRankingScore != NULL)
	{	// テクスチャの開放
		g_pD3DTextureRankingScore->Release();
		g_pD3DTextureRankingScore = NULL;
	}

	if (g_pD3DTextureRankingBG != NULL)
	{
		g_pD3DTextureRankingBG->Release();
		g_pD3DTextureRankingBG = NULL;
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		if (g_rank[i].texture != NULL)
		{
			g_rank[i].texture->Release();
			g_rank[i].texture = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankingScore(void)
{
	ARROW *arrow = GetArrow();

	// デバッグ用
	if (GetKeyboardTrigger(DIK_A))
	{
		if (g_appearRanking == false)
		{
			g_appearRanking = true;
		}
		else if (g_appearRanking == true)
		{
			g_appearRanking = false;
		}
	}

	/*ランキングが表示されているか否か*/
	if (arrow->isRanked == true)
	{
		g_appearRanking = true;
	}
	else
	{
		g_appearRanking = false;
	}

	/*プレイヤーの入力で文字が移動*/
	if (g_appearRanking == true)
	{
		if (GetKeyboardPress(DIK_UP) || IsButtonPressed(0, BUTTON_UP))
		{
			/*数字が移動*/
			for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
			{
				for (int j = 0; j < RANKING_MAX; j++)
				{
					g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
					g_rankingNum[i][j].pos.y += 3.0f;

					if (g_rankingNum[i][0].pos.y >= FIRST_RANKINGSCORE_POS_Y)
					{
						g_rankingNum[i][j].pos = g_rankingNum[i][j].oldPos;
						g_rankingNum[i][0].pos.y = FIRST_RANKINGSCORE_POS_Y;
					}
				}
			}

			/*順位の文字が移動*/
			for (int i = 0; i < RANKING_MAX; i++)
			{
				g_rank[i].pos.y = g_rankingNum[0][i].pos.y;
			}
		}
		if (GetKeyboardPress(DIK_DOWN) || IsButtonPressed(0, BUTTON_DOWN))
		{
			/*数字が移動*/
			for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
			{
				for (int j = 0; j < RANKING_MAX; j++)
				{
					g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
					g_rankingNum[i][j].pos.y -= 3.0f;

					if (g_rankingNum[i][9].pos.y <= LAST_RANKINGSCORE_POS_Y)
					{
						g_rankingNum[i][j].pos = g_rankingNum[i][j].oldPos;
						g_rankingNum[i][9].pos.y = LAST_RANKINGSCORE_POS_Y;
					}
				}
			}

			/*順位の文字が移動*/
			for (int i = 0; i < RANKING_MAX; i++)
			{
				g_rank[i].pos.y = g_rankingNum[0][i].pos.y;
			}
		}

	}

	SortRanking();

	SetTextureRankingScore();

	SetVertexRankingScore();
}


//=============================================================================
// スコア描画処理
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_appearRanking == true)
	{
		// ランキングの背景
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定 
		pDevice->SetTexture(0, g_pD3DTextureRankingBG);
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRankingBG, sizeof(VERTEX_2D));


		// スコアの数字
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
		{
			for (int j = 0; j < RANKING_MAX; j++)
			{
				//if (g_rankingNum[i][j].pos.y >= RANKING_BG_POS_Y + TEXTURE_RANKINGSCORE_SIZE_Y
				//	&& g_rankingNum[i][j].pos.y <= RANKING_BG_POS_Y + RANKING_BG_SIZE_Y - TEXTURE_RANKINGSCORE_SIZE_Y)
				{
					// テクスチャの設定 
					pDevice->SetTexture(0, g_rankingNum[i][j].texture);

					// ポリゴンの描画
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rankingNum[i][j].vertexWk, sizeof(VERTEX_2D));
				}
			}
		}

		// 順位の文字
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		for (int i = 0; i < RANKING_MAX; i++)
		{
			// テクスチャの設定 
			pDevice->SetTexture(0, g_rank[i].texture);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rank[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexRankingScore();

	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			// 数字の頂点座標の設定
			g_rankingNum[i][j].vertexWk[0].rhw =
				g_rankingNum[i][j].vertexWk[1].rhw =
				g_rankingNum[i][j].vertexWk[2].rhw =
				g_rankingNum[i][j].vertexWk[3].rhw = 1.0f;

			g_rankingNum[i][j].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_rankingNum[i][j].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_rankingNum[i][j].vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_RANK_X, 0.0f);
			g_rankingNum[i][j].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_RANK_Y);
			g_rankingNum[i][j].vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_RANK_X, 1.0f / TEXTURE_PATTERN_DIVIDE_RANK_Y);
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].rhw =
			g_rank[i].vertexWk[1].rhw =
			g_rank[i].vertexWk[2].rhw =
			g_rank[i].vertexWk[3].rhw = 1.0f;

		g_rank[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_rank[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rank[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rank[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rank[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

HRESULT MakeVertexRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexRankingBG();

	g_vertexWkRankingBG[0].rhw =
		g_vertexWkRankingBG[1].rhw =
		g_vertexWkRankingBG[2].rhw =
		g_vertexWkRankingBG[3].rhw = 1.0f;

	g_vertexWkRankingBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);

	g_vertexWkRankingBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRankingBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRankingBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRankingBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRankingScore(void)
{
	static int rankingScore[RANKING_MAX];
	for (int i = 0; i < RANKING_MAX; i++)
	{
		rankingScore[i] = g_rankingScore[i];
	}
	float numAboveHeight[RANKING_MAX];			// 数字の表示範囲(上にある時、数字の上が削れる)
	float numBellowHeight[RANKING_MAX];			// 同上(下にある時、数字の下が削れる)

	/*数字の表示範囲の設定*/
	for (int i = 0; i < RANKING_MAX; i++)
	{
		numAboveHeight[i] = (g_rankingNum[0][i].pos.y - RANKING_BG_POS_Y - BG_NUM_DIFFER_ABOVE) / TEXTURE_RANKINGSCORE_SIZE_Y;
		if (numAboveHeight[i] >= 1.0f)
		{
			numAboveHeight[i] = 1.0f;
		}
		else if (numAboveHeight[i] <= 0.0f)
		{
			numAboveHeight[i] = 0.0f;
		}
		numAboveHeight[i] = 1.0f - numAboveHeight[i];


		numBellowHeight[i] = (RANKING_BG_POS_Y + RANKING_BG_SIZE_Y - BG_NUM_DIFFER_BELLOW - g_rankingNum[0][i].pos.y) / TEXTURE_RANKINGSCORE_SIZE_Y;
		if (numBellowHeight[i] >= 1.0f)
		{
			numBellowHeight[i] = 1.0f;
		}
		else if (numBellowHeight[i] <= 0.0f)
		{
			numBellowHeight[i] = 0.0f;
		}
	}

	// テクスチャ座標の設定
	for (int i = 0; i < RANKING_MAX; i++)
	{
		for (int j = 0; j < RANKINGSCORE_DIGITS; j++)
		{
			/*総スコア*/
			float tx = (float)(rankingScore[i] % 10) - 1.0f;		//10で割ったあまりがその桁の数字になる

			g_rankingNum[j][i].vertexWk[0].tex = D3DXVECTOR2(tx * 0.1f, 0.0f + numAboveHeight[i]);
			g_rankingNum[j][i].vertexWk[1].tex = D3DXVECTOR2((tx + 1) *0.1f, 0.0f + numAboveHeight[i]);
			g_rankingNum[j][i].vertexWk[2].tex = D3DXVECTOR2(tx * 0.1f, numBellowHeight[i]);
			g_rankingNum[j][i].vertexWk[3].tex = D3DXVECTOR2((tx + 1) * 0.1f, numBellowHeight[i]);

			//g_rankingNum[j][i].vertexWk[0].tex = D3DXVECTOR2(tx * 0.1f, 0.0f);
			//g_rankingNum[j][i].vertexWk[1].tex = D3DXVECTOR2((tx + 1) *0.1f, 0.0f);
			//g_rankingNum[j][i].vertexWk[2].tex = D3DXVECTOR2(tx * 0.1f, 1.0f);
			//g_rankingNum[j][i].vertexWk[3].tex = D3DXVECTOR2((tx + 1) * 0.1f, 1.0f);

			rankingScore[i] /= 10;							//桁を右に一つ移動
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, numAboveHeight[i]);
		g_rank[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, numAboveHeight[i]);
		g_rank[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, numBellowHeight[i]);
		g_rank[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, numBellowHeight[i]);
	}
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRankingScore(void)
{
	/*数字のテクスチャ*/
	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			/*総スコア*/
			g_rankingNum[i][j].vertexWk[0].vtx.x = g_rankingNum[i][j].pos.x - TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[0].vtx.y = g_rankingNum[i][j].pos.y - TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[0].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[1].vtx.x = g_rankingNum[i][j].pos.x + TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[1].vtx.y = g_rankingNum[i][j].pos.y - TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[1].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[2].vtx.x = g_rankingNum[i][j].pos.x - TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[2].vtx.y = g_rankingNum[i][j].pos.y + TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[2].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[3].vtx.x = g_rankingNum[i][j].pos.x + TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[3].vtx.y = g_rankingNum[i][j].pos.y + TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[3].vtx.z = 0.0f;
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].vtx.x = g_rank[i].pos.x - TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[0].vtx.y = g_rank[i].pos.y - TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[0].vtx.z = 0.0f;

		g_rank[i].vertexWk[1].vtx.x = g_rank[i].pos.x + TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[1].vtx.y = g_rank[i].pos.y - TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[1].vtx.z = 0.0f;

		g_rank[i].vertexWk[2].vtx.x = g_rank[i].pos.x - TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[2].vtx.y = g_rank[i].pos.y + TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[2].vtx.z = 0.0f;

		g_rank[i].vertexWk[3].vtx.x = g_rank[i].pos.x + TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[3].vtx.y = g_rank[i].pos.y + TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[3].vtx.z = 0.0f;
	}
}

void SetVertexRankingBG(void)
{
	g_vertexWkRankingBG[0].vtx = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y, 0.0f);
	g_vertexWkRankingBG[1].vtx = D3DXVECTOR3(RANKING_BG_POS_X + RANKING_BG_SIZE_X, RANKING_BG_POS_Y, 0.0f);
	g_vertexWkRankingBG[2].vtx = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y + RANKING_BG_SIZE_Y, 0.0f);
	g_vertexWkRankingBG[3].vtx = D3DXVECTOR3(RANKING_BG_POS_X + RANKING_BG_SIZE_X, RANKING_BG_POS_Y + RANKING_BG_SIZE_Y, 0.0f);
}

int *GetRankingScore(void)
{
	return &g_rankingScore[0];
}

void SaveRankingScore(int score)
{
	// スコアが０の配列を探索
	int saveNum = 0;			// スコアを格納する添え字
	bool saveScore = false;		// スコア保存場所が決まったか否か
	int *rankScore = GetRankingScore();

	// 数値が0（まだスコアが記録されていない）のところに保存
	for (int i = 0; i < RANKING_MAX; i++)
	{
		if (rankScore[i] == 0)
		{
			rankScore[i] = score;
			saveScore = true;
			break;
		}
	}

	// 空きの配列がない場合、最小値である配列に格納
	if (saveScore == false)
	{
		int minScore = RANKINGSCORE_MAX;

		for (int i = 0; i < RANKING_MAX; i++)
		{
			if (rankScore[i] <= minScore)
			{
				minScore = rankScore[i];
				saveNum = i;
			}
		}

		rankScore[saveNum] = score;
	}
}

void SortRanking(void)
{
	// ランキングスコアを降順にソート
	for (int i = 0; i < RANKING_MAX; i++)
	{
		for (int j = i + 1; j < RANKING_MAX; j++)
		{
			if (g_rankingScore[i] < g_rankingScore[j])
			{
				int temp = g_rankingScore[i];
				g_rankingScore[i] = g_rankingScore[j];
				g_rankingScore[j] = temp;
			}
		}
	}
}

bool *GetAppearInfo(void)
{
	return &g_appearRanking;
}