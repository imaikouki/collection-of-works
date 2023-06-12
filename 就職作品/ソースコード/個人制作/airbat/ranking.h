//=============================================================================
//
// ポリゴン処理 [ranking.h]
// Author : Imai
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_


// マクロ定義
#define TEXTURE_GAME_RANKINGSCORE	("data/TEXTURE/number004.png")	// サンプル用画像  
#define TEXTURE_GAME_RANKINGBG		("data/TEXTURE/rankingBG002.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK1			("data/TEXTURE/rank001.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK2			("data/TEXTURE/rank002.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK3			("data/TEXTURE/rank003.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK4			("data/TEXTURE/rank004.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK5			("data/TEXTURE/rank005.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK6			("data/TEXTURE/rank006.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK7			("data/TEXTURE/rank007.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK8			("data/TEXTURE/rank008.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK9			("data/TEXTURE/rank009.png")	// サンプル用画像  
#define TEXTURE_GAME_RANK10			("data/TEXTURE/rank010.png")	// サンプル用画像  

#define TEXTURE_RANKINGSCORE_SIZE_X	(50/2)								// テクスチャサイズ  
#define TEXTURE_RANKINGSCORE_SIZE_Y	(50/2)								// 同上  
#define TEXTURE_RANK_SIZE_X			(100/2)								// 順位のテクスチャサイズ
#define TEXTURE_RANK_SIZE_Y			(50/2)								// 同上
#define TEXTURE_PATTERN_DIVIDE_RANK_X	(10)							// アニメパターンのテクスチャ内分割数（X)  
#define TEXTURE_PATTERN_DIVIDE_RANK_Y	(1)								// アニメパターンのテクスチャ内分割数（Y)  
#define ANIM_PATTERN_RANK_NUM			(TEXTURE_PATTERN_DIVIDE_RANK_X*TEXTURE_PATTERN_DIVIDE_RANK_Y)	// アニメーションパターン数  
#define RANKINGSCORE_DIGITS				(5)								// スコアの最大桁数
#define RANKING_MAX						(10)							// 何位まで表示するか
#define RANKINGSCORE_MAX				(99999)							// スコアの最大値

#define FIRST_RANKINGSCORE_POS_Y	(60.0f)								// 総スコアのy座標
#define LAST_RANKINGSCORE_POS_Y		(420.0f)							// 同上
#define RANKINGSCORE_INTERVAL_Y		(90.0f)									// ランキング表示の行間隔
#define FIRST_RANKINGSCORE_POS_X	(150.0f)								// スコアの一桁目のx座標
#define RANK_POS_X					(120.0f)							// 順位の文字の表示位置

#define RANKING_BG_SIZE_X			(540)				// ランキング表示の背景のサイズ
#define RANKING_BG_SIZE_Y			(480)				// 同上
#define RANKING_BG_POS_X			(50.0f)			// ランキング表示の背景の位置
#define RANKING_BG_POS_Y			(0.0f)			// 同上

#define BG_NUM_DIFFER_ABOVE			(30.0f)			// ランキング背景と数字の位置の差（上）
#define BG_NUM_DIFFER_BELLOW		(30.0f)		// ランキング背景と数字の位置の差（下）

typedef struct 
{
	D3DXVECTOR3				pos;					// スコア表示用文字の位置
	D3DXVECTOR3				oldPos;					// 移動前の位置座標
	LPDIRECT3DTEXTURE9		texture;				// スコア表示用数字のテクスチャ
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

}RANKINGNUM;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRankingScore(int type);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void SaveRankingScore(int score);
int *GetRankingScore(void);
bool *GetAppearInfo(void);


#endif
