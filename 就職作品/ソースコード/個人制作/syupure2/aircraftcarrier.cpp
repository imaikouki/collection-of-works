//=============================================================================
//
// �G�l�~�[���f������ [aircraftcarrier.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "aircraftcarrier.h"
#include "shadow.h"
#include "game.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define	MODEL_AIRCRAFTCARRIER			"data/MODEL/airplane000.x"			// �ǂݍ��ރ��f����
#define	MODEL_AIRCRAFTCARRIER	"data/MODEL/aircraftcarrier.x"		// �ǂݍ��ރ��f����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static AIRCRAFTCARRIER				g_AircraftCarrier[MAX_AIRCRAFTCARRIER];				// ���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitAircraftCarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* �����_���p�����ݒ� */
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		g_AircraftCarrier[i].use = true;			// �g��

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_AircraftCarrier[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_AircraftCarrier[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_AircraftCarrier[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		g_AircraftCarrier[i].move = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

		g_AircraftCarrier[i].pD3DTexture = NULL;
		g_AircraftCarrier[i].pD3DXMesh = NULL;
		g_AircraftCarrier[i].pD3DXBuffMat = NULL;
		g_AircraftCarrier[i].nNumMat = 0;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_AIRCRAFTCARRIER,					// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
			D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
			pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
			NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			&g_AircraftCarrier[i].pD3DXBuffMat,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
			&g_AircraftCarrier[i].nNumMat,		// D3DXMATERIAL�\���̂̐�
			&g_AircraftCarrier[i].pD3DXMesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,				// �t�@�C���̖��O
			&g_AircraftCarrier[i].pD3DTexture);		// �ǂݍ��ރ������[
#endif

		//// �e�̏�����
		//D3DXVECTOR3 pos = g_AircraftCarrier[i].pos;
		//pos.y = 0.0f;
		//g_AircraftCarrier[i].shadowIdx = CreateShadow(pos, g_AircraftCarrier[i].scl);

		//g_AircraftCarrier[i].tbl_adr = NULL;
		//g_AircraftCarrier[i].tbl_cnt = 0;
		//g_AircraftCarrier[i].move_time = 0.0f;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitAircraftCarrier(void)
{

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		if (g_AircraftCarrier[i].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_AircraftCarrier[i].pD3DTexture->Release();
			g_AircraftCarrier[i].pD3DTexture = NULL;
		}

		if (g_AircraftCarrier[i].pD3DXMesh != NULL)
		{// ���b�V���̊J��
			g_AircraftCarrier[i].pD3DXMesh->Release();
			g_AircraftCarrier[i].pD3DXMesh = NULL;
		}

		if (g_AircraftCarrier[i].pD3DXBuffMat != NULL)
		{// �}�e���A���̊J��
			g_AircraftCarrier[i].pD3DXBuffMat->Release();
			g_AircraftCarrier[i].pD3DXBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAircraftCarrier(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAircraftCarrier(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int i = 0; i < MAX_AIRCRAFTCARRIER; i++)
	{
		// �g���Ă���Ȃ珈������
		if (g_AircraftCarrier[i].use == true)
		{
			// �g���Ă��Ȃ��̂Ȃ�R���e�B�j���[����
			if(g_AircraftCarrier[i].use == false) continue;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_AircraftCarrier[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_AircraftCarrier[i].scl.x, g_AircraftCarrier[i].scl.y, g_AircraftCarrier[i].scl.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_AircraftCarrier[i].rot.y, g_AircraftCarrier[i].rot.x, g_AircraftCarrier[i].rot.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_AircraftCarrier[i].pos.x, g_AircraftCarrier[i].pos.y, g_AircraftCarrier[i].pos.z);
			D3DXMatrixMultiply(&g_AircraftCarrier[i].mtxWorld, &g_AircraftCarrier[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_AircraftCarrier[i].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_AircraftCarrier[i].pD3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_AircraftCarrier[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_AircraftCarrier[i].pD3DTexture);

				// �`��
				g_AircraftCarrier[i].pD3DXMesh->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=============================================================================
// �G�l�~�[�̎擾
//=============================================================================
AIRCRAFTCARRIER *GetAircraftCarrier()
{
	return &(g_AircraftCarrier[0]);
}
