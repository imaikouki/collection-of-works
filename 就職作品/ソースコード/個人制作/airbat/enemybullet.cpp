//=============================================================================
//
// �G�̒e���� [enemybullet.cpp]
// Author : Imai
//
//=============================================================================
#include "enemybullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "enemy.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ENEMYBULLET			"data/TEXTURE/enemybullet000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//#define	ENEMYBULLET_SIZE_X			(50.0f)							// �r���{�[�h�̕�
//#define	ENEMYBULLET_SIZE_Y			(50.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_ENEMYBULLET		(2.0f)							// �ړ����x

#define ENEMYBULLETMAXPOS			(2000)							//�e�̓����͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEnemyBullet(int nIdxEnemyBullet, float fSizeX, float fSizeY);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureEnemyBullet = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEnemyBullet = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldEnemyBullet;				// ���[���h�}�g���b�N�X

ENEMYBULLET					g_aEnemyBullet[MAX_ENEMYBULLET];			// �e���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexEnemyBullet(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_ENEMYBULLET,				// �t�@�C���̖��O
								&g_pD3DTextureEnemyBullet);	// �ǂݍ��ރ������[

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		g_aEnemyBullet[nCntEnemyBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEnemyBullet[nCntEnemyBullet].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEnemyBullet[nCntEnemyBullet].fSizeX = ENEMYBULLET_SIZE_X;
		g_aEnemyBullet[nCntEnemyBullet].fSizeY = ENEMYBULLET_SIZE_Y;
		g_aEnemyBullet[nCntEnemyBullet].nTimer = 0;
		g_aEnemyBullet[nCntEnemyBullet].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyBullet(void)
{
	if(g_pD3DTextureEnemyBullet != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureEnemyBullet->Release();
		g_pD3DTextureEnemyBullet = NULL;
	}

	if(g_pD3DVtxBuffEnemyBullet != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEnemyBullet->Release();
		g_pD3DVtxBuffEnemyBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyBullet(void)
{
	// �G�l�~�[���擾
	ENEMY *enemy = GetEnemy();

	D3DXVECTOR3 rotCamera;


	// �J�����̉�]���擾
	rotCamera = GetRotCamera();

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos.x += g_aEnemyBullet[nCntEnemyBullet].move.x;
			g_aEnemyBullet[nCntEnemyBullet].pos.z += g_aEnemyBullet[nCntEnemyBullet].move.z;

			g_aEnemyBullet[nCntEnemyBullet].nTimer--;
			if(g_aEnemyBullet[nCntEnemyBullet].nTimer <= 0)
			{
				/*DeleteShadow(g_aEnemyBullet[nCntEnemyBullet].nIdxShadow);
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;*/
			}
			else
			{
				//// �e�̈ʒu�ݒ�
				//SetPositionShadow(g_aEnemyBullet[nCntEnemyBullet].nIdxShadow, D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, 0.1f, g_aEnemyBullet[nCntEnemyBullet].pos.z));

				//// �G�t�F�N�g�̐ݒ�
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);
				//SetEffect(g_aEnemyBullet[nCntEnemyBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				//					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);
			}

			//if(g_aEnemyBullet[nCntEnemyBullet].pos.x < enemy->pos.x - ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.x > enemy->pos.x + ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.z < enemy->pos.z - ENEMYBULLETMAXPOS
			//|| g_aEnemyBullet[nCntEnemyBullet].pos.z > enemy->pos.z + ENEMYBULLETMAXPOS)
			//{
			//	g_aEnemyBullet[nCntEnemyBullet].bUse = false;

			//	//// �����̐���
			//	//SetExplosion(g_aEnemyBullet[nCntEnemyBullet].pos, 40.0f, 40.0f);

			//	//DeleteEnemyBullet(nCntEnemyBullet);

			//	//// SE�Đ�
			//	//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			//}

			if(g_aEnemyBullet[nCntEnemyBullet].pos.x - ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.x + ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.z - ENEMYBULLETMAXPOS
			|| g_aEnemyBullet[nCntEnemyBullet].pos.z + ENEMYBULLETMAXPOS)
			{
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;

			}

			float fSizeX = 8.0f + (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f) * 0.05f;
			if(fSizeX < 8.0f)
			{
				fSizeX = 8.0f;
			}
			float fSizeY = 8.0f + (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f) * 0.05f;
			if(fSizeY < 8.0f)
			{
				fSizeY = 8.0f;
			}

			float colA = (200.0f - (g_aEnemyBullet[nCntEnemyBullet].pos.y - 4.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ���C�e�B���O�𖳌���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEnemyBullet);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetMtxView();

			g_mtxWorldEnemyBullet._11 = mtxView._11;
			g_mtxWorldEnemyBullet._12 = mtxView._21;
			g_mtxWorldEnemyBullet._13 = mtxView._31;
			g_mtxWorldEnemyBullet._21 = mtxView._12;
			g_mtxWorldEnemyBullet._22 = mtxView._22;
			g_mtxWorldEnemyBullet._23 = mtxView._32;
			g_mtxWorldEnemyBullet._31 = mtxView._13;
			g_mtxWorldEnemyBullet._32 = mtxView._23;
			g_mtxWorldEnemyBullet._33 = mtxView._33;

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, g_aEnemyBullet[nCntEnemyBullet].scale.x, g_aEnemyBullet[nCntEnemyBullet].scale.y, g_aEnemyBullet[nCntEnemyBullet].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemyBullet, &g_mtxWorldEnemyBullet, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemyBullet, &g_mtxWorldEnemyBullet, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemyBullet);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEnemyBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureEnemyBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEnemyBullet * 4), NUM_POLYGON);
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
HRESULT MakeVertexEnemyBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_ENEMYBULLET,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,							// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,								// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,							// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffEnemyBullet,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))										// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-ENEMYBULLET_SIZE_X / 2, -ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ENEMYBULLET_SIZE_X / 2, -ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-ENEMYBULLET_SIZE_X / 2, ENEMYBULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ENEMYBULLET_SIZE_X / 2, ENEMYBULLET_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemyBullet(int nIdxEnemyBullet, float fSizeX, float fSizeY)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEnemyBullet * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEnemyBullet->Unlock();
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxEnemyBullet = -1;

	for(int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if(!g_aEnemyBullet[nCntEnemyBullet].bUse)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos = pos;
			g_aEnemyBullet[nCntEnemyBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyBullet[nCntEnemyBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aEnemyBullet[nCntEnemyBullet].move = move;
			g_aEnemyBullet[nCntEnemyBullet].fSizeX = fSizeX;
			g_aEnemyBullet[nCntEnemyBullet].fSizeY = fSizeY;
			g_aEnemyBullet[nCntEnemyBullet].nTimer = nTimer;
			g_aEnemyBullet[nCntEnemyBullet].bUse = true;

			//// �e�̐ݒ�
			//g_aEnemyBullet[nCntEnemyBullet].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// �e�̐ݒ�

			// ���_���W�̐ݒ�
			SetVertexEnemyBullet(nCntEnemyBullet, fSizeX, fSizeY);

			nIdxEnemyBullet = nCntEnemyBullet;

			break;
		}
	}

	return nIdxEnemyBullet;
}

//=============================================================================
// �e�̍폜
//=============================================================================
void DeleteEnemyBullet(int nIdxEnemyBullet)
{
	if(nIdxEnemyBullet >= 0 && nIdxEnemyBullet < MAX_ENEMYBULLET)
	{
		/*DeleteShadow(g_aEnemyBullet[nIdxEnemyBullet].nIdxShadow);*/
		g_aEnemyBullet[nIdxEnemyBullet].bUse = false;
	}
}

//=============================================================================
// �G�l�~�[�̎擾
//=============================================================================
ENEMYBULLET *GetEnemyBullet()
{
	return &(g_aEnemyBullet[0]);
}