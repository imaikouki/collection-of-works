//=============================================================================
//
// タイトル画面処理 [titleselection.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_START_LOGO		("data/TEXTURE/start001.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RANKING_LOGO	("data/TEXTURE/ranking001.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_CHOICEARROW		("data/TEXTURE/arrow001.png")		// 読み込むテクスチャファイル名

#define	TITLELOGO_POS_X		(200)							// タイトルロゴの表示位置
#define	TITLELOGO_POS_Y		(350)							// タイトルロゴの表示位置
#define	TITLELOGO_SIZE_X	(250)							// タイトルロゴの幅
#define	TITLELOGO_SIZE_Y	(100)							// タイトルロゴの高さ
#define STARTLOGO_POS_X		(250)							// スタートロゴの表示位置
#define STARTLOGO_POS_Y		(250)							// 同上
#define STARTLOGO_SIZE_X	(250/2)							// スタートロゴのサイズ
#define STARTLOGO_SIZE_Y	(125/2)							// 同上

#define RANKINGLOGO_POS_X	(250)							// ランキングロゴの表示位置
#define RANKINGLOGO_POS_Y	(350)							// 同上
#define RANKINGLOGO_SIZE_X	(250/2)							// ランキングロゴのサイズ
#define RANKINGLOGO_SIZE_Y	(125/2)							// 同上

#define CHOICEARROW_POS_X	(150)							// 選択用矢印の表示位置
#define CHOICEARROW_HIGHT	(30)							// 矢印の高さ調整用
#define CHOICEARROW_SIZE_X	(125/2)							// 選択用矢印のサイズ
#define CHOICEARROW_SIZE_Y	(250/2)							// 同上
#define ARROW_ANIM_DEVIDE_X		(10)							// アニメーションのテクスチャ分割数
#define ARROW_ANIM_DEVIDE_Y		(1)							// 同上
#define ARROW_ANIM_NUM		(ARROW_ANIM_DEVIDE_X * ARROW_ANIM_DEVIDE_Y)	// アニメーションのパターン数
#define ARROW_ANIM_TIME		(3)


typedef struct
{
	D3DXVECTOR3				pos;				// 矢印の表示位置
	D3DXVECTOR3				rot;				// 回転量

	LPDIRECT3DTEXTURE9		pD3DTexture;			// テクスチャのポインタ
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

	int						nCountAnim;			// アニメーション用のカウント
	int						nPatternAnim;		// アニメーションのパターン

	float					radius;				// 半径
	float					baseAngle;			// 角度

	bool					isRanked;			// ランキング表示するか否か（参照用）
}ARROW;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitleSelection(int type);
void UninitTitleSelection(void);
void UpdateTitleSelection(void);
void DrawTitleSelection(void);
ARROW *GetArrow(void);

