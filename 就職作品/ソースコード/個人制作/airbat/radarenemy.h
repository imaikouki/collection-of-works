//=============================================================================
//
// レーダー敵処理 [radarenemy.h]
// Author : Imai
//
//=============================================================================
#pragma once
#include "radar.h"

// マクロ定義
#define RADARENEMY_TEXTURE			("data/TEXTURE/teki.png")	// 画像
#define RADARENEMY_TEXTURE_SIZE_X	(50/10)		// テクスチャサイズ
#define RADARENEMY_TEXTURE_SIZE_Y	(50/10)		// 同上

#define RADARENEMY_TEXTURE_PATTERN_DIVIDE_X	(1)	// アニメパターンのテクスチャ内分割数（X)
#define RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define RADARENEMY_ANIM_PATTERN_NUM			(RADARENEMY_TEXTURE_PATTERN_DIVIDE_X*RADARENEMY_TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define RADARENEMY_TIME_ANIMATION			(4)	// アニメーションの切り替わるカウント

#define RADARENEMY_MAX						(4) // 敵の最大数
#define RADARENEMY_SPEEDX					(0.5) // 敵のスピード
#define RADARENEMY_SPEEDY						(0.5) // 敵のスピード
#define NX (SCREEN_WIDTH - RADARBOU_SIZE_X  / 2.0f)
#define NY (SCREEN_HEIGHT - RADARBOU_SIZE_Y / 2.0f)

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		ppos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	D3DXVECTOR3		vec;
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度
	float			distance;					//プレイヤーとエネミーの距離
} RADARENEMY;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRadarEnemy(int type);
void UninitRadarEnemy(void);
void UpdateRadarEnemy(void);
void DrawRadarEnemy(void);
void SetBullet(D3DXVECTOR3 pos);
RADARENEMY *GetRadarEnemy(void);


