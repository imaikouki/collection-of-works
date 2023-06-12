//=============================================================================
//
// �G�l�~�[���f������ [aircraftcarrier.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define MAX_AIRCRAFTCARRIER		(1)					// �G�l�~�[�̐�

#define AIRCRAFTCARRIER_SIZE_X       (150.0f)				//�G�l�~�[�̑傫��
#define AIRCRAFTCARRIER_SIZE_Y       (150.0f)				//�G�l�~�[�̑傫��
#define AIRCRAFTCARRIER_SIZE_Z       (150.0f)				//�G�l�~�[�̑傫��

struct AIRCRAFTCARRIER
{
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			rot;				// ���f���̌���(��])
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			move;				// ���f���̈ړ���

	LPDIRECT3DTEXTURE9	pD3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			pD3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pD3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD				nNumMat;			// �}�e���A�����̐�

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X

	bool				use;				//�g�p�����ǂ���
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitAircraftCarrier(void);
void UninitAircraftCarrier(void);
void UpdateAircraftCarrier(void);
void DrawAircraftCarrier(void);

AIRCRAFTCARRIER *GetAircraftCarrier();