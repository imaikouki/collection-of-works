//=============================================================================
//
// チュートリアル画面処理 [rule.h]
// Author : Imai
//
//=============================================================================
#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RULE1		("data/TEXTURE/ps.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RULE2		("data/TEXTURE/back.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RULE3		("data/TEXTURE/kaiten.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RULE4		("data/TEXTURE/zyouge.png")			// 読み込むテクスチャファイル名
#define TEXTURE_RULE5		("data/TEXTURE/sayu.png")
#define TEXTURE_RULE6		("data/TEXTURE/l1.png")
#define TEXTURE_RULE7		("data/TEXTURE/clear.png")
#define TEXTURE_RULE8		("data/TEXTURE/zyunbi.png")

#define	RULE_POS_X			(0)								// チュートリアルの表示位置
#define	RULE_POS_Y			(320)								// チュートリアルの表示位置
#define	RULE_SIZE_X			(640)							// チュートリアルの幅
#define	RULE_SIZE_Y			(120)							// チュートリアルの高さ
#define	RULE_NUM			(8)								// チュートリアルのページ数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRule(int type);
void UninitRule(void);
void UpdateRule(void);
void DrawRule(void);