//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#pragma once

// マクロ定義
#define TEXTURE_GAME_SCORE				("data/TEXTURE/number000.png")	// サンプル用画像
#define TEXTURE_SCORE_SIZE_X			(32)		// テクスチャサイズ
#define TEXTURE_SCORE_SIZE_Y			(32)		// 同上
#define SCORE_POS_X						(550)		// ポリゴンの初期位置X
#define SCORE_POS_Y						(20)		// 同上
#define SCORE_MAX						(99999)		// スコアの最大値
#define SCORE_DIGIT						(5)			// 桁数

#define TEXTURE_PATTERN_DIVIDE_S_X		(10)		// スコア用数字テクスチャの分割数
#define TEXTURE_PATTERN_DIVIDE_S_Y		(1)			// 同上

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );
int *GetScore(void);

