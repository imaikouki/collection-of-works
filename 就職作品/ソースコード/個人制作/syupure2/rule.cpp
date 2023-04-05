//=============================================================================
//
// �`���[�g���A����ʏ��� [rule.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "rule.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "game.h"


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRule(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRule[RULE_NUM];		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureRuleLogo = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkRule[NUM_VERTEX];			// ���_���i�[���[�N

int						ruleNumber = 0;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitRule(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ruleNumber = 0;

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE1,				// �t�@�C���̖��O
			&g_pD3DTextureRule[0]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE2,				// �t�@�C���̖��O
			&g_pD3DTextureRule[1]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE3,				// �t�@�C���̖��O
			&g_pD3DTextureRule[2]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE4,				// �t�@�C���̖��O
			&g_pD3DTextureRule[3]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE5,				// �t�@�C���̖��O
			&g_pD3DTextureRule[4]);		// �ǂݍ��ރ������[

			// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE6,				// �t�@�C���̖��O
			&g_pD3DTextureRule[5]);		// �ǂݍ��ރ������[

			// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE7,				// �t�@�C���̖��O
			&g_pD3DTextureRule[6]);		// �ǂݍ��ރ������[

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
			TEXTURE_RULE8,				// �t�@�C���̖��O
			&g_pD3DTextureRule[7]);		// �ǂݍ��ރ������[
	}

	// ���_���̍쐬
	MakeVertexRule();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRule(void)
{
	for (int i = 0; i < RULE_NUM; i++)
	{
		if (g_pD3DTextureRule[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTextureRule[i]->Release();
			g_pD3DTextureRule[i] = NULL;
		}
	}

	if (g_pD3DTextureRuleLogo != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRuleLogo->Release();
		g_pD3DTextureRuleLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRule(void)
{

	if (ruleNumber >= RULE_NUM)
	{
		ruleNumber = RULE_NUM;
		SetFade(FADE_OUT);
	}

	else {
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			ruleNumber++;
			PlaySound(SOUND_LABEL_SE_COIN);
		}
		// �Q�[���p�b�h�łňړ�����
		else if (IsButtonTriggered(0, BUTTON_O))
		{
			ruleNumber++;
			PlaySound(SOUND_LABEL_SE_COIN);
		}
		else if (IsButtonTriggered(0, BUTTON_O))
		{
			ruleNumber++;
			PlaySound(SOUND_LABEL_SE_COIN);
		}
	}

	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRule[ruleNumber]);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_vertexWkRule, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRule(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkRule[0].vtx = D3DXVECTOR3(RULE_POS_X, RULE_POS_Y, 0.0f);
	g_vertexWkRule[1].vtx = D3DXVECTOR3(RULE_POS_X + RULE_SIZE_X, RULE_POS_Y, 0.0f);
	g_vertexWkRule[2].vtx = D3DXVECTOR3(RULE_POS_X, RULE_POS_Y + RULE_SIZE_Y, 0.0f);
	g_vertexWkRule[3].vtx = D3DXVECTOR3(RULE_POS_X + RULE_SIZE_X, RULE_POS_Y + RULE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkRule[0].rhw =
		g_vertexWkRule[1].rhw =
		g_vertexWkRule[2].rhw =
		g_vertexWkRule[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkRule[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkRule[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRule[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRule[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRule[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
