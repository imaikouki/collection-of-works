//=============================================================================
//
// ���[�_�[�G���� [radarenemy.h]
// Author : Imai
//
//=============================================================================
#pragma once
#include "radar.h"

// �}�N����`
#define RADARENEMY_TEXTURE			("data/TEXTURE/teki.png")	// �摜
#define RADARENEMY_TEXTURE_SIZE_X	(50/10)		// �e�N�X�`���T�C�Y
#define RADARENEMY_TEXTURE_SIZE_Y	(50/10)		// ����

#define RADARENEMY_TEXTURE_PATTERN_DIVIDE_X	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define RADARENEMY_ANIM_PATTERN_NUM			(RADARENEMY_TEXTURE_PATTERN_DIVIDE_X*RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define RADARENEMY_TIME_ANIMATION			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define RADARENEMY_MAX						(4) // �G�̍ő吔
#define RADARENEMY_SPEEDX					(0.5) // �G�̃X�s�[�h
#define RADARENEMY_SPEEDY						(0.5) // �G�̃X�s�[�h
#define NX (SCREEN_WIDTH - RADARBOU_SIZE_X  / 2.0f)
#define NY (SCREEN_HEIGHT - RADARBOU_SIZE_Y / 2.0f)

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

typedef struct	// �G�l�~�[�\����
{
	bool			use;						// true:�g�p  false:���g�p
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		ppos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	D3DXVECTOR3		vec;
	int				PatternAnim;				// �A�j���[�V�����p�^�[���i���o�[
	int				CountAnim;					// �A�j���[�V�����J�E���g

	LPDIRECT3DTEXTURE9	Texture;				// �e�N�X�`�����
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N

	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x
	float			distance;					//�v���C���[�ƃG�l�~�[�̋���
} RADARENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRadarEnemy(int type);
void UninitRadarEnemy(void);
void UpdateRadarEnemy(void);
void DrawRadarEnemy(void);
void SetBullet(D3DXVECTOR3 pos);
RADARENEMY *GetRadarEnemy(void);


