//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Imai
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct CAMERA
{
	D3DXVECTOR3			pos;			// カメラのFPS視点(位置)
	D3DXVECTOR3			tpspos;			// カメラのTPS視点(位置)
	D3DXVECTOR3			at;				// カメラの注視点
	D3DXVECTOR3			up;				// カメラの上方向ベクトル
	D3DXVECTOR3			rot;			// カメラの回転
	float				len;			// カメラの視点と注視点の距離


	D3DXMATRIX			mtxView;		// ビューマトリックス
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス


	D3DXVECTOR3 oldrot;					//昔の角度
	D3DXVECTOR3 rotmv;					//角度の移動量

	bool fpsmode;						//FPSモード

	int fpsbgmcnt;							//BGMカウント
	int tpsbgmcnt;							//BGMカウント						

	D3DXMATRIX TurnCam; // 回転行列
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
D3DXVECTOR3 GetRotMove();
D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);
CAMERA *GetCamera();
#endif
