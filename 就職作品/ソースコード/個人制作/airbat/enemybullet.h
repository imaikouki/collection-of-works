//=============================================================================
//
// 弾処理 [enemybullet.h]
// Author : Imai
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXVECTOR3 move;		// 移動量
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nTimer;				// タイマー
	int nIdxShadow;			// 影ID
	bool bUse;				// 使用しているかどうか
} ENEMYBULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define ENEMYBULLET_SIZE_X       (10.0f)				//弾の大きさ
#define ENEMYBULLET_SIZE_Y       (10.0f)				//弾の大きさ
#define ENEMYBULLET_SIZE_Z       (10.0f)				//弾の大きさ
#define	MAX_ENEMYBULLET			 (1000)					// ビルボード最大数

HRESULT InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
ENEMYBULLET *GetEnemyBullet();
int SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer);
void DeleteEnemyBullet(int nIdxEnemyBullet);

#endif
