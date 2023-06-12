//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#pragma once

// �}�N����`
#define TEXTURE_GAME_SCORE				("data/TEXTURE/number000.png")	// �T���v���p�摜
#define TEXTURE_SCORE_SIZE_X			(32)		// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE_SIZE_Y			(32)		// ����
#define SCORE_POS_X						(550)		// �|���S���̏����ʒuX
#define SCORE_POS_Y						(20)		// ����
#define SCORE_MAX						(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT						(5)			// ����

#define TEXTURE_PATTERN_DIVIDE_S_X		(10)		// �X�R�A�p�����e�N�X�`���̕�����
#define TEXTURE_PATTERN_DIVIDE_S_Y		(1)			// ����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore( int add );
int *GetScore(void);

