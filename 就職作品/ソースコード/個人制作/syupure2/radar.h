//=============================================================================
//
// ���[�_�[���� [radar.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RADAR		("data/TEXTURE/radar.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RADAR_LOGO	("data/TEXTURE/bou5.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RADAR_POS_X			(0)								// �^�C�g���̕\���ʒu
#define	RADAR_POS_Y			(0)								// �^�C�g���̕\���ʒu
#define	RADAR_SIZE_X		(640)							// �^�C�g���̕�
#define	RADAR_SIZE_Y		(640)							// �^�C�g���̍���
#define	RADARBOU_POS_X		(350)							// �^�C�g�����S�̕\���ʒu
#define	RADARBOU_POS_Y		(350)							// �^�C�g�����S�̕\���ʒu
#define RADARBOU_SIZE_X		(90.0f)							//���[�_�[�_�̃T�C�Y		
#define RADARBOU_SIZE_Y		(90.0f)							//���[�_�[�_�̃T�C�Y

typedef struct
{
	D3DXVECTOR3		pos;						// �|���S���̈ړ���
	D3DXVECTOR3		rot;						// �|���S���̉�]��
	float			Radius;						// �G�l�~�[�̔��a
	float			BaseAngle;					// �G�l�~�[�̊p�x
	VERTEX_2D		vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
}RADAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRadar(int type);
void UninitRadar(void);
void UpdateRadar(void);
void DrawRadar(void);

