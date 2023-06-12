//=============================================================================
//
// レーダー処理 [radar.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RADAR		("data/TEXTURE/radar.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_RADAR_LOGO	("data/TEXTURE/bou5.png")		// 読み込むテクスチャファイル名
#define	RADAR_POS_X			(0)								// タイトルの表示位置
#define	RADAR_POS_Y			(0)								// タイトルの表示位置
#define	RADAR_SIZE_X		(640)							// タイトルの幅
#define	RADAR_SIZE_Y		(640)							// タイトルの高さ
#define	RADARBOU_POS_X		(350)							// タイトルロゴの表示位置
#define	RADARBOU_POS_Y		(350)							// タイトルロゴの表示位置
#define RADARBOU_SIZE_X		(90.0f)							//レーダー棒のサイズ		
#define RADARBOU_SIZE_Y		(90.0f)							//レーダー棒のサイズ

typedef struct
{
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
}RADAR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRadar(int type);
void UninitRadar(void);
void UpdateRadar(void);
void DrawRadar(void);

