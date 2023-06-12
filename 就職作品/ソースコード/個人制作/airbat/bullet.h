//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Imai
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"


//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct BULLET
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
} ;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#define BULET_SIZE_X       (10.0f)				//弾の大きさ
#define BULET_SIZE_Y       (10.0f)
#define BULET_SIZE_Z       (10.0f)
#define	MAX_BULLET		   (128)							// ビルボード最大数

HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBullet();

int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer);
void DeleteBullet(int nIdxBullet);
#endif
