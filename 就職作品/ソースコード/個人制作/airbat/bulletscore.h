//=============================================================================
//
// �X�R�A���� [bulletscore.h]
// Author : Imai
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBulletScore(void);
void UninitBulletScore(void);
void UpdateBulletScore(void);
void DrawBulletScore(void);

void ChangeBulletScore(int value);

#endif
