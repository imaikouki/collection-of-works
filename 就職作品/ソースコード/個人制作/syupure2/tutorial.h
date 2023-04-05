//=============================================================================
//
// チュートリアル画面処理 [tutorial.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TUTORIAL		("data/TEXTURE/sousa.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TUTORIAL_LOGO	("data/TEXTURE/sentoukaisi.png")		// 読み込むテクスチャファイル名
#define	TUTORIAL_POS_X			(0)								// タイトルの表示位置
#define	TUTORIAL_POS_Y			(0)								// タイトルの表示位置
#define	TUTORIAL_SIZE_X		(640)							// タイトルの幅
#define	TUTORIAL_SIZE_Y		(640)							// タイトルの高さ
#define	TUTORIALLOGO_POS_X		(350)							// タイトルロゴの表示位置
#define	TUTORIALLOGO_POS_Y		(350)							// タイトルロゴの表示位置
#define	TUTORIALLOGO_SIZE_X	(300)							// タイトルロゴの幅
#define	TUTORIALLOGO_SIZE_Y	(80)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTutorial(int type);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

