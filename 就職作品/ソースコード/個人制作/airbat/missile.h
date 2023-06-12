//=============================================================================
//
// ミサイル処理 [missile.h]
// Author : Imai
//
//=============================================================================
#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "main.h"


//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct MISSILE
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
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#define BULET_SIZE_Y       (10.0f)				//ミサイルの大きさ
#define BULET_SIZE_Z       (10.0f)				//ミサイルの大きさ
#define BULET_SIZE_X       (10.0f)				//ミサイルの大きさ
#define	MAX_MISSILE		   (128)				// ビルボード最大数

HRESULT InitMissile(void);
void UninitMissile(void);
void UpdateMissile(void);
void DrawMissile(void);
MISSILE *GetMissile();

int SetMissile(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer);
void DeleteMissile(int nIdxMissile);
#endif
