//=============================================================================
//
// �e���� [enemybullet.h]
// Author : Imai
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	D3DXVECTOR3 scale;		// �X�P�[��
	D3DXVECTOR3 move;		// �ړ���
	float fSizeX;			// ��
	float fSizeY;			// ����
	int nTimer;				// �^�C�}�[
	int nIdxShadow;			// �eID
	bool bUse;				// �g�p���Ă��邩�ǂ���
} ENEMYBULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#define ENEMYBULLET_SIZE_X       (10.0f)				//�e�̑傫��
#define ENEMYBULLET_SIZE_Y       (10.0f)				//�e�̑傫��
#define ENEMYBULLET_SIZE_Z       (10.0f)				//�e�̑傫��
#define	MAX_ENEMYBULLET			 (1000)					// �r���{�[�h�ő吔

HRESULT InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
ENEMYBULLET *GetEnemyBullet();
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer);
void DeleteEnemyBullet(int nIdxEnemyBullet);

#endif
