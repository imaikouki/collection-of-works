//=============================================================================
//
// タイトル画面処理 [titleselection.cpp]
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(void);
void SetVertexLogo(void);
void SetTextureArrow(int cntPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureStartLogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRankingLogo = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];							// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleLogo[TITLELOGO_SIZE_Y][NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkStartLogo[NUM_VERTEX];
VERTEX_2D				g_vertexWkRankingLogo[NUM_VERTEX];

D3DXVECTOR3				g_startLogoPos;
D3DXVECTOR3				g_rankingLogoPos;

ARROW					g_choiceArrow;

double sinbuf[TITLELOGO_SIZE_Y];
float radius = 0.0f;
int g_alpha = 255;

bool					isEntered;						// エンターキーが押されたかどうか
static int				g_cnt;							// 文字点滅用カウント
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitleSelection(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	double pi = 3.14;

	if (type == 0)
	{

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_START_LOGO,			// ファイルの名前
			&g_pD3DTextureStartLogo);	// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RANKING_LOGO,			// ファイルの名前
			&g_pD3DTextureRankingLogo);	// 読み込むメモリー

		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_CHOICEARROW,			// ファイルの名前
			&g_choiceArrow.pD3DTexture);	// 読み込むメモリー

	}

	/*表示位置の初期化*/
	g_startLogoPos = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y, 0.0f);
	g_rankingLogoPos = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y, 0.0f);
	g_choiceArrow.pos = D3DXVECTOR3(CHOICEARROW_POS_X, STARTLOGO_POS_Y + CHOICEARROW_HIGHT, 0.0f);

	g_choiceArrow.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI / 2);		// 回転量
	g_choiceArrow.nCountAnim = 0;
	g_choiceArrow.nPatternAnim = 0;
	g_choiceArrow.isRanked = false;

	D3DXVECTOR2 temp = D3DXVECTOR2(CHOICEARROW_SIZE_X, CHOICEARROW_SIZE_Y);
	g_choiceArrow.radius = D3DXVec2Length(&temp);								// ボールの半径を初期化
	g_choiceArrow.baseAngle = atan2f(CHOICEARROW_SIZE_Y, CHOICEARROW_SIZE_X);	// ボールの角度を初期化


	for (int i = 0; i < TITLELOGO_SIZE_Y; i++)
	{
		//sinbuf[i] = sinf((pi * i) / 20.0f);
		sinbuf[i] = sinf((2 * D3DX_PI * i) / TITLELOGO_SIZE_Y);
	}

	isEntered = false;
	g_cnt = 0;

	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitleSelection(void)
{
	if (g_pD3DTextureStartLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureStartLogo->Release();
		g_pD3DTextureStartLogo = NULL;
	}

	if (g_pD3DTextureRankingLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureRankingLogo->Release();
		g_pD3DTextureRankingLogo = NULL;
	}

	if (g_choiceArrow.pD3DTexture != NULL)
	{// テクスチャの開放
		g_choiceArrow.pD3DTexture->Release();
		g_choiceArrow.pD3DTexture = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitleSelection(void)
{
	if (g_choiceArrow.pos.y == g_startLogoPos.y + CHOICEARROW_HIGHT)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			//InitResultScore(1);
			InitPlayer();		// プレイヤーの再初期化
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
		// ゲームパッドでで移動処理
		else if (IsButtonTriggered(0, BUTTON_O))
		{
			//InitResultScore(1);
			InitPlayer();		// プレイヤーの再初期化
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
		else if (IsButtonTriggered(0, BUTTON_X))
		{
			//InitResultScore(1);
			InitPlayer();		// プレイヤーの再初期化
			SetFade(FADE_OUT/*, SCENE_TUTORIAL, SOUND_LABEL_BGM_tutorial*/);
			StopSound(SOUND_LABEL_BGM000);
			PlaySound(SOUND_LABEL_SE_COIN);
			isEntered = true;
		}
	}
	else if (g_choiceArrow.pos.y == g_rankingLogoPos.y + CHOICEARROW_HIGHT)
	{
		// ランキングの表示
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
		// ゲームパッドでで移動処理
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

	/*文字の点滅処理*/
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

	/*矢印の移動処理*/
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
	/*矢印のアニメーション*/
	g_choiceArrow.nCountAnim++;

	if ((g_choiceArrow.nCountAnim % ARROW_ANIM_TIME) == 0)
	{
		// パターンの切り替え
		g_choiceArrow.nPatternAnim = (g_choiceArrow.nPatternAnim + 1) % ARROW_ANIM_NUM;

		// テクスチャ座標を設定
		SetTextureArrow(g_choiceArrow.nPatternAnim);
	}


	SetVertexLogo();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitleSelection(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スタートロゴ
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureStartLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkStartLogo, sizeof(VERTEX_2D));

	// ランキングロゴ
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRankingLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkRankingLogo, sizeof(VERTEX_2D));

	// 矢印
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_choiceArrow.pD3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_choiceArrow.vertexWk, sizeof(VERTEX_2D));

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{
	// スタートロゴ
	// 頂点座標の設定
	g_vertexWkStartLogo[0].vtx = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y, 0.0f);
	g_vertexWkStartLogo[1].vtx = D3DXVECTOR3(STARTLOGO_POS_X + STARTLOGO_SIZE_X, STARTLOGO_POS_Y, 0.0f);
	g_vertexWkStartLogo[2].vtx = D3DXVECTOR3(STARTLOGO_POS_X, STARTLOGO_POS_Y + STARTLOGO_SIZE_Y, 0.0f);
	g_vertexWkStartLogo[3].vtx = D3DXVECTOR3(STARTLOGO_POS_X + STARTLOGO_SIZE_X, STARTLOGO_POS_Y + STARTLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkStartLogo[0].rhw =
		g_vertexWkStartLogo[1].rhw =
		g_vertexWkStartLogo[2].rhw =
		g_vertexWkStartLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkStartLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkStartLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkStartLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkStartLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkStartLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkStartLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ランキングロゴ
	// 頂点座標の設定
	g_vertexWkRankingLogo[0].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y, 0.0f);
	g_vertexWkRankingLogo[1].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X + RANKINGLOGO_SIZE_X, RANKINGLOGO_POS_Y, 0.0f);
	g_vertexWkRankingLogo[2].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X, RANKINGLOGO_POS_Y + RANKINGLOGO_SIZE_Y, 0.0f);
	g_vertexWkRankingLogo[3].vtx = D3DXVECTOR3(RANKINGLOGO_POS_X + RANKINGLOGO_SIZE_X, RANKINGLOGO_POS_Y + RANKINGLOGO_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkRankingLogo[0].rhw =
		g_vertexWkRankingLogo[1].rhw =
		g_vertexWkRankingLogo[2].rhw =
		g_vertexWkRankingLogo[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkRankingLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkRankingLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkRankingLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkRankingLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkRankingLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkRankingLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点座標の設定
	g_choiceArrow.vertexWk[0].vtx = D3DXVECTOR3(CHOICEARROW_POS_X, g_choiceArrow.pos.y, 0.0f);
	g_choiceArrow.vertexWk[1].vtx = D3DXVECTOR3(CHOICEARROW_POS_X + CHOICEARROW_SIZE_X, g_choiceArrow.pos.y, 0.0f);
	g_choiceArrow.vertexWk[2].vtx = D3DXVECTOR3(CHOICEARROW_POS_X, g_choiceArrow.pos.y + CHOICEARROW_SIZE_Y, 0.0f);
	g_choiceArrow.vertexWk[3].vtx = D3DXVECTOR3(CHOICEARROW_POS_X + CHOICEARROW_SIZE_X, g_choiceArrow.pos.y + CHOICEARROW_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_choiceArrow.vertexWk[0].rhw =
		g_choiceArrow.vertexWk[1].rhw =
		g_choiceArrow.vertexWk[2].rhw =
		g_choiceArrow.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	g_choiceArrow.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_choiceArrow.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_choiceArrow.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_choiceArrow.vertexWk[1].tex = D3DXVECTOR2(1.0f / ARROW_ANIM_DEVIDE_X, 0.0f);
	g_choiceArrow.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / ARROW_ANIM_DEVIDE_Y);
	g_choiceArrow.vertexWk[3].tex = D3DXVECTOR2(1.0f / ARROW_ANIM_DEVIDE_X, 1.0f / ARROW_ANIM_DEVIDE_Y);

	return S_OK;
}

void SetTextureArrow(int cntPattern)
{
	// テクスチャ座標の設定
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
		// 頂点座標の設定
		g_vertexWkTitleLogo[i][0].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius), TITLELOGO_POS_Y + (float)(i), 0.0f);
		g_vertexWkTitleLogo[i][1].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius) + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + (float)(i), 0.0f);
		g_vertexWkTitleLogo[i][2].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius), TITLELOGO_POS_Y + (float)(i)+1.0f, 0.0f);
		g_vertexWkTitleLogo[i][3].vtx = D3DXVECTOR3(TITLELOGO_POS_X + (float)(sinbuf[i] * radius) + TITLELOGO_SIZE_X, TITLELOGO_POS_Y + (float)(i)+1.0f, 0.0f);
	}

	// 矢印
	// 頂点座標の設定
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