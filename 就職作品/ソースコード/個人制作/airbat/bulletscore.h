//=============================================================================
//
// スコア処理 [bulletscore.h]
// Author : Imai
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBulletScore(void);
void UninitBulletScore(void);
void UpdateBulletScore(void);
void DrawBulletScore(void);

void ChangeBulletScore(int value);

#endif
