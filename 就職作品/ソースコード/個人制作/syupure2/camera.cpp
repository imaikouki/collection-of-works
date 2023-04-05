//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Imai
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include <time.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(100000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	INTERVAL_CAMERA_R	(12.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.05f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(1.0f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(100.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

#define	POS_X_CAM		(0.0f)						// カメラの初期位置(X座標)
#define	POS_Y_CAM		(0.0f)						// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-150.0f)					// カメラの初期位置(Z座標)

#define	ROT_Y_MOVE			(240.0f)						// カメラの感度(Y軸)
#define CAMERA_MOVESPEED	(0.05f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA			g_Camera;					// カメラデータ
D3DXVECTOR3		g_posCameraPDest;			// カメラの視点の目的位置
D3DXVECTOR3		g_posCameraRDest;			// カメラの注視点の目的位置
D3DXVECTOR3		g_rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
float			g_fLengthIntervalPlayer;	// プレイヤーと注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	g_posCameraPDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	g_posCameraRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.oldrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rotmv = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx,vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);
	g_fLengthIntervalPlayer = INTERVAL_CAMERA_R;

	g_Camera.tpspos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.pos = D3DXVECTOR3(0, 0, 0);
	g_Camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.fpsmode = false;


	g_Camera.fpsbgmcnt = 0;
	g_Camera.tpsbgmcnt = 0;
	g_Camera.camcnt = 0;


	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	///* ランダム用初期設定 */
	//srand((unsigned)time(NULL));

	D3DXVECTOR3 posPlayer;
	D3DXVECTOR3 movePlayer;
	D3DXVECTOR3 ordcamerapos;
	PLAYER*player = GetPlayer();

	float fLength;

	// モデルの位置取得
	posPlayer = GetPositionPlayer();

	// モデルの移動量取得
	movePlayer = GetMovePlayer();


	//カーソル座標の取得
	POINT curpos;
	GetCursorPos(&curpos);


	//角度の移動量を計算
	g_Camera.rotmv = g_rotCamera - g_Camera.oldrot;

	//角度のの引き渡し
	g_Camera.oldrot = g_rotCamera;

	//fpsmode
	if (g_Camera.fpsmode == true) //fpsmode
	{
		//// 視点の目的位置
		//fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;
		//g_posCameraPDest.y = posPlayer.y + CHASE_HEIGHT_P;
		//g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

		//// 注視点の目的位置
		//fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
		//g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
		//g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

		// 視点の補正
		g_Camera.pos.x = posPlayer.x;
		g_Camera.pos.y = posPlayer.y;
		g_Camera.pos.z = posPlayer.z;

		g_Camera.at.x = posPlayer.x + movePlayer.x * 20;
		g_Camera.at.y = posPlayer.y + movePlayer.y * 20;
		g_Camera.at.z = posPlayer.z + movePlayer.z * 20;

		//後ろを向く
		if (GetKeyboardPress(DIK_G) || IsButtonPressed(0, BUTTON_CROSS_UP))
		{
			ordcamerapos = g_Camera.pos;
			g_Camera.pos = g_Camera.at + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			g_Camera.at = ordcamerapos;
		}

		if (g_Camera.fpsbgmcnt == 0)
		{
			// SE再生
			PlaySound(SOUND_LABEL_SE_FPS);
			g_Camera.fpsbgmcnt = 900;
		}
		else
		{
			g_Camera.fpsbgmcnt--;
		}


		//fpsmodeoff
		if (GetKeyboardTrigger(DIK_F) || IsButtonTriggered(0, BUTTON_R3))
		{
			g_Camera.fpsbgmcnt = 0;
			//PlaySound(NULL, NULL, 0);
			g_Camera.fpsmode = false;
			// SE再生
			StopSound(SOUND_LABEL_SE_FPS);

		}
	}

	//tpsmode
	else 
	{
		//// 視点の目的位置
		//fLength = sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraPDest.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera - sinf(rotPlayer.y) * fLength;
		//g_posCameraPDest.y = posPlayer.y + CHASE_HEIGHT_P;
		//g_posCameraPDest.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera - cosf(rotPlayer.y) * fLength;

		//// 注視点の目的位置
		//fLength = g_fLengthIntervalPlayer + sqrtf(movePlayer.x * movePlayer.x + movePlayer.z * movePlayer.z) * 6.0f;
		//g_posCameraRDest.x = posPlayer.x - sinf(rotPlayer.y) * fLength;
		//g_posCameraRDest.y = posPlayer.y - CHASE_HEIGHT_R;
		//g_posCameraRDest.z = posPlayer.z - cosf(rotPlayer.y) * fLength;

		// 視点の補正
		g_Camera.pos.x += (g_posCameraPDest.x - g_Camera.pos.x) * RATE_CHASE_CAMERA_P;
		g_Camera.pos.y += (g_posCameraPDest.y - g_Camera.pos.y) * RATE_CHASE_CAMERA_P;
		g_Camera.pos.z += (g_posCameraPDest.z - g_Camera.pos.z) * RATE_CHASE_CAMERA_P;

		g_Camera.pos.x = posPlayer.x - movePlayer.x * 15;
		g_Camera.pos.y = posPlayer.y - movePlayer.y * 15+ player->Upvec.y*10;
		g_Camera.pos.z = posPlayer.z - movePlayer.z * 15;
		if (player->accelnow <= ACCEL_TIME)
		{
			g_Camera.pos.y = 400.0f;
		}

		// 注視点の補正
		g_Camera.at.x += (g_posCameraRDest.x - g_Camera.at.x) * RATE_CHASE_CAMERA_R;
		g_Camera.at.y += (g_posCameraRDest.y - g_Camera.at.y) * RATE_CHASE_CAMERA_R;
		g_Camera.at.z += (g_posCameraRDest.z - g_Camera.at.z) * RATE_CHASE_CAMERA_R;

		g_Camera.at.x = g_Camera.at.x = posPlayer.x + movePlayer.x * 10;
		g_Camera.at.y = posPlayer.y + movePlayer.y * 10;
		g_Camera.at.z = posPlayer.z + movePlayer.z * 10;

		//後ろを向く
		if (GetKeyboardPress(DIK_G)|| IsButtonPressed(0, BUTTON_CROSS_UP))
		{
			ordcamerapos = g_Camera.pos;
			g_Camera.pos = g_Camera.at + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			g_Camera.at = ordcamerapos;
		}

		if (g_Camera.tpsbgmcnt == 0)
		{
			// SE再生
			PlaySound(SOUND_LABEL_SE_TPS);
			g_Camera.tpsbgmcnt = 900;
		}
		else
		{
			g_Camera.tpsbgmcnt--;
		}

		//fpsmodeoff
		if (GetKeyboardTrigger(DIK_F) || IsButtonTriggered(0, BUTTON_R3))
		{
			g_Camera.fpsmode = true;
			g_Camera.tpsbgmcnt = 0;
			StopSound(SOUND_LABEL_SE_TPS);
			g_Camera.tpsbgmcnt = 0;
		}
	}

	if (g_rotCamera.y >= D3DX_PI*2 || g_rotCamera.y <= -D3DX_PI*2)
	{
		g_rotCamera.y = 0.0f;
	}}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	PLAYER*player = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_Camera.pos,		// カメラの視点
						&g_Camera.at,		// カメラの注視点
						&player->Upvec);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// 視野角
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// アスペクト比
								VIEW_NEAR_Z,									// ビュー平面のNearZ値
								VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotMove(void)
{
	return g_Camera.rotmv;
}
//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}

//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_Camera;
}
