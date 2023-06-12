//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Imai
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_SIZE_X       (40.0f)				//プレイヤーの大きさX
#define PLAYER_SIZE_Y       (40.0f)				//プレイヤーの大きさY
#define PLAYER_SIZE_Z       (40.0f)				//プレイヤーの大きさZ
#define ACCEL_TIME			(360)				//離陸時の加速時間
#define	TAKE_OFF_TIME		(ACCEL_TIME - 80)		//離陸までの時間

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 現在の位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	D3DXVECTOR3 vec;		// プレイヤーのベクトル

	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	bool use;				//使用
	int life;				//体力
	bool spdmode;			//スピードモード
	float	 xrot;			//X軸回転
	float	 yrot;			//X軸回転
	bool flaremode;			//フレアモード
	int	flarecnt;			//フレアのカウント
	int	flarepace;			//フレアのペース
	int	flaretime;			//フレアのタイマ
	int killcnt;			//敵を倒した数
	float acceleration;		//加速度
	int accelnow;			//離陸時の加速
	int capacity;			//弾の装弾数
	int bulletreloadtime;	//弾のリロードに必要な時間
	bool bulletuse;			//弾を使用中
	bool missilemode;       //弾の種類
	int missilecapacity;	//ミサイルの装弾数
	int missilereloadtime;	//ミサイルのリロードに必要な時間
	int missilepace;		//フレアのペース
	bool missleuse;			//ミサイルを使用中

	D3DXQUATERNION quorot;				//常に更新するクォータニオン		
	D3DXQUATERNION quorot2;				//値を格納するクォータニオン

	D3DXVECTOR3 Upvec;					//上方向ベクトル
	D3DXVECTOR3 Unitx;					//X軸
	D3DXVECTOR3 Unity;					//Y軸
	D3DXVECTOR3 Unitz;					//Z軸

	D3DXVECTOR3 axis;					//回転後の方向ベクトル	

} PLAYER;          

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);
D3DVECTOR Transform(const D3DVECTOR vec, const D3DXQUATERNION qua);

#endif
