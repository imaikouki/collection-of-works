//=============================================================================
//
// ポリゴン処理 [resultScore.h]
// Author : Imai
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_


// マクロ定義
#define TEXTURE_GAME_RESULTSCORE	("data/TEXTURE/number004.png")	// サンプル用画像  
#define TEXTURE_RESULTSCORE_SIZE_X	(50/2)								// テクスチャサイズ  
#define TEXTURE_RESULTSCORE_SIZE_Y	(100/2)								// 同上  
#define TEXTURE_PATTERN_DIVIDE_RS_X	(10)								// アニメパターンのテクスチャ内分割数（X)  
#define TEXTURE_PATTERN_DIVIDE_RS_Y	(1)								// アニメパターンのテクスチャ内分割数（Y)  
#define ANIM_PATTERN_RS_NUM			(TEXTURE_PATTERN_DIVIDE_RS_X*TEXTURE_PATTERN_DIVIDE_RS_Y)	// アニメーションパターン数  
#define RESULTSCORE_DIGITS				(5)								//スコアの最大桁数
#define RESULTSCORE_MAX					(99999)

#define RESULTSCORE_POS_Y			(180.0f)								// 進んだ距離スコアのy座標
#define BEATSCORE_POS_Y				(250.0f)								// 倒した敵の数スコアのy座標
#define ALLSCORE_POS_Y				(300.0f)								// 総スコアのy座標
#define FIRST_SCORE_POS_X			(125.0)								// スコアの一桁目のx座標


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultScore(int type);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);

#endif
