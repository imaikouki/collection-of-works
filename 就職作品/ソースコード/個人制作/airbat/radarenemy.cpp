//=============================================================================
//
// ���[�_�[�G���� [enemy.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "radarenemy.h"
#include "player.h"
#include "enemybullet.h"
#include "enemy.h"
#include "radar.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRadarEnemy( int no );
void SetTextureRadarEnemy( int no, int cntPattern );
void SetVertexRadarEnemy( int no );
int e_pos = 30;
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureRadarEnemy = NULL;		// �e�N�X�`���ւ̃|���S��

static RADARENEMY					g_RadarEnemy[MAX_ENEMY];				// �G�l�~�[�\����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRadarEnemy(int type)
{

		LPDIRECT3DDEVICE9	pDevice = GetDevice();

		// �e�N�X�`���[�̏��������s���H
		if (type == 0)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�̃|�C���^
				RADARENEMY_TEXTURE,										// �t�@�C���̖��O
				&g_pD3DTextureRadarEnemy);								// �ǂݍ��ރ������̃|�C���^
		}


		// �G�l�~�[�̏���������
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			g_RadarEnemy[i].use = true;										// �g�p
			g_RadarEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
			g_RadarEnemy[i].ppos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
			g_RadarEnemy[i].vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���W�f�[�^��������
			g_RadarEnemy[i].distance = 0.0f;
			g_RadarEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]�f�[�^��������
			g_RadarEnemy[i].PatternAnim = 0;									// �A�j���p�^�[���ԍ��������_���ŏ�����
			g_RadarEnemy[i].CountAnim = 0;									// �A�j���J�E���g��������

			D3DXVECTOR2 temp = D3DXVECTOR2(RADARENEMY_TEXTURE_SIZE_X, RADARENEMY_TEXTURE_SIZE_Y);
			g_RadarEnemy[i].Radius = D3DXVec2Length(&temp);					// �G�l�~�[�̔��a��������
			g_RadarEnemy[i].BaseAngle = atan2f(RADARENEMY_TEXTURE_SIZE_Y, RADARENEMY_TEXTURE_SIZE_X);	// �G�l�~�[�̊p�x��������
			g_RadarEnemy[i].Texture = g_pD3DTextureRadarEnemy;
			MakeVertexRadarEnemy(i);											// ���_���̍쐬
		}
	

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRadarEnemy(void)
{
		if (g_pD3DTextureRadarEnemy != NULL)
		{	// �e�N�X�`���̊J��
			g_pD3DTextureRadarEnemy->Release();
			g_pD3DTextureRadarEnemy = NULL;
		}
	
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRadarEnemy(void)
{

	ENEMY*enemy = GetEnemy();		// �G�l�~�[�̃|�C���^�[��������
	PLAYER*player = GetPlayer();	//�v���C���[�̃|�C���^�[��������

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//�v���C���[�ƓG�̈ʒu���v�Z
		g_RadarEnemy[i].ppos = (player->pos - enemy[i].pos) / 300;
		//g_RadarEnemy[i].vec = Transform(D3DXVECTOR3(g_RadarEnemy[i].ppos.x,0.0f,g_RadarEnemy[i].ppos.z), player->quorot);
		g_RadarEnemy[i].vec = Transform(D3DXVECTOR3(g_RadarEnemy[i].ppos.x, g_RadarEnemy[i].ppos.y, g_RadarEnemy[i].ppos.z), player->quorot);
		g_RadarEnemy[i].distance = D3DXVec2Length(&D3DXVECTOR2(g_RadarEnemy[i].ppos.x, g_RadarEnemy[i].ppos.z));

			//if (g_RadarEnemy[i]. distance <= 25.0f)
			{
				if (enemy[i].use == true)
				{
					g_RadarEnemy[i].pos.x = g_RadarEnemy[i].vec.x;
					g_RadarEnemy[i].pos.y = g_RadarEnemy[i].vec.z;
					g_RadarEnemy[i].pos.z = g_RadarEnemy[i].vec.y;

					SetVertexRadarEnemy(i);							// �ړ���̍��W�Œ��_��ݒ�
				}
			}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRadarEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_RadarEnemy[i].distance <= 35.0f)
		{
			if (g_RadarEnemy[i].use == true)			// �g�p���Ă����ԂȂ�`�悷��
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_RadarEnemy[i].Texture);

				// �|���S���̕`��
				pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_RadarEnemy[i].vertexWk, sizeof(VERTEX_2D));
			}
		}
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRadarEnemy( int i )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		// ���_���W�̐ݒ�
		SetVertexRadarEnemy(i);

		// rhw�̐ݒ�
		g_RadarEnemy[i].vertexWk[0].rhw =
			g_RadarEnemy[i].vertexWk[1].rhw =
			g_RadarEnemy[i].vertexWk[2].rhw =
			g_RadarEnemy[i].vertexWk[3].rhw = 1.0f;

			g_RadarEnemy[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_RadarEnemy[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_RadarEnemy[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_RadarEnemy[i].vertexWk[1].tex = D3DXVECTOR2(1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X, 0.0f);
		g_RadarEnemy[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y);
		g_RadarEnemy[i].vertexWk[3].tex = D3DXVECTOR2(1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X, 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRadarEnemy( int i, int cntPattern )
{
		// �e�N�X�`�����W�̐ݒ�
		int x = cntPattern % RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		int y = cntPattern / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeX = 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_X;
		float sizeY = 1.0f / RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y;

		g_RadarEnemy[i].vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		g_RadarEnemy[i].vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		g_RadarEnemy[i].vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		g_RadarEnemy[i].vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexRadarEnemy( int i )
{
	// ���_���W�̐ݒ�
	g_RadarEnemy[i].vertexWk[0].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x - RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y - RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[1].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x + RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y - RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[2].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x - RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y + RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
	g_RadarEnemy[i].vertexWk[3].vtx = D3DXVECTOR3(NX + g_RadarEnemy[i].pos.x + RADARENEMY_TEXTURE_SIZE_X, NY + g_RadarEnemy[i].pos.y + RADARENEMY_TEXTURE_SIZE_Y, 0.0f);
}


