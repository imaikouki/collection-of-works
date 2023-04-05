//=============================================================================
//
// �J�������� [camera.cpp]
// Author : Imai
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include <time.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_NEAR_Z			(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(100000.0f)				// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	INTERVAL_CAMERA_R	(12.5f)					// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_P	(0.05f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(1.0f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(100.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)					// �ǐՎ��̒����_�̍���

#define	POS_X_CAM		(0.0f)						// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(0.0f)						// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-150.0f)					// �J�����̏����ʒu(Z���W)

#define	ROT_Y_MOVE			(240.0f)						// �J�����̊��x(Y��)
#define CAMERA_MOVESPEED	(0.05f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA			g_Camera;					// �J�����f�[�^
D3DXVECTOR3		g_posCameraPDest;			// �J�����̎��_�̖ړI�ʒu
D3DXVECTOR3		g_posCameraRDest;			// �J�����̒����_�̖ړI�ʒu
D3DXVECTOR3		g_rotCamera;				// �J�����̉�]
float			g_fLengthIntervalCamera;	// �J�����̎��_�ƒ����_�̋���
float			g_fLengthIntervalPlayer;	// �v���C���[�ƒ����_�̋���
D3DXMATRIX		g_mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		g_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraPDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.oldrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rotmv = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx,vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);
	g_fLengthIntervalPlayer = INTERVAL_CAMERA_R;

	g_Camera.tpspos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.pos = D3DXVECTOR3(0, 0, 0);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.fpsmode = false;


	g_Camera.fpsbgmcnt = 0;
	g_Camera.tpsbgmcnt = 0;
	g_Camera.camcnt = 0;


	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	///* �����_���p�����ݒ� */
	//srand((unsigned)time(NULL));

	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 movePlayer;
	D3DXVECTOR3 ordcamerapos;
	PLAYER*player = GetPlayer();

	float fLength;

	// ���f���̈ʒu�擾
	posPlayer = GetPositionPlayer();

	// ���f���̈ړ��ʎ擾
	movePlayer = GetMovePlayer();


	//�J�[�\�����W�̎擾
	POINT curpos;
	GetCursorPos(&curpos);


	//�p�x�̈ړ��ʂ��v�Z
	g_Camera.rotmv = g_rotCamera - g_Camera.oldrot;

	//�p�x�̂̈����n��
	g_Camera.oldrot = g_rotCamera;

	//fpsmode
	if (g_Camera.fpsmode == true) //fpsmode
	{
		//// ���_�̖ړI�ʒu
		//fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;
		//g_posCameraPDest.y = posPlayer.y + CHASE_HEIGHT_P;
		//g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

		//// �����_�̖ړI�ʒu
		//fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
		//g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
		//g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

		// ���_�̕␳
		g_Camera.pos.x = posPlayer.x;
		g_Camera.pos.y = posPlayer.y;
		g_Camera.pos.z = posPlayer.z;

		g_Camera.at.x = posPlayer.x + movePlayer.x * 20;
		g_Camera.at.y = posPlayer.y + movePlayer.y * 20;
		g_Camera.at.z = posPlayer.z + movePlayer.z * 20;

		//��������
		if (GetKeyboardPress(DIK_G) || IsButtonPressed(0, BUTTON_CROSS_UP))
		{
			ordcamerapos = g_Camera.pos;
			g_Camera.pos = g_Camera.at + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			g_Camera.at = ordcamerapos;
		}

		if (g_Camera.fpsbgmcnt == 0)
		{
			// SE�Đ�
			PlaySound(SOUND_LABEL_SE_FPS);
			g_Camera.fpsbgmcnt = 900;
		}
		else
		{
			g_Camera.fpsbgmcnt--;
		}


		//fpsmodeoff
		if (GetKeyboardTrigger(DIK_F) || IsButtonTriggered(0, BUTTON_R3))
		{
			g_Camera.fpsbgmcnt = 0;
			//PlaySound(NULL, NULL, 0);
			g_Camera.fpsmode = false;
			// SE�Đ�
			StopSound(SOUND_LABEL_SE_FPS);

		}
	}

	//tpsmode
	else 
	{
		//// ���_�̖ړI�ʒu
		//fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;
		//g_posCameraPDest.y = posPlayer.y + CHASE_HEIGHT_P;
		//g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

		//// �����_�̖ړI�ʒu
		//fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
		//g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
		//g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

		// ���_�̕␳
		g_Camera.pos.x += (g_posCameraPDest.x - g_Camera.pos.x) * RATE_CHASE_CAMERA_P;
		g_Camera.pos.y += (g_posCameraPDest.y - g_Camera.pos.y) * RATE_CHASE_CAMERA_P;
		g_Camera.pos.z += (g_posCameraPDest.z - g_Camera.pos.z) * RATE_CHASE_CAMERA_P;

		g_Camera.pos.x = posPlayer.x - movePlayer.x * 15;
		g_Camera.pos.y = posPlayer.y - movePlayer.y * 15+ player->Upvec.y*10;
		g_Camera.pos.z = posPlayer.z - movePlayer.z * 15;
		if (player->accelnow <= ACCEL_TIME)
		{
			g_Camera.pos.y = 400.0f;
		}

		// �����_�̕␳
		g_Camera.at.x += (g_posCameraRDest.x - g_Camera.at.x) * RATE_CHASE_CAMERA_R;
		g_Camera.at.y += (g_posCameraRDest.y - g_Camera.at.y) * RATE_CHASE_CAMERA_R;
		g_Camera.at.z += (g_posCameraRDest.z - g_Camera.at.z) * RATE_CHASE_CAMERA_R;

		g_Camera.at.x = g_Camera.at.x = posPlayer.x + movePlayer.x * 10;
		g_Camera.at.y = posPlayer.y + movePlayer.y * 10;
		g_Camera.at.z = posPlayer.z + movePlayer.z * 10;

		//��������
		if (GetKeyboardPress(DIK_G)|| IsButtonPressed(0, BUTTON_CROSS_UP))
		{
			ordcamerapos = g_Camera.pos;
			g_Camera.pos = g_Camera.at + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			g_Camera.at = ordcamerapos;
		}

		if (g_Camera.tpsbgmcnt == 0)
		{
			// SE�Đ�
			PlaySound(SOUND_LABEL_SE_TPS);
			g_Camera.tpsbgmcnt = 900;
		}
		else
		{
			g_Camera.tpsbgmcnt--;
		}

		//fpsmodeoff
		if (GetKeyboardTrigger(DIK_F) || IsButtonTriggered(0, BUTTON_R3))
		{
			g_Camera.fpsmode = true;
			g_Camera.tpsbgmcnt = 0;
			StopSound(SOUND_LABEL_SE_TPS);
			g_Camera.tpsbgmcnt = 0;
		}
	}

	if (g_rotCamera.y >= D3DX_PI*2 || g_rotCamera.y <= -D3DX_PI*2)
	{
		g_rotCamera.y = 0.0f;
	}}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	PLAYER*player = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_Camera.pos,		// �J�����̎��_
						&g_Camera.at,		// �J�����̒����_
						&player->Upvec);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// ����p
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// �A�X�y�N�g��
								VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotMove(void)
{
	return g_Camera.rotmv;
}
//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_Camera;
}
