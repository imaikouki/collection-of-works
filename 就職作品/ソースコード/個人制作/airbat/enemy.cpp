//=============================================================================
//
// �G�l�~�[���f������ [enemy.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "enemy.h"
#include "shadow.h"
#include "game.h"
#include "enemybullet.h"
#include "sound.h"
#include "player.h"
#include "effect.h"
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_BALLOON			"data/MODEL/husen.x"			// �ǂݍ��ރ��f����

#define	VALUE_MOVE			(5.0f)							// �ړ���
#define	VALUE_ROTATE		(D3DX_PI * 0.02f)				// ��]��
#define	VALUE_MOVE_BULLET	(20.5f)							// �e�̈ړ����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static ENEMY				g_Enemy[MAX_ENEMY];				// �G�l�~�[

float move_time = 0;										//�����̎���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* �����_���p�����ݒ� */
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_Enemy[i].use = true;			// �g��

		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		g_Enemy[i].randx = rand() % 10000;
		g_Enemy[i].randy = rand() % 5000;
		g_Enemy[i].randz = rand() % 10000;		g_Enemy[i].randz = rand() % 7000;
		g_Enemy[i].pos = D3DXVECTOR3((FLOAT)g_Enemy[i].randx, (FLOAT)g_Enemy[i].randy, (FLOAT)g_Enemy[i].randz);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_Enemy[i].scl = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

		g_Enemy[i].move = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

		g_Enemy[i].pD3DTexture = NULL;
		g_Enemy[i].pD3DXMesh = NULL;
		g_Enemy[i].pD3DXBuffMat = NULL;
		g_Enemy[i].nNumMat = 0;
		g_Enemy[i].life = 10;
		g_Enemy[i].recnt = 0;
		g_Enemy[i].posplus = 0.0f;
		g_Enemy[i].pospluscnt = 0;
		g_Enemy[i].posplususe = true;

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(MODEL_BALLOON,					// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
			D3DXMESH_SYSTEMMEM,			// ���b�V���̍쐬�I�v�V�������w��
			pDevice,					// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
			NULL,						// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			&g_Enemy[i].pD3DXBuffMat,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			NULL,						// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
			&g_Enemy[i].nNumMat,		// D3DXMATERIAL�\���̂̐�
			&g_Enemy[i].pD3DXMesh)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}

#if 0
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			TEXTURE_FILENAME,				// �t�@�C���̖��O
			&g_Enemy[i].pD3DTexture);		// �ǂݍ��ރ������[
#endif

		//// �e�̏�����
		//D3DXVECTOR3 pos = g_Enemy[i].pos;
		//pos.y = 0.0f;
		//g_Enemy[i].shadowIdx = CreateShadow(pos, g_Enemy[i].scl);

		//g_Enemy[i].tbl_adr = NULL;
		//g_Enemy[i].tbl_cnt = 0;
		//g_Enemy[i].move_time = 0.0f;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].pD3DTexture != NULL)
		{// �e�N�X�`���̊J��
			g_Enemy[i].pD3DTexture->Release();
			g_Enemy[i].pD3DTexture = NULL;
		}

		if (g_Enemy[i].pD3DXMesh != NULL)
		{// ���b�V���̊J��
			g_Enemy[i].pD3DXMesh->Release();
			g_Enemy[i].pD3DXMesh = NULL;
		}

		if (g_Enemy[i].pD3DXBuffMat != NULL)
		{// �}�e���A���̊J��
			g_Enemy[i].pD3DXBuffMat->Release();
			g_Enemy[i].pD3DXBuffMat = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	PLAYER*player = GetPlayer();

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// �g���Ă���Ȃ珈������
		if (g_Enemy[i].use == true)
		{

			// �O�Ԃ����v���C���[���z�[�~���O����悤�ɂ��Ă݂�
			D3DXVECTOR3 pos = GetPlayer()->pos - g_Enemy[i].pos;
			float rot = atan2f(pos.z,pos.x);


			g_Enemy[i].rot.y = atan2f(pos.z, pos.x) - D3DX_PI / 2.0f;

			//D3DXVECTOR3 leng = player->pos - g_Enemy->pos;

			float vleng = D3DXVec3Length(&D3DXVECTOR3(player->pos - g_Enemy->pos));
			
			
				if (g_Enemy[i].posplususe == true)
				{
					g_Enemy[i].posplus += 0.02f;
					g_Enemy[i].pospluscnt += 1;

					if (g_Enemy[i].pospluscnt > 100)
					{
						g_Enemy[i].pospluscnt = 0;
						g_Enemy[i].posplus = 0.0f;
						g_Enemy[i].posplususe = false;
					}
				}
				else if(g_Enemy[i].posplususe == false)
				{
					g_Enemy[i].posplus -= 0.02f;
					g_Enemy[i].pospluscnt += 1;

					if (g_Enemy[i].pospluscnt > 100)
					{
						g_Enemy[i].pospluscnt = 0;
						g_Enemy[i].posplus = 0.0f;
						g_Enemy[i].posplususe = true;
					}
				}
			

			g_Enemy[i].pos.y += g_Enemy[i].posplus;

			//if (0.0f <= vleng < 20.0f && 0.0f > vleng > 20.0f)
			//{
			//	g_Enemy[i].pos.x += cosf(rot) * g_Enemy[i].move.x+pos.x/5000;
			//	g_Enemy[i].pos.y += cosf(rot) * g_Enemy[i].move.y+pos.y/5000;
			//	g_Enemy[i].pos.z += sinf(rot) * g_Enemy[i].move.z+pos.z/5000;
			//}

			//// �e����
			//if (GetKeyboardPress(DIK_SPACE) || IsButtonPressed(0, BUTTON_R2) || IsMouseRightPressed())
			//{
			//	D3DXVECTOR3 pos;
			//	D3DXVECTOR3 move;

			//	pos.x = g_Enemy[i].pos.x - sinf(g_Enemy[i].rot.y) * 10.0f;
			//	pos.y = g_Enemy[i].pos.y;
			//	pos.z = g_Enemy[i].pos.z - cosf(g_Enemy[i].rot.y) * 10.0f;

			//	move.x = -sinf(g_Enemy[i].rot.y) * VALUE_MOVE_BULLET;
			//	move.y = 0.0f;
			//	move.z = -cosf(g_Enemy[i].rot.y) * VALUE_MOVE_BULLET;

			//	SetEnemyBullet(pos, move, 4.0f, 4.0f, 60 * 4);
			//}

		}
		else
		{
			if (g_Enemy[i].recnt < 0)
			{
				g_Enemy[i].recnt--;
			}
			else
			{
				g_Enemy[i].randx = rand() % 10000;
				g_Enemy[i].randy = rand() % 5000;
				g_Enemy[i].randz = rand() % 10000;

				g_Enemy[i].use = true;
				g_Enemy[i].pos = D3DXVECTOR3((FLOAT)g_Enemy[i].randx, 100, (FLOAT)g_Enemy[i].randz);
				g_Enemy[i].life = 10;

			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		// �g���Ă���Ȃ珈������
		if (g_Enemy[i].use == true)
		{
			// �g���Ă��Ȃ��̂Ȃ�R���e�B�j���[����
			if(g_Enemy[i].use == false) continue;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[i].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)g_Enemy[i].pD3DXBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[i].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Enemy[i].pD3DTexture);

				// �`��
				g_Enemy[i].pD3DXMesh->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}

}

//=============================================================================
// �G�l�~�[�̎擾
//=============================================================================
ENEMY *GetEnemy()
{
	return &(g_Enemy[0]);
}
