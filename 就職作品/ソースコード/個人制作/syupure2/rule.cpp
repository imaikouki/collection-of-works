//=============================================================================
//
// チュートリアル画面処理 [rule.cpp]
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRule(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRule[RULE_NUM];		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRuleLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkRule[NUM_VERTEX];			// 頂点情報格納ワーク

int						ruleNumber = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRule(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ruleNumber = 0;

	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE1,				// ファイルの名前
			&g_pD3DTextureRule[0]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE2,				// ファイルの名前
			&g_pD3DTextureRule[1]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE3,				// ファイルの名前
			&g_pD3DTextureRule[2]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE4,				// ファイルの名前
			&g_pD3DTextureRule[3]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE5,				// ファイルの名前
			&g_pD3DTextureRule[4]);		// 読み込むメモリー

			// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE6,				// ファイルの名前
			&g_pD3DTextureRule[5]);		// 読み込むメモリー

			// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE7,				// ファイルの名前
			&g_pD3DTextureRule[6]);		// 読み込むメモリー

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RULE8,				// ファイルの名前
			&g_pD3DTextureRule[7]);		// 読み込むメモリー
	}

	// 頂点情報の作成
	MakeVertexRule();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRule(void)
{
	for (int i = 0; i < RULE_NUM; i++)
	{
		if (g_pD3DTextureRule[i] != NULL)
		{// テクスチャの開放
			g_pD3DTextureRule[i]->Release();
			g_pD3DTextureRule[i] = NULL;
		}
	}

	if (g_pD3DTextureRuleLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureRuleLogo->Release();
		g_pD3DTextureRuleLogo = NULL;
	}
}

//=============================================================================
// 更新処理
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
		// ゲームパッドでで移動処理
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
// 描画処理
//=============================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRule[ruleNumber]);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_vertexWkRule, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRule(void)
{

	// 頂点座標の設定
	g_vertexWkRule[0].vtx = D3DXVECTOR3(RULE_POS_X, RULE_POS_Y, 0.0f);
	g_vertexWkRule[1].vtx = D3DXVECTOR3(RULE_POS_X + RULE_SIZE_X, RULE_POS_Y, 0.0f);
	g_vertexWkRule[2].vtx = D3DXVECTOR3(RULE_POS_X, RULE_POS_Y + RULE_SIZE_Y, 0.0f);
	g_vertexWkRule[3].vtx = D3DXVECTOR3(RULE_POS_X + RULE_SIZE_X, RULE_POS_Y + RULE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkRule[0].rhw =
		g_vertexWkRule[1].rhw =
		g_vertexWkRule[2].rhw =
		g_vertexWkRule[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRule[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRule[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkRule[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRule[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRule[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRule[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}
