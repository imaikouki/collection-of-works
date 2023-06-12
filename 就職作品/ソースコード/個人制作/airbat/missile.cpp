//=============================================================================
//
// �~�T�C������ [missile.cpp]
// Author : Imai
//
//=============================================================================
#include "missile.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_MISSILE			"data/TEXTURE/missile000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MISSILE_SIZE_X			(50.0f)							// �r���{�[�h�̕�
#define	MISSILE_SIZE_Y			(50.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_MISSILE		(2.0f)							// �ړ����x
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexMissile(LPDIRECT3DDEVICE9 pDevice);
void SetVertexMissile(int nIdxMissile, float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMissile = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMissile = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldMissile;				// ���[���h�}�g���b�N�X

MISSILE					g_aMissile[MAX_MISSILE];			// �e���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexMissile(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_MISSILE,				// �t�@�C���̖��O
								&g_pD3DTextureMissile);	// �ǂݍ��ރ������[

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		g_aMissile[nCntMissile].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMissile[nCntMissile].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aMissile[nCntMissile].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aMissile[nCntMissile].fSizeX = MISSILE_SIZE_X;
		g_aMissile[nCntMissile].fSizeY = MISSILE_SIZE_Y;
		g_aMissile[nCntMissile].nTimer = 0;
		g_aMissile[nCntMissile].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMissile(void)
{
	if(g_pD3DTextureMissile != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureMissile->Release();
		g_pD3DTextureMissile = NULL;
	}

	if(g_pD3DVtxBuffMissile != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffMissile->Release();
		g_pD3DVtxBuffMissile = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMissile(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	D3DXVECTOR3 posPlayer;
	// ���f���̈ʒu�擾
	posPlayer = GetPositionPlayer();

	// �v���C���[���擾
	pPlayer = GetPlayer();

	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(g_aMissile[nCntMissile].bUse==true)
		{
			g_aMissile[nCntMissile].pos.x += g_aMissile[nCntMissile].move.x;
			g_aMissile[nCntMissile].pos.y += g_aMissile[nCntMissile].move.y;
			g_aMissile[nCntMissile].pos.z += g_aMissile[nCntMissile].move.z;

			g_aMissile[nCntMissile].nTimer--;
			if(g_aMissile[nCntMissile].nTimer <= 0)
			{
				/*DeleteShadow(g_aMissile[nCntMissile].nIdxShadow);
				g_aMissile[nCntMissile].bUse = false;*/
			}
			else
			{
				//// �e�̈ʒu�ݒ�
				//SetPositionShadow(g_aMissile[nCntMissile].nIdxShadow, D3DXVECTOR3(g_aMissile[nCntMissile].pos.x, 0.1f, g_aMissile[nCntMissile].pos.z));

				// �G�t�F�N�g�̐ݒ�
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
				SetEffect(g_aMissile[nCntMissile].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.0f, 3.0f, 30);
			}
			
			if(g_aMissile[nCntMissile].pos.x < posPlayer.x - 10000.0f
			|| g_aMissile[nCntMissile].pos.x > posPlayer.x + 10000.0f
			|| g_aMissile[nCntMissile].pos.y < posPlayer.y - 10000.0f
			|| g_aMissile[nCntMissile].pos.y > posPlayer.y + 10000.0f
			|| g_aMissile[nCntMissile].pos.z < posPlayer.z - 10000.0f
			|| g_aMissile[nCntMissile].pos.z > posPlayer.z + 10000.0f)
			{
				g_aMissile[nCntMissile].bUse = false;

				//// �����̐���
				//SetExplosion(g_aMissile[nCntMissile].pos, 40.0f, 40.0f);

				DeleteMissile(nCntMissile);

				//// SE�Đ�
				//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			}

			float fSizeX = 8.0f + (g_aMissile[nCntMissile].pos.y - 4.0f) * 0.05f;
			if(fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aMissile[nCntMissile].pos.y - 4.0f) * 0.05f;
			if(fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}

			/*SetVertexShadow(g_aMissile[nCntMissile].nIdxShadow, fSizeX, fSizeY);*/

			float colA = (200.0f - (g_aMissile[nCntMissile].pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
		/*	SetColorShadow(g_aMissile[nCntMissile].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));*/
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMissile(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(g_aMissile[nCntMissile].bUse==true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMissile);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			g_mtxWorldMissile._11 = mtxView._11;
			g_mtxWorldMissile._12 = mtxView._21;
			g_mtxWorldMissile._13 = mtxView._31;
			g_mtxWorldMissile._21 = mtxView._12;
			g_mtxWorldMissile._22 = mtxView._22;
			g_mtxWorldMissile._23 = mtxView._32;
			g_mtxWorldMissile._31 = mtxView._13;
			g_mtxWorldMissile._32 = mtxView._23;
			g_mtxWorldMissile._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aMissile[nCntMissile].scale.x, g_aMissile[nCntMissile].scale.y, g_aMissile[nCntMissile].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldMissile, &g_mtxWorldMissile, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aMissile[nCntMissile].pos.x, g_aMissile[nCntMissile].pos.y, g_aMissile[nCntMissile].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldMissile, &g_mtxWorldMissile, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMissile);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMissile, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureMissile);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntMissile * 4), NUM_POLYGON);
		}
	}

	// ���C�e�B���O��L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexMissile(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_MISSILE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffMissile,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffMissile->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-MISSILE_SIZE_X / 2, -MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(MISSILE_SIZE_X / 2, -MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-MISSILE_SIZE_X / 2, MISSILE_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(MISSILE_SIZE_X / 2, MISSILE_SIZE_Y / 2, 0.0f);

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffMissile->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexMissile(int nIdxMissile, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffMissile->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxMissile * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffMissile->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxMissile = -1;

	for(int nCntMissile = 0; nCntMissile < MAX_MISSILE; nCntMissile++)
	{
		if(!g_aMissile[nCntMissile].bUse)
		{
			g_aMissile[nCntMissile].pos = pos;
			g_aMissile[nCntMissile].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aMissile[nCntMissile].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aMissile[nCntMissile].move = move;
			g_aMissile[nCntMissile].fSizeX = fSizeX;
			g_aMissile[nCntMissile].fSizeY = fSizeY;
			g_aMissile[nCntMissile].nTimer = nTimer;
			g_aMissile[nCntMissile].bUse = true;

			//// �e�̐ݒ�
			//g_aMissile[nCntMissile].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexMissile(nCntMissile, fSizeX, fSizeY);

			nIdxMissile = nCntMissile;

			break;
		}
	}

	return nIdxMissile;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteMissile(int nIdxMissile)
{
	if(nIdxMissile >= 0 && nIdxMissile < MAX_MISSILE)
	{
		/*DeleteShadow(g_aMissile[nIdxMissile].nIdxShadow);*/
		g_aMissile[nIdxMissile].bUse = false;
	}
}

//=============================================================================
// �G�l�~�[�̎擾
//=============================================================================
MISSILE *GetMissile()
{
	return &(g_aMissile[0]);
}
