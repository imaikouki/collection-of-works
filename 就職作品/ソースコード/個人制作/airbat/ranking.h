//=============================================================================
//
// �|���S������ [ranking.h]
// Author : Imai
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_


// �}�N����`
#define TEXTURE_GAME_RANKINGSCORE	("data/TEXTURE/number004.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANKINGBG		("data/TEXTURE/rankingBG002.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK1			("data/TEXTURE/rank001.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK2			("data/TEXTURE/rank002.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK3			("data/TEXTURE/rank003.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK4			("data/TEXTURE/rank004.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK5			("data/TEXTURE/rank005.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK6			("data/TEXTURE/rank006.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK7			("data/TEXTURE/rank007.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK8			("data/TEXTURE/rank008.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK9			("data/TEXTURE/rank009.png")	// �T���v���p�摜  
#define TEXTURE_GAME_RANK10			("data/TEXTURE/rank010.png")	// �T���v���p�摜  

#define TEXTURE_RANKINGSCORE_SIZE_X	(50/2)								// �e�N�X�`���T�C�Y  
#define TEXTURE_RANKINGSCORE_SIZE_Y	(50/2)								// ����  
#define TEXTURE_RANK_SIZE_X			(100/2)								// ���ʂ̃e�N�X�`���T�C�Y
#define TEXTURE_RANK_SIZE_Y			(50/2)								// ����
#define TEXTURE_PATTERN_DIVIDE_RANK_X	(10)							// �A�j���p�^�[���̃e�N�X�`�����������iX)  
#define TEXTURE_PATTERN_DIVIDE_RANK_Y	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iY)  
#define ANIM_PATTERN_RANK_NUM			(TEXTURE_PATTERN_DIVIDE_RANK_X*TEXTURE_PATTERN_DIVIDE_RANK_Y)	// �A�j���[�V�����p�^�[����  
#define RANKINGSCORE_DIGITS				(5)								// �X�R�A�̍ő包��
#define RANKING_MAX						(10)							// ���ʂ܂ŕ\�����邩
#define RANKINGSCORE_MAX				(99999)							// �X�R�A�̍ő�l

#define FIRST_RANKINGSCORE_POS_Y	(60.0f)								// ���X�R�A��y���W
#define LAST_RANKINGSCORE_POS_Y		(420.0f)							// ����
#define RANKINGSCORE_INTERVAL_Y		(90.0f)									// �����L���O�\���̍s�Ԋu
#define FIRST_RANKINGSCORE_POS_X	(150.0f)								// �X�R�A�̈ꌅ�ڂ�x���W
#define RANK_POS_X					(120.0f)							// ���ʂ̕����̕\���ʒu

#define RANKING_BG_SIZE_X			(540)				// �����L���O�\���̔w�i�̃T�C�Y
#define RANKING_BG_SIZE_Y			(480)				// ����
#define RANKING_BG_POS_X			(50.0f)			// �����L���O�\���̔w�i�̈ʒu
#define RANKING_BG_POS_Y			(0.0f)			// ����

#define BG_NUM_DIFFER_ABOVE			(30.0f)			// �����L���O�w�i�Ɛ����̈ʒu�̍��i��j
#define BG_NUM_DIFFER_BELLOW		(30.0f)		// �����L���O�w�i�Ɛ����̈ʒu�̍��i���j

typedef struct 
{
	D3DXVECTOR3				pos;					// �X�R�A�\���p�����̈ʒu
	D3DXVECTOR3				oldPos;					// �ړ��O�̈ʒu���W
	LPDIRECT3DTEXTURE9		texture;				// �X�R�A�\���p�����̃e�N�X�`��
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

}RANKINGNUM;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRankingScore(int type);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);

void SaveRankingScore(int score);
int *GetRankingScore(void);
bool *GetAppearInfo(void);


#endif
