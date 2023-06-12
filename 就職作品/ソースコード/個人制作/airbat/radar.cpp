//=============================================================================
//
// ���[�_�[���� [radar.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "radar.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRadar(void);
void SetVertexBou(void);
void SetTextureRadar(void);
void SetVertexRadr(void);

static RADAR radar;
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRadar = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRadarBou = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkRadar[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkRadarBou[NUM_VERTEX];		// ���_���i�[���[�N
int radarbgmcnt = 0;

#define RADARBOU_SIZE_X		(90.0f)		//���[�_�[�_�̃T�C�Y		
#define RADARBOU_SIZE_Y		(90.0f)		//���[�_�[�_�̃T�C�Y
//=============================================================================
// ����������
//=============================================================================
HRESULT InitRadar(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	radar.pos = D3DXVECTOR3(SCREEN_WIDTH- RADARBOU_SIZE_X/2, SCREEN_HEIGHT - RADARBOU_SIZE_X/2, 0.0f);
	radar.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 temp = D3DXVECTOR2(90.0f, 90.0f);
	radar.Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
	radar.BaseAngle = atan2f(90.0f, 90.0f);	// �G�l�~�[�̊p�x��������
	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RADAR,				// �t�@�C���̖��O
			&g_pD3DTextureRadar);		// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RADAR_LOGO,			// �t�@�C���̖��O
			&g_pD3DTextureRadarBou);	// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexRadar();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRadar(void)
{
	if (g_pD3DTextureRadar != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRadar->Release();
		g_pD3DTextureRadar = NULL;
	}

	if (g_pD3DTextureRadarBou != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRadarBou->Release();
		g_pD3DTextureRadarBou = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRadar(void)
{
	radar.rot.z += 0.01f;
	SetVertexRadr();						// �ړ���̍��W�Œ��_��ݒ�
	//// �e�N�X�`�����W��ݒ�
	//SetTextureRadar();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRadar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRadar);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRadar, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRadarBou);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRadarBou, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRadar(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkRadar[0].vtx = D3DXVECTOR3(SCREEN_WIDTH-90.0f,SCREEN_HEIGHT - 90.0f, 0.0f);
	g_vertexWkRadar[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - 90.0f, 0.0f);
	g_vertexWkRadar[2].vtx = D3DXVECTOR3(SCREEN_WIDTH-90.0f, SCREEN_HEIGHT, 0.0f);
	g_vertexWkRadar[3].vtx = D3DXVECTOR3(SCREEN_WIDTH ,SCREEN_HEIGHT, 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRadar[0].rhw =
		g_vertexWkRadar[1].rhw =
		g_vertexWkRadar[2].rhw =
		g_vertexWkRadar[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRadar[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadar[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRadar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRadar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRadar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRadar[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	//SetVertexRadr();

	// ���_���W�̐ݒ�
	g_vertexWkRadarBou[0].vtx = D3DXVECTOR3(radar.pos.x- RADARBOU_SIZE_X/2.0f, radar.pos.y - RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[1].vtx = D3DXVECTOR3(radar.pos.x+ RADARBOU_SIZE_X/2.0f, radar.pos.y - RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[2].vtx = D3DXVECTOR3(radar.pos.x - RADARBOU_SIZE_X/2.0f, radar.pos.y + RADARBOU_SIZE_Y/2.0f, 0.0f);
	g_vertexWkRadarBou[3].vtx = D3DXVECTOR3(radar.pos.x + RADARBOU_SIZE_X/2.0f, radar.pos.x + RADARBOU_SIZE_Y/2.0f, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRadarBou[0].rhw =
		g_vertexWkRadarBou[1].rhw =
		g_vertexWkRadarBou[2].rhw =
		g_vertexWkRadarBou[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRadarBou[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRadarBou[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRadarBou[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRadarBou[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRadarBou[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRadarBou[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRadar(void)
{

		//// �e�N�X�`�����W�̐ݒ�
		//int x = 0;
		//int y = 0;
		//float sizeX = 1.0f;
		//float sizeY = 1.0f;

		//g_vertexWkRadarBou[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		//g_vertexWkRadarBou[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		//g_vertexWkRadarBou[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		//g_vertexWkRadarBou[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexRadr(void)
{
	// ���_���W�̐ݒ�
	g_vertexWkRadarBou[0].vtx.x = radar.pos.x - cosf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[0].vtx.y = radar.pos.y - sinf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[0].vtx.z = 0.0f;

	g_vertexWkRadarBou[1].vtx.x = radar.pos.x + cosf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[1].vtx.y = radar.pos.y - sinf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[1].vtx.z = 0.0f;

	g_vertexWkRadarBou[2].vtx.x = radar.pos.x - cosf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[2].vtx.y = radar.pos.y + sinf(radar.BaseAngle - radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[2].vtx.z = 0.0f;

	g_vertexWkRadarBou[3].vtx.x = radar.pos.x + cosf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[3].vtx.y = radar.pos.y + sinf(radar.BaseAngle + radar.rot.z) * radar.Radius;
	g_vertexWkRadarBou[3].vtx.z = 0.0f;

	// ���_���W�̐ݒ�
	//g_vertexWkRadar[0].vtx.x = 0.0f;
	//g_vertexWkRadar[0].vtx.y = 0.0f;
	//g_vertexWkRadar[0].vtx.z = 0.0f;

	//g_vertexWkRadar[1].vtx.x = 0.0f+100.0f;
	//g_vertexWkRadar[1].vtx.y = 0.0f;
	//g_vertexWkRadar[1].vtx.z = 0.0f;

	//g_vertexWkRadar[2].vtx.x = 0.0f;
	//g_vertexWkRadar[2].vtx.y = 0.0f+100.0f;
	//g_vertexWkRadar[2].vtx.z = 0.0f;

	//g_vertexWkRadar[3].vtx.x = 0.0f+100.0f;
	//g_vertexWkRadar[3].vtx.y = 0.0f+100.0f;
	//g_vertexWkRadar[3].vtx.z = 0.0f;

}

