//=============================================================================
//
// �R�b�N�s�b�g���� [cockpit.cpp]
// Author : Imai
//
//=============================================================================
#include "cockpit.h"
#include "fade.h"
#include "camera.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FRAME_COCKPIT	"data/TEXTURE/cockpit.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME_COCKPIT2	"data/TEXTURE/rokku.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	COCKPIT_SIZE_X		(35.0f)							// �^�C�}�[�̐����̕�
#define	COCKPIT_SIZE_Y		(50.0f)							// �^�C�}�[�̐����̍���
#define	COCKPIT_INTERVAL_X	(0.0f)							// �^�C�}�[�̐����̕\���Ԋu

#define	NUM_PLACE			(3)			// �^�C�}�[�̌���

#define	COCKPIT_POS_X			(SCREEN_WIDTH / 2 - ((COCKPIT_SIZE_X * NUM_PLACE + COCKPIT_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// �^�C�}�[�̕\����ʒu�w���W
#define	COCKPIT_POS_Y			(25.0f)																						// �^�C�}�[�̕\����ʒu�x���W

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice);
void SetTextureCockpit(int idx, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit[2] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureCockpit2[2] = {};		// �e�N�X�`���ւ̃|�C���^

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffCockpit2 = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				g_posCockpit;
D3DXVECTOR3				g_rotCockpit;

int						g_nCockpit;						// �R�b�N�s�b�g
bool					g_bEnableCockpit;					// �R�b�N�s�b�g����ON/OFF

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCockpit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posCockpit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCockpit = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �R�b�N�s�b�g�̏�����
	g_nCockpit = 30 * 60;
	g_bEnableCockpit = true;

	// ���_���̍쐬
	MakeVertexCockpit(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FRAME_COCKPIT,			// �t�@�C���̖��O
								&g_pD3DTextureCockpit[0]);	// �ǂݍ��ރ������[

// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FRAME_COCKPIT2,			// �t�@�C���̖��O
								&g_pD3DTextureCockpit2[0]);	// �ǂݍ��ރ������[	
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCockpit(void)
{
	if(g_pD3DTextureCockpit[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCockpit[0]->Release();
		g_pD3DTextureCockpit[0] = NULL;
	}
	if(g_pD3DTextureCockpit[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCockpit[1]->Release();
		g_pD3DTextureCockpit[1] = NULL;
	}

	if (g_pD3DTextureCockpit2[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCockpit2[0]->Release();
		g_pD3DTextureCockpit2[0] = NULL;
	}
	if (g_pD3DTextureCockpit2[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureCockpit2[1]->Release();
		g_pD3DTextureCockpit2[1] = NULL;
	}

	if(g_pD3DVtxBuffCockpit != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffCockpit->Release();
		g_pD3DVtxBuffCockpit = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCockpit(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCockpit(void)
{
	CAMERA*camera = GetCamera();

	if (camera->fpsmode == true)
	{
		if (GetKeyboardPress(DIK_G)==true || !IsButtonPressed(0, BUTTON_CROSS_UP)==true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureCockpit[0]);

			// �|���S���̕`��
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureCockpit[1]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
		}
	}
	else 
	{
		if (GetKeyboardPress(DIK_G) == true || !IsButtonPressed(0, BUTTON_CROSS_UP) == true)
		{



			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffCockpit2, 0, sizeof(VERTEX_2D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureCockpit2[0]);

			// �|���S���̕`��
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureCockpit2[1]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCockpit(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pD3DVtxBuffCockpit,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))											// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffCockpit->Unlock();
	}

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffCockpit2,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffCockpit2->Lock(0, 0, (void**)&pVtx, 0);

		//// ���_���W�̐ݒ�
		//pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		//pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		//pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

				// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2- 50, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH/2+ 50, SCREEN_HEIGHT/2- 50, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(SCREEN_WIDTH/2- 50, SCREEN_HEIGHT/2+ 50, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH/2+ 50, SCREEN_HEIGHT/2+ 50, 0.0f);


		// rhw�̐ݒ�
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffCockpit2->Unlock();
	}


	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureCockpit(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffCockpit->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffCockpit2->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffCockpit2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffCockpit2->Unlock();

}
