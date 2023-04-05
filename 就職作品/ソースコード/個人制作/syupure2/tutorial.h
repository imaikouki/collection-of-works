//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TUTORIAL		("data/TEXTURE/sousa.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TUTORIAL_LOGO	("data/TEXTURE/sentoukaisi.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TUTORIAL_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	TUTORIAL_SIZE_X		(640)							// �^�C�g���̕�
#define	TUTORIAL_SIZE_Y		(640)							// �^�C�g���̍���
#define	TUTORIALLOGO_POS_X		(350)							// �^�C�g�����S�̕\���ʒu
#define	TUTORIALLOGO_POS_Y		(350)							// �^�C�g�����S�̕\���ʒu
#define	TUTORIALLOGO_SIZE_X	(300)							// �^�C�g�����S�̕�
#define	TUTORIALLOGO_SIZE_Y	(80)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

