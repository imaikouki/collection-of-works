//=============================================================================
//
// �^�C�g����ʏ��� [titleselection.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "titleselection.h"
#include "resultScore.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include <math.h>

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexLogo(void);
void SetTextureArrow(int cntPattern);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureStartLogo = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRankingLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];							// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleLogo[TITLELOGO_SIZE_Y][NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkStartLogo[NUM_VERTEX];
VERTEX_2D				g_vertexWkRankingLogo[NUM_VERTEX];

D3DXVECTOR3				g_startLogoPos;
D3DXVECTOR3				g_rankingLogoPos;

ARROW					g_choiceArrow;

double sinbuf[TITLELOGO_SIZE_Y];
float radius = 0.0f;
int g_alpha = 255;

bool					isEntered;						// �G���^�[�L�[�������ꂽ���ǂ���
static int				g_cnt;							// �����_�ŗp�J�E���g
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitleSelection(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	double pi = 3.14;

	if (type == 0)
	{

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_START_LOGO,			// �t�@�C���̖��O
			&g_pD3DTextureStartLogo);	// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RANKING_LOGO,			// �t�@�C���̖��O
			&g_pD3DTextureRankingLogo);	// �ǂݍ��ރ������[

		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_CHOICEARROW,			// �t�@�C���̖��O
			&g_choiceArrow.pD3DTexture);	// �ǂݍ��ރ������[

	}

	/*�\���ʒu�̏�����*/
	g_startLogoPos = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y, 0.0f);
	g_rankingLogoPos = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y, 0.0f);
	g_choiceArrow.pos = D3DXVECTOR3(CHOICEARROW_POS_X, STARTLOGO_POS_Y + CHOICEARROW_HIGHT, 0.0f);

	g_choiceArrow.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2);		// ��]��
	g_choiceArrow.nCountAnim = 0;
	g_choiceArrow.nPatternAnim = 0;
	g_choiceArrow.isRanked = false;

	D3DXVECTOR2 temp = D3DXVECTOR2(CHOICEARROW_SIZE_X, CHOICEARROW_SIZE_Y);
	g_choiceArrow.radius = D3DXVec2Length(&temp);								// �{�[���̔��a��������
	g_choiceArrow.baseAngle = atan2f(CHOICEARROW_SIZE_Y, CHOICEARROW_SIZE_X);	// �{�[���̊p�x��������


	for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
	{
		//sinbuf[i] = sinf((pi * i) / 20.0f);
		sinbuf[i] = sinf((2 * D3DX_PI * i) / TITLELOGO_SIZE_Y);
	}

	isEntered = false;
	g_cnt = 0;

	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitleSelection(void)
{
	if (g_pD3DTextureStartLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureStartLogo->Release();
		g_pD3DTextureStartLogo = NULL;
	}

	if (g_pD3DTextureRankingLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRankingLogo->Release();
		g_pD3DTextureRankingLogo = NULL;
	}

	if (g_choiceArrow.pD3DTexture != NULL)
	{// �e�N�X�`���̊J��
		g_choiceArrow.pD3DTexture->Release();
		g_choiceArrow.pD3DTexture = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitleSelection(void)
{
	if (g_choiceArrow.pos.y == g_startLogoPos.y + CHOICEARROW_HIGHT)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter��������A�X�e�[�W��؂�ւ���
			//InitResultScore(1);
			InitPlayer();		// �v���C���[�̍ď�����
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
		// �Q�[���p�b�h�łňړ�����
		else if (IsButtonTriggered(0, BUTTON_O))
		{
			//InitResultScore(1);
			InitPlayer();		// �v���C���[�̍ď�����
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			//InitResultScore(1);
			InitPlayer();		// �v���C���[�̍ď�����
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
	}
	else if (g_choiceArrow.pos.y == g_rankingLogoPos.y + CHOICEARROW_HIGHT)
	{
		// �����L���O�̕\��
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			if (g_choiceArrow.isRanked == false)
			{
				g_choiceArrow.isRanked = true;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
			else
			{
				g_choiceArrow.isRanked = false;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
		}
		// �Q�[���p�b�h�łňړ�����
		else if (IsButtonTriggered(0, BUTTON_O))
		{
			if (g_choiceArrow.isRanked == false)
			{
				g_choiceArrow.isRanked = true;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
			else
			{
				g_choiceArrow.isRanked = false;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
		}
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			if (g_choiceArrow.isRanked == false)
			{
				g_choiceArrow.isRanked = true;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
			else
			{
				g_choiceArrow.isRanked = false;
				PlaySound(SOUND_LABEL_SE_COIN);
			}
		}
	}

	/*�����̓_�ŏ���*/
	if (isEntered == false)
	{
		if (g_cnt % 20 == 0)
		{
			for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
			{
				g_vertexWkTitleLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		else if (g_cnt % 20 == 10)
		{
			for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
			{
				g_vertexWkTitleLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
			}
		}

	}
	else
	{
		if (g_cnt % 6 == 0)
		{
			for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
			{
				g_vertexWkTitleLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
				g_vertexWkTitleLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
		}
		else if (g_cnt % 6 == 3)
		{
			for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
			{
				g_vertexWkTitleLogo[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
				g_vertexWkTitleLogo[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
			}
		}

	}
	g_cnt++;

	/*���̈ړ�����*/
	if (g_choiceArrow.isRanked != true)
	{
		if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(0, BUTTON_DOWN))
		{
			g_choiceArrow.pos.y = g_rankingLogoPos.y + CHOICEARROW_HIGHT;
			PlaySound(SOUND_LABEL_SE_COIN);
		}
		else if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(0, BUTTON_UP))
		{
			g_choiceArrow.pos.y = g_startLogoPos.y + CHOICEARROW_HIGHT;
			PlaySound(SOUND_LABEL_SE_COIN);
		}
	}
	/*���̃A�j���[�V����*/
	g_choiceArrow.nCountAnim++;

	if ((g_choiceArrow.nCountAnim % ARROW_ANIM_TIME) == 0)
	{
		// �p�^�[���̐؂�ւ�
		g_choiceArrow.nPatternAnim = (g_choiceArrow.nPatternAnim + 1) % ARROW_ANIM_NUM;

		// �e�N�X�`�����W��ݒ�
		SetTextureArrow(g_choiceArrow.nPatternAnim);
	}


	SetVertexLogo();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitleSelection(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�^�[�g���S
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureStartLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkStartLogo, sizeof(VERTEX_2D));

	// �����L���O���S
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRankingLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRankingLogo, sizeof(VERTEX_2D));

	// ���
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_choiceArrow.pD3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_choiceArrow.vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	// �X�^�[�g���S
	// ���_���W�̐ݒ�
	g_vertexWkStartLogo[0].vtx = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y, 0.0f);
	g_vertexWkStartLogo[1].vtx = D3DXVECTOR3(STARTLOGO_POS_X + STARTLOGO_SIZE_X, STARTLOGO_POS_Y, 0.0f);
	g_vertexWkStartLogo[2].vtx = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y + STARTLOGO_SIZE_Y, 0.0f);
	g_vertexWkStartLogo[3].vtx = D3DXVECTOR3(STARTLOGO_POS_X + STARTLOGO_SIZE_X, STARTLOGO_POS_Y + STARTLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkStartLogo[0].rhw =
		g_vertexWkStartLogo[1].rhw =
		g_vertexWkStartLogo[2].rhw =
		g_vertexWkStartLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkStartLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkStartLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkStartLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkStartLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkStartLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �����L���O���S
	// ���_���W�̐ݒ�
	g_vertexWkRankingLogo[0].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y, 0.0f);
	g_vertexWkRankingLogo[1].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X + RANKINGLOGO_SIZE_X, RANKINGLOGO_POS_Y, 0.0f);
	g_vertexWkRankingLogo[2].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y + RANKINGLOGO_SIZE_Y, 0.0f);
	g_vertexWkRankingLogo[3].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X + RANKINGLOGO_SIZE_X, RANKINGLOGO_POS_Y + RANKINGLOGO_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRankingLogo[0].rhw =
		g_vertexWkRankingLogo[1].rhw =
		g_vertexWkRankingLogo[2].rhw =
		g_vertexWkRankingLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRankingLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRankingLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRankingLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRankingLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRankingLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	g_choiceArrow.vertexWk[0].vtx = D3DXVECTOR3(CHOICEARROW_POS_X, g_choiceArrow.pos.y, 0.0f);
	g_choiceArrow.vertexWk[1].vtx = D3DXVECTOR3(CHOICEARROW_POS_X + CHOICEARROW_SIZE_X, g_choiceArrow.pos.y, 0.0f);
	g_choiceArrow.vertexWk[2].vtx = D3DXVECTOR3(CHOICEARROW_POS_X, g_choiceArrow.pos.y + CHOICEARROW_SIZE_Y, 0.0f);
	g_choiceArrow.vertexWk[3].vtx = D3DXVECTOR3(CHOICEARROW_POS_X + CHOICEARROW_SIZE_X, g_choiceArrow.pos.y + CHOICEARROW_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_choiceArrow.vertexWk[0].rhw =
		g_choiceArrow.vertexWk[1].rhw =
		g_choiceArrow.vertexWk[2].rhw =
		g_choiceArrow.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_choiceArrow.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_choiceArrow.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_choiceArrow.vertexWk[1].tex = D3DXVECTOR2(1.0f / ARROW_ANIM_DEVIDE_X, 0.0f);
	g_choiceArrow.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / ARROW_ANIM_DEVIDE_Y);
	g_choiceArrow.vertexWk[3].tex = D3DXVECTOR2(1.0f / ARROW_ANIM_DEVIDE_X, 1.0f / ARROW_ANIM_DEVIDE_Y);

	return S_OK;
}

void SetTextureArrow(int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % ARROW_ANIM_DEVIDE_X;
	int y = cntPattern / ARROW_ANIM_DEVIDE_X;
	float sizeX = 1.0f / ARROW_ANIM_DEVIDE_X;
	float sizeY = 1.0f / ARROW_ANIM_DEVIDE_Y;

	g_choiceArrow.vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	g_choiceArrow.vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	g_choiceArrow.vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	g_choiceArrow.vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}


void SetVertexLogo(void)
{
	for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkTitleLogo[i][0].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius), TITLELOGO_POS_Y + (float)(i), 0.0f);
		g_vertexWkTitleLogo[i][1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius) + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + (float)(i), 0.0f);
		g_vertexWkTitleLogo[i][2].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius), TITLELOGO_POS_Y + (float)(i)+1.0f, 0.0f);
		g_vertexWkTitleLogo[i][3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius) + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + (float)(i)+1.0f, 0.0f);
	}

	// ���
	// ���_���W�̐ݒ�
	g_choiceArrow.vertexWk[0].vtx.x = g_choiceArrow.pos.x - cosf(g_choiceArrow.baseAngle + g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[0].vtx.y = g_choiceArrow.pos.y - sinf(g_choiceArrow.baseAngle + g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[0].vtx.z = 0.0f;

	g_choiceArrow.vertexWk[1].vtx.x = g_choiceArrow.pos.x + cosf(g_choiceArrow.baseAngle - g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[1].vtx.y = g_choiceArrow.pos.y - sinf(g_choiceArrow.baseAngle - g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[1].vtx.z = 0.0f;

	g_choiceArrow.vertexWk[2].vtx.x = g_choiceArrow.pos.x - cosf(g_choiceArrow.baseAngle - g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[2].vtx.y = g_choiceArrow.pos.y + sinf(g_choiceArrow.baseAngle - g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[2].vtx.z = 0.0f;

	g_choiceArrow.vertexWk[3].vtx.x = g_choiceArrow.pos.x + cosf(g_choiceArrow.baseAngle + g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[3].vtx.y = g_choiceArrow.pos.y + sinf(g_choiceArrow.baseAngle + g_choiceArrow.rot.z) * g_choiceArrow.radius;
	g_choiceArrow.vertexWk[3].vtx.z = 0.0f;

}


ARROW *GetArrow(void)
{
	return &g_choiceArrow;
}