//=============================================================================
//
// �|���S������ [resultScore.h]
// Author : Imai
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_


// �}�N����`
#define TEXTURE_GAME_RESULTSCORE	("data/TEXTURE/number004.png")	// �T���v���p�摜  
#define TEXTURE_RESULTSCORE_SIZE_X	(50/2)								// �e�N�X�`���T�C�Y  
#define TEXTURE_RESULTSCORE_SIZE_Y	(100/2)								// ����  
#define TEXTURE_PATTERN_DIVIDE_RS_X	(10)								// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define TEXTURE_PATTERN_DIVIDE_RS_Y	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define ANIM_PATTERN_RS_NUM			(TEXTURE_PATTERN_DIVIDE_RS_X*TEXTURE_PATTERN_DIVIDE_RS_Y)	// �A�j���[�V�����p�^�[����  
#define RESULTSCORE_DIGITS				(5)								//�X�R�A�̍ő包��
#define RESULTSCORE_MAX					(99999)

#define RESULTSCORE_POS_Y			(180.0f)								// �i�񂾋����X�R�A��y���W
#define BEATSCORE_POS_Y				(250.0f)								// �|�����G�̐��X�R�A��y���W
#define ALLSCORE_POS_Y				(300.0f)								// ���X�R�A��y���W
#define FIRST_SCORE_POS_X			(125.0)								// �X�R�A�̈ꌅ�ڂ�x���W


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultScore(int type);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);

#endif
