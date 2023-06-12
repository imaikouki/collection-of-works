//=============================================================================
//
// �J�������� [camera.h]
// Author : Imai
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct CAMERA
{
	D3DXVECTOR3			pos;			// �J������FPS���_(�ʒu)
	D3DXVECTOR3			tpspos;			// �J������TPS���_(�ʒu)
	D3DXVECTOR3			at;				// �J�����̒����_
	D3DXVECTOR3			up;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			rot;			// �J�����̉�]
	float				len;			// �J�����̎��_�ƒ����_�̋���


	D3DXMATRIX			mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X


	D3DXVECTOR3 oldrot;					//�̂̊p�x
	D3DXVECTOR3 rotmv;					//�p�x�̈ړ���

	bool fpsmode;						//FPS���[�h

	int fpsbgmcnt;							//BGM�J�E���g
	int tpsbgmcnt;							//BGM�J�E���g						

	D3DXMATRIX TurnCam; // ��]�s��
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotMove();
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
CAMERA *GetCamera();
#endif
