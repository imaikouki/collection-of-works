//=============================================================================
//
// �`���[�g���A����ʏ��� [rule.h]
// Author : Imai
//
//=============================================================================
#pragma once


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RULE1		("data/TEXTURE/ps.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RULE2		("data/TEXTURE/back.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RULE3		("data/TEXTURE/kaiten.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RULE4		("data/TEXTURE/zyouge.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_RULE5		("data/TEXTURE/sayu.png")
#define TEXTURE_RULE6		("data/TEXTURE/l1.png")
#define TEXTURE_RULE7		("data/TEXTURE/clear.png")
#define TEXTURE_RULE8		("data/TEXTURE/zyunbi.png")

#define	RULE_POS_X			(0)								// �`���[�g���A���̕\���ʒu
#define	RULE_POS_Y			(320)								// �`���[�g���A���̕\���ʒu
#define	RULE_SIZE_X			(640)							// �`���[�g���A���̕�
#define	RULE_SIZE_Y			(120)							// �`���[�g���A���̍���
#define	RULE_NUM			(8)								// �`���[�g���A���̃y�[�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRule(int type);
void UninitRule(void);
void UpdateRule(void);
void DrawRule(void);