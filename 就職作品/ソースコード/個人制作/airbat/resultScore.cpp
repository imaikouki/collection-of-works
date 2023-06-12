//=============================================================================
//
// �|���S������ [resultScore.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "score.h"
#include "resultScore.h"
#include "ranking.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexResultScore(void);
void SetTextureResultScore(void);
void SetVertexResultScore(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
/*�i�񂾋���*/
LPDIRECT3DTEXTURE9		g_pD3DTextureResultScore[RESULTSCORE_DIGITS];	// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				g_vertexWkResultScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				g_posResultScore[RESULTSCORE_DIGITS];					// �����̈ʒu

/*�|�����G�̐�*/
LPDIRECT3DTEXTURE9		g_pD3DTextureBeatScore[RESULTSCORE_DIGITS];	// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				g_vertexWkBeatScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				g_posBeatScore[RESULTSCORE_DIGITS];					// �����̈ʒu

/*���X�R�A*/
LPDIRECT3DTEXTURE9		g_pD3DTextureAllScore[RESULTSCORE_DIGITS];	// �e�N�X�`���ւ̃|�C���^
VERTEX_2D				g_vertexWkAllScore[RESULTSCORE_DIGITS][NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				g_posAllScore[RESULTSCORE_DIGITS];					// �����̈ʒu

static int g_scoreNum = 0;

static bool saveScore;		// �X�R�A�������L���O�p�ɕۑ��������ۂ�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultScore(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posResultScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), RESULTSCORE_POS_Y, 0.0f);
	}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posBeatScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), BEATSCORE_POS_Y, 0.0f);
	}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		g_posAllScore[i] = D3DXVECTOR3(FIRST_SCORE_POS_X + TEXTURE_RESULTSCORE_SIZE_X * 2 * ((RESULTSCORE_DIGITS - i) + 1), ALLSCORE_POS_Y, 0.0f);
	}

	g_scoreNum = 0;
	saveScore = false;

	// �e�N�X�`���̓ǂݍ���  
	if (type == 0)	// ����̂ݓǂݍ���
	{
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_GAME_RESULTSCORE,				// �t�@�C���̖��O
				&g_pD3DTextureResultScore[i]);			// �ǂݍ��ރ������̃|�C���^
		}
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_GAME_RESULTSCORE,				// �t�@�C���̖��O
				&g_pD3DTextureBeatScore[i]);			// �ǂݍ��ރ������̃|�C���^
		}
		for (int i = 0; i < RESULTSCORE_DIGITS; i++)
		{
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
				TEXTURE_GAME_RESULTSCORE,				// �t�@�C���̖��O
				&g_pD3DTextureAllScore[i]);			// �ǂݍ��ރ������̃|�C���^
		}

	}

	MakeVertexResultScore();

	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitResultScore(void)
{

	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		if (g_pD3DTextureResultScore[i] != NULL)
		{
			g_pD3DTextureResultScore[i]->Release();
			g_pD3DTextureResultScore[i] = NULL;
		}

		if (g_pD3DTextureResultScore[i] != NULL)
		{
			g_pD3DTextureBeatScore[i]->Release();
			g_pD3DTextureBeatScore[i] = NULL;
		}

		if (g_pD3DTextureAllScore[i] != NULL)
		{
			g_pD3DTextureAllScore[i]->Release();
			g_pD3DTextureAllScore[i] = NULL;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultScore(void)
{
	SetTextureResultScore();
}


//=============================================================================
// �X�R�A�`�揈��
//=============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	// �e�N�X�`���̐ݒ� 
	//	pDevice->SetTexture(0, g_pD3DTextureResultScore[i]);

	//	// �|���S���̕`��
	//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkResultScore[i], sizeof(VERTEX_2D));
	//}
	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	// �e�N�X�`���̐ݒ� 
	//	pDevice->SetTexture(0, g_pD3DTextureBeatScore[i]);

	//	// �|���S���̕`��
	//	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkBeatScore[i], sizeof(VERTEX_2D));
	//}
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		// �e�N�X�`���̐ݒ� 
		pDevice->SetTexture(0, g_pD3DTextureAllScore[i]);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkAllScore[i], sizeof(VERTEX_2D));
	}

}


//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetVertexResultScore();

	for (int no = 0; no < RESULTSCORE_DIGITS; no++)
	{
		// �����̒��_���W�̐ݒ�
		// �i�񂾋���
		g_vertexWkResultScore[no][0].rhw =
			g_vertexWkResultScore[no][1].rhw =
			g_vertexWkResultScore[no][2].rhw =
			g_vertexWkResultScore[no][3].rhw = 1.0f;

		g_vertexWkResultScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkResultScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkResultScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkResultScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkResultScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkResultScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);

		// �����̒��_���W�̐ݒ�
		// �|�����G�̐�
		g_vertexWkBeatScore[no][0].rhw =
			g_vertexWkBeatScore[no][1].rhw =
			g_vertexWkBeatScore[no][2].rhw =
			g_vertexWkBeatScore[no][3].rhw = 1.0f;

		g_vertexWkBeatScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkBeatScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkBeatScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkBeatScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkBeatScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkBeatScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);

		// �����̒��_���W�̐ݒ�
		// ���X�R�A
		g_vertexWkAllScore[no][0].rhw =
			g_vertexWkAllScore[no][1].rhw =
			g_vertexWkAllScore[no][2].rhw =
			g_vertexWkAllScore[no][3].rhw = 1.0f;

		g_vertexWkAllScore[no][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkAllScore[no][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_vertexWkAllScore[no][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkAllScore[no][1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 0.0f);
		g_vertexWkAllScore[no][2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
		g_vertexWkAllScore[no][3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_S_X, 1.0f / TEXTURE_PATTERN_DIVIDE_S_Y);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureResultScore(void)
{
	PLAYER *player = GetPlayer();
	int allScore = *GetScore();		// ���X�R�A

	//player->distanceScore = (int)(player->maxDistance / 20);
	//int beatNum = player->beatEnemyNum;
	//int allScore = player->distanceScore + beatNum * 50;
	
	//int allScore = 1000;												// ���X�R�A

	if (saveScore != true)
	{
		SaveRankingScore(allScore);
		saveScore = true;
	}
	////�e�N�X�`�����W�̐ݒ�
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	/*�i�񂾋���*/
	//	float tx1 = (float)(allScore % 10) - 1.0f;		//10�Ŋ��������܂肪���̌��̐����ɂȂ�
	//	g_vertexWkResultScore[i][0].tex = D3DXVECTOR2(tx1 * 0.1f, 0.0f);
	//	g_vertexWkResultScore[i][1].tex = D3DXVECTOR2((tx1 + 1) *0.1f, 0.0f);
	//	g_vertexWkResultScore[i][2].tex = D3DXVECTOR2(tx1 * 0.1f, 1.0f);
	//	g_vertexWkResultScore[i][3].tex = D3DXVECTOR2((tx1 + 1) * 0.1f, 1.0f);
	//	allScore /= 10;							//�����E�Ɉ�ړ�
	//}
	//for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	//{
	//	/*�|�����G�̐�*/
	//	float tx2 = (float)(allScore % 10) - 1.0f;		//10�Ŋ��������܂肪���̌��̐����ɂȂ�
	//	g_vertexWkBeatScore[i][0].tex = D3DXVECTOR2(tx2 * 0.1f, 0.0f);
	//	g_vertexWkBeatScore[i][1].tex = D3DXVECTOR2((tx2 + 1) *0.1f, 0.0f);
	//	g_vertexWkBeatScore[i][2].tex = D3DXVECTOR2(tx2 * 0.1f, 1.0f);
	//	g_vertexWkBeatScore[i][3].tex = D3DXVECTOR2((tx2 + 1) * 0.1f, 1.0f);
	//	allScore /= 10;							//�����E�Ɉ�ړ�
	//}
	for (int i = 0; i < RESULTSCORE_DIGITS; i++)
	{
		/*���X�R�A*/
		float tx3 = (float)(allScore % 10) - 1.0f;		//10�Ŋ��������܂肪���̌��̐����ɂȂ�
		g_vertexWkAllScore[i][0].tex = D3DXVECTOR2(tx3 * 0.1f, 0.0f);
		g_vertexWkAllScore[i][1].tex = D3DXVECTOR2((tx3 + 1) *0.1f, 0.0f);
		g_vertexWkAllScore[i][2].tex = D3DXVECTOR2(tx3 * 0.1f, 1.0f);
		g_vertexWkAllScore[i][3].tex = D3DXVECTOR2((tx3 + 1) * 0.1f, 1.0f);
		allScore /= 10;							//�����E�Ɉ�ړ�
	}
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexResultScore(void)
{
	/*�����̃e�N�X�`��*/
	for (int no = 0; no < RESULTSCORE_DIGITS; no++)
	{
		/*�i�񂾋���*/
		g_vertexWkResultScore[no][0].vtx.x = g_posResultScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][0].vtx.y = g_posResultScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][0].vtx.z = 0.0f;

		g_vertexWkResultScore[no][1].vtx.x = g_posResultScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][1].vtx.y = g_posResultScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][1].vtx.z = 0.0f;

		g_vertexWkResultScore[no][2].vtx.x = g_posResultScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][2].vtx.y = g_posResultScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][2].vtx.z = 0.0f;

		g_vertexWkResultScore[no][3].vtx.x = g_posResultScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkResultScore[no][3].vtx.y = g_posResultScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkResultScore[no][3].vtx.z = 0.0f;

		/*�|�����G�̐�*/
		g_vertexWkBeatScore[no][0].vtx.x = g_posBeatScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][0].vtx.y = g_posBeatScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][0].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][1].vtx.x = g_posBeatScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][1].vtx.y = g_posBeatScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][1].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][2].vtx.x = g_posBeatScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][2].vtx.y = g_posBeatScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][2].vtx.z = 0.0f;

		g_vertexWkBeatScore[no][3].vtx.x = g_posBeatScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkBeatScore[no][3].vtx.y = g_posBeatScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkBeatScore[no][3].vtx.z = 0.0f;

		/*���X�R�A*/
		g_vertexWkAllScore[no][0].vtx.x = g_posAllScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][0].vtx.y = g_posAllScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][0].vtx.z = 0.0f;

		g_vertexWkAllScore[no][1].vtx.x = g_posAllScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][1].vtx.y = g_posAllScore[no].y - TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][1].vtx.z = 0.0f;

		g_vertexWkAllScore[no][2].vtx.x = g_posAllScore[no].x - TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][2].vtx.y = g_posAllScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][2].vtx.z = 0.0f;

		g_vertexWkAllScore[no][3].vtx.x = g_posAllScore[no].x + TEXTURE_SCORE_SIZE_X;
		g_vertexWkAllScore[no][3].vtx.y = g_posAllScore[no].y + TEXTURE_SCORE_SIZE_Y;
		g_vertexWkAllScore[no][3].vtx.z = 0.0f;

	}

}
