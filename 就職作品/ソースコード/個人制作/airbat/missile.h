//=============================================================================
//
// �~�T�C������ [missile.h]
// Author : Imai
//
//=============================================================================
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "main.h"


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct MISSILE
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
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#define BULET_SIZE_Y       (10.0f)				//�~�T�C���̑傫��
#define BULET_SIZE_Z       (10.0f)				//�~�T�C���̑傫��
#define BULET_SIZE_X       (10.0f)				//�~�T�C���̑傫��
#define	MAX_MISSILE		   (128)				// �r���{�[�h�ő吔

HRESULT InitMissile(void);
void UninitMissile(void);
void UpdateMissile(void);
void DrawMissile(void);
MISSILE *GetMissile();

int SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer);
void DeleteMissile(int nIdxMissile);
#endif
