//=============================================================================
//
// �G�l�~�[���f������ [enemy.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define MAX_ENEMY		(10)					// �G�l�~�[�̐�

#define ENEMY_SIZE_X       (150.0f)				//�G�l�~�[�̑傫��
#define ENEMY_SIZE_Y       (150.0f)
#define ENEMY_SIZE_Z       (150.0f)

struct ENEMY
{
	D3DXVECTOR3			pos;				// ���f���̈ʒu
	D3DXVECTOR3			rot;				// ���f���̌���(��])
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			move;				// ���f���̈ړ���

	float				spd;				// �ړ��X�s�[�h

	LPDIRECT3DTEXTURE9	pD3DTexture;		// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH			pD3DXMesh;			// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pD3DXBuffMat;		// �}�e���A�����ւ̃|�C���^
	DWORD				nNumMat;			// �}�e���A�����̐�

	int					tbl_cnt;			//�e�[�u���̃J�E���g
	float				move_time;			//�e�[�u���̎���
	float				posplus;
	int					pospluscnt;
	bool				posplususe;

	D3DXMATRIX			mtxWorld;			// ���[���h�}�g���b�N�X

	int recnt;
	bool				use;
	int					shadowIdx;			// �e�̃C���f�b�N�X�ԍ�
	int					life;				// �̗�
	int					randx;				//�G�l�~�[�̃����_���ʒu
	int					randy;				//�G�l�~�[�̃����_���ʒu
	int					randz;				//�G�l�~�[�̃����_���ʒu
	int					descnt;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy();