//=============================================================================
//
// �|���S������ [ranking.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "score.h"
#include "ranking.h"
#include "titleselection.h"
#include "input.h"
#include "getScore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRankingScore(void);
void SetTextureRankingScore(void);
void SetVertexRankingScore(void);

void SortRanking(void);

HRESULT MakeVertexRankingBG(void);
void SetVertexRankingBG(void);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
/*���X�R�A*/
RANKINGNUM g_rankingNum[RANKINGSCORE_DIGITS][RANKING_MAX];
RANKINGNUM g_rank[RANKING_MAX];

static LPDIRECT3DTEXTURE9	g_pD3DTextureRankingScore = NULL;		// �e�N�X�`���̃|�C���^
static LPDIRECT3DTEXTURE9	g_pD3DTextureRankingBG = NULL;

static D3DXVECTOR3			g_posRankingBG;

static VERTEX_2D			g_vertexWkRankingBG[NUM_VERTEX];

int							g_rankingScore[RANKING_MAX];			// �����L���O�p�X�R�A�ۑ�

bool						g_appearRanking = false;				// �����L���O��\�����邩�ۂ�
//=============================================================================
// ����������
//=============================================================================
HRESULT InitRankingScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���  
	if (type == 0)	// ����̂ݓǂݍ���
	{
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANKINGSCORE,				// �t�@�C���̖��O
			&g_pD3DTextureRankingScore);			// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANKINGBG,				// �t�@�C���̖��O
			&g_pD3DTextureRankingBG);			// �ǂݍ��ރ������̃|�C���^

		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK1,				// �t�@�C���̖��O
			&g_rank[0].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK2,				// �t�@�C���̖��O
			&g_rank[1].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK3,				// �t�@�C���̖��O
			&g_rank[2].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK4,				// �t�@�C���̖��O
			&g_rank[3].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK5,				// �t�@�C���̖��O
			&g_rank[4].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK6,				// �t�@�C���̖��O
			&g_rank[5].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK7,				// �t�@�C���̖��O
			&g_rank[6].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK8,				// �t�@�C���̖��O
			&g_rank[7].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK9,				// �t�@�C���̖��O
			&g_rank[8].texture);			// �ǂݍ��ރ������̃|�C���^
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_RANK10,				// �t�@�C���̖��O
			&g_rank[9].texture);			// �ǂݍ��ރ������̃|�C���^


		// �����L���O�X�R�A�̏�����
		for (int i = 0; i < RANKING_MAX; i++)
		{
			g_rankingScore[i] = 0;
		}
	}

	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			g_rankingNum[i][j].texture = g_pD3DTextureRankingScore;					// �e�N�X�`���̓ǂݍ���
			g_rankingNum[i][j].pos = D3DXVECTOR3(FIRST_RANKINGSCORE_POS_X + TEXTURE_RANKINGSCORE_SIZE_X * 2 * ((RANKINGSCORE_DIGITS - i) + 1),
				FIRST_RANKINGSCORE_POS_Y + (RANKINGSCORE_INTERVAL_Y * j), 0.0f);	// �ʒu���W�̐ݒ�
			g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].pos = D3DXVECTOR3(RANK_POS_X, g_rankingNum[0][i].pos.y, 0.0f);
		g_rank[i].oldPos = g_rank[i].pos;
	}

	g_posRankingBG = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y, 0.0f);
	g_appearRanking = false;

	MakeVertexRankingScore();
	MakeVertexRankingBG();

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitRankingScore(void)
{
	if (g_pD3DTextureRankingScore != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureRankingScore->Release();
		g_pD3DTextureRankingScore = NULL;
	}

	if (g_pD3DTextureRankingBG != NULL)
	{
		g_pD3DTextureRankingBG->Release();
		g_pD3DTextureRankingBG = NULL;
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		if (g_rank[i].texture != NULL)
		{
			g_rank[i].texture->Release();
			g_rank[i].texture = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRankingScore(void)
{
	ARROW *arrow = GetArrow();

	// �f�o�b�O�p
	if (GetKeyboardTrigger(DIK_A))
	{
		if (g_appearRanking == false)
		{
			g_appearRanking = true;
		}
		else if (g_appearRanking == true)
		{
			g_appearRanking = false;
		}
	}

	/*�����L���O���\������Ă��邩�ۂ�*/
	if (arrow->isRanked == true)
	{
		g_appearRanking = true;
	}
	else
	{
		g_appearRanking = false;
	}

	/*�v���C���[�̓��͂ŕ������ړ�*/
	if (g_appearRanking == true)
	{
		if (GetKeyboardPress(DIK_UP) || IsButtonPressed(0, BUTTON_UP))
		{
			/*�������ړ�*/
			for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
			{
				for (int j = 0; j < RANKING_MAX; j++)
				{
					g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
					g_rankingNum[i][j].pos.y += 3.0f;

					if (g_rankingNum[i][0].pos.y >= FIRST_RANKINGSCORE_POS_Y)
					{
						g_rankingNum[i][j].pos = g_rankingNum[i][j].oldPos;
						g_rankingNum[i][0].pos.y = FIRST_RANKINGSCORE_POS_Y;
					}
				}
			}

			/*���ʂ̕������ړ�*/
			for (int i = 0; i < RANKING_MAX; i++)
			{
				g_rank[i].pos.y = g_rankingNum[0][i].pos.y;
			}
		}
		if (GetKeyboardPress(DIK_DOWN) || IsButtonPressed(0, BUTTON_DOWN))
		{
			/*�������ړ�*/
			for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
			{
				for (int j = 0; j < RANKING_MAX; j++)
				{
					g_rankingNum[i][j].oldPos = g_rankingNum[i][j].pos;
					g_rankingNum[i][j].pos.y -= 3.0f;

					if (g_rankingNum[i][9].pos.y <= LAST_RANKINGSCORE_POS_Y)
					{
						g_rankingNum[i][j].pos = g_rankingNum[i][j].oldPos;
						g_rankingNum[i][9].pos.y = LAST_RANKINGSCORE_POS_Y;
					}
				}
			}

			/*���ʂ̕������ړ�*/
			for (int i = 0; i < RANKING_MAX; i++)
			{
				g_rank[i].pos.y = g_rankingNum[0][i].pos.y;
			}
		}

	}

	SortRanking();

	SetTextureRankingScore();

	SetVertexRankingScore();
}


//=============================================================================
// �X�R�A�`�揈��
//=============================================================================
void DrawRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_appearRanking == true)
	{
		// �����L���O�̔w�i
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		// �e�N�X�`���̐ݒ� 
		pDevice->SetTexture(0, g_pD3DTextureRankingBG);
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRankingBG, sizeof(VERTEX_2D));


		// �X�R�A�̐���
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
		{
			for (int j = 0; j < RANKING_MAX; j++)
			{
				//if (g_rankingNum[i][j].pos.y >= RANKING_BG_POS_Y + TEXTURE_RANKINGSCORE_SIZE_Y
				//	&& g_rankingNum[i][j].pos.y <= RANKING_BG_POS_Y + RANKING_BG_SIZE_Y - TEXTURE_RANKINGSCORE_SIZE_Y)
				{
					// �e�N�X�`���̐ݒ� 
					pDevice->SetTexture(0, g_rankingNum[i][j].texture);

					// �|���S���̕`��
					pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rankingNum[i][j].vertexWk, sizeof(VERTEX_2D));
				}
			}
		}

		// ���ʂ̕���
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);
		for (int i = 0; i < RANKING_MAX; i++)
		{
			// �e�N�X�`���̐ݒ� 
			pDevice->SetTexture(0, g_rank[i].texture);
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_rank[i].vertexWk, sizeof(VERTEX_2D));
		}
	}
}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRankingScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexRankingScore();

	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			// �����̒��_���W�̐ݒ�
			g_rankingNum[i][j].vertexWk[0].rhw =
				g_rankingNum[i][j].vertexWk[1].rhw =
				g_rankingNum[i][j].vertexWk[2].rhw =
				g_rankingNum[i][j].vertexWk[3].rhw = 1.0f;

			g_rankingNum[i][j].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_rankingNum[i][j].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_rankingNum[i][j].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_rankingNum[i][j].vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_RANK_X, 0.0f);
			g_rankingNum[i][j].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_RANK_Y);
			g_rankingNum[i][j].vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_RANK_X, 1.0f / TEXTURE_PATTERN_DIVIDE_RANK_Y);
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].rhw =
			g_rank[i].vertexWk[1].rhw =
			g_rank[i].vertexWk[2].rhw =
			g_rank[i].vertexWk[3].rhw = 1.0f;

		g_rank[i].vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_rank[i].vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_rank[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_rank[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_rank[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_rank[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}

HRESULT MakeVertexRankingBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexRankingBG();

	g_vertexWkRankingBG[0].rhw =
		g_vertexWkRankingBG[1].rhw =
		g_vertexWkRankingBG[2].rhw =
		g_vertexWkRankingBG[3].rhw = 1.0f;

	g_vertexWkRankingBG[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);
	g_vertexWkRankingBG[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 127);

	g_vertexWkRankingBG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRankingBG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRankingBG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRankingBG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRankingScore(void)
{
	static int rankingScore[RANKING_MAX];
	for (int i = 0; i < RANKING_MAX; i++)
	{
		rankingScore[i] = g_rankingScore[i];
	}
	float numAboveHeight[RANKING_MAX];			// �����̕\���͈�(��ɂ��鎞�A�����̏オ����)
	float numBellowHeight[RANKING_MAX];			// ����(���ɂ��鎞�A�����̉�������)

	/*�����̕\���͈͂̐ݒ�*/
	for (int i = 0; i < RANKING_MAX; i++)
	{
		numAboveHeight[i] = (g_rankingNum[0][i].pos.y - RANKING_BG_POS_Y - BG_NUM_DIFFER_ABOVE) / TEXTURE_RANKINGSCORE_SIZE_Y;
		if (numAboveHeight[i] >= 1.0f)
		{
			numAboveHeight[i] = 1.0f;
		}
		else if (numAboveHeight[i] <= 0.0f)
		{
			numAboveHeight[i] = 0.0f;
		}
		numAboveHeight[i] = 1.0f - numAboveHeight[i];


		numBellowHeight[i] = (RANKING_BG_POS_Y + RANKING_BG_SIZE_Y - BG_NUM_DIFFER_BELLOW - g_rankingNum[0][i].pos.y) / TEXTURE_RANKINGSCORE_SIZE_Y;
		if (numBellowHeight[i] >= 1.0f)
		{
			numBellowHeight[i] = 1.0f;
		}
		else if (numBellowHeight[i] <= 0.0f)
		{
			numBellowHeight[i] = 0.0f;
		}
	}

	// �e�N�X�`�����W�̐ݒ�
	for (int i = 0; i < RANKING_MAX; i++)
	{
		for (int j = 0; j < RANKINGSCORE_DIGITS; j++)
		{
			/*���X�R�A*/
			float tx = (float)(rankingScore[i] % 10) - 1.0f;		//10�Ŋ��������܂肪���̌��̐����ɂȂ�

			g_rankingNum[j][i].vertexWk[0].tex = D3DXVECTOR2(tx * 0.1f, 0.0f + numAboveHeight[i]);
			g_rankingNum[j][i].vertexWk[1].tex = D3DXVECTOR2((tx + 1) *0.1f, 0.0f + numAboveHeight[i]);
			g_rankingNum[j][i].vertexWk[2].tex = D3DXVECTOR2(tx * 0.1f, numBellowHeight[i]);
			g_rankingNum[j][i].vertexWk[3].tex = D3DXVECTOR2((tx + 1) * 0.1f, numBellowHeight[i]);

			//g_rankingNum[j][i].vertexWk[0].tex = D3DXVECTOR2(tx * 0.1f, 0.0f);
			//g_rankingNum[j][i].vertexWk[1].tex = D3DXVECTOR2((tx + 1) *0.1f, 0.0f);
			//g_rankingNum[j][i].vertexWk[2].tex = D3DXVECTOR2(tx * 0.1f, 1.0f);
			//g_rankingNum[j][i].vertexWk[3].tex = D3DXVECTOR2((tx + 1) * 0.1f, 1.0f);

			rankingScore[i] /= 10;							//�����E�Ɉ�ړ�
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].tex = D3DXVECTOR2(0.0f, numAboveHeight[i]);
		g_rank[i].vertexWk[1].tex = D3DXVECTOR2(1.0f, numAboveHeight[i]);
		g_rank[i].vertexWk[2].tex = D3DXVECTOR2(0.0f, numBellowHeight[i]);
		g_rank[i].vertexWk[3].tex = D3DXVECTOR2(1.0f, numBellowHeight[i]);
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexRankingScore(void)
{
	/*�����̃e�N�X�`��*/
	for (int i = 0; i < RANKINGSCORE_DIGITS; i++)
	{
		for (int j = 0; j < RANKING_MAX; j++)
		{
			/*���X�R�A*/
			g_rankingNum[i][j].vertexWk[0].vtx.x = g_rankingNum[i][j].pos.x - TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[0].vtx.y = g_rankingNum[i][j].pos.y - TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[0].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[1].vtx.x = g_rankingNum[i][j].pos.x + TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[1].vtx.y = g_rankingNum[i][j].pos.y - TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[1].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[2].vtx.x = g_rankingNum[i][j].pos.x - TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[2].vtx.y = g_rankingNum[i][j].pos.y + TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[2].vtx.z = 0.0f;

			g_rankingNum[i][j].vertexWk[3].vtx.x = g_rankingNum[i][j].pos.x + TEXTURE_RANKINGSCORE_SIZE_X;
			g_rankingNum[i][j].vertexWk[3].vtx.y = g_rankingNum[i][j].pos.y + TEXTURE_RANKINGSCORE_SIZE_Y;
			g_rankingNum[i][j].vertexWk[3].vtx.z = 0.0f;
		}
	}

	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_rank[i].vertexWk[0].vtx.x = g_rank[i].pos.x - TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[0].vtx.y = g_rank[i].pos.y - TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[0].vtx.z = 0.0f;

		g_rank[i].vertexWk[1].vtx.x = g_rank[i].pos.x + TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[1].vtx.y = g_rank[i].pos.y - TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[1].vtx.z = 0.0f;

		g_rank[i].vertexWk[2].vtx.x = g_rank[i].pos.x - TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[2].vtx.y = g_rank[i].pos.y + TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[2].vtx.z = 0.0f;

		g_rank[i].vertexWk[3].vtx.x = g_rank[i].pos.x + TEXTURE_RANK_SIZE_X;
		g_rank[i].vertexWk[3].vtx.y = g_rank[i].pos.y + TEXTURE_RANK_SIZE_Y;
		g_rank[i].vertexWk[3].vtx.z = 0.0f;
	}
}

void SetVertexRankingBG(void)
{
	g_vertexWkRankingBG[0].vtx = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y, 0.0f);
	g_vertexWkRankingBG[1].vtx = D3DXVECTOR3(RANKING_BG_POS_X + RANKING_BG_SIZE_X, RANKING_BG_POS_Y, 0.0f);
	g_vertexWkRankingBG[2].vtx = D3DXVECTOR3(RANKING_BG_POS_X, RANKING_BG_POS_Y + RANKING_BG_SIZE_Y, 0.0f);
	g_vertexWkRankingBG[3].vtx = D3DXVECTOR3(RANKING_BG_POS_X + RANKING_BG_SIZE_X, RANKING_BG_POS_Y + RANKING_BG_SIZE_Y, 0.0f);
}

int *GetRankingScore(void)
{
	return &g_rankingScore[0];
}

void SaveRankingScore(int score)
{
	// �X�R�A���O�̔z���T��
	int saveNum = 0;			// �X�R�A���i�[����Y����
	bool saveScore = false;		// �X�R�A�ۑ��ꏊ�����܂������ۂ�
	int *rankScore = GetRankingScore();

	// ���l��0�i�܂��X�R�A���L�^����Ă��Ȃ��j�̂Ƃ���ɕۑ�
	for (int i = 0; i < RANKING_MAX; i++)
	{
		if (rankScore[i] == 0)
		{
			rankScore[i] = score;
			saveScore = true;
			break;
		}
	}

	// �󂫂̔z�񂪂Ȃ��ꍇ�A�ŏ��l�ł���z��Ɋi�[
	if (saveScore == false)
	{
		int minScore = RANKINGSCORE_MAX;

		for (int i = 0; i < RANKING_MAX; i++)
		{
			if (rankScore[i] <= minScore)
			{
				minScore = rankScore[i];
				saveNum = i;
			}
		}

		rankScore[saveNum] = score;
	}
}

void SortRanking(void)
{
	// �����L���O�X�R�A���~���Ƀ\�[�g
	for (int i = 0; i < RANKING_MAX; i++)
	{
		for (int j = i + 1; j < RANKING_MAX; j++)
		{
			if (g_rankingScore[i] < g_rankingScore[j])
			{
				int temp = g_rankingScore[i];
				g_rankingScore[i] = g_rankingScore[j];
				g_rankingScore[j] = temp;
			}
		}
	}
}

bool *GetAppearInfo(void)
{
	return &g_appearRanking;
}