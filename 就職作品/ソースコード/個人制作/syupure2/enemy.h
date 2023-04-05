//=============================================================================
//
// エネミーモデル処理 [enemy.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAX_ENEMY		(10)					// エネミーの数

#define ENEMY_SIZE_X       (150.0f)				//エネミーの大きさ
#define ENEMY_SIZE_Y       (150.0f)
#define ENEMY_SIZE_Z       (150.0f)

struct ENEMY
{
	D3DXVECTOR3			pos;				// モデルの位置
	D3DXVECTOR3			rot;				// モデルの向き(回転)
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			move;				// モデルの移動量

	float				spd;				// 移動スピード

	LPDIRECT3DTEXTURE9	pD3DTexture;		// テクスチャへのポインタ
	LPD3DXMESH			pD3DXMesh;			// メッシュ情報へのポインタ
	LPD3DXBUFFER		pD3DXBuffMat;		// マテリアル情報へのポインタ
	DWORD				nNumMat;			// マテリアル情報の数

	int					tbl_cnt;			//テーブルのカウント
	float				move_time;			//テーブルの時間
	float				posplus;
	int					pospluscnt;
	bool				posplususe;

	D3DXMATRIX			mtxWorld;			// ワールドマトリックス

	int recnt;
	bool				use;
	int					shadowIdx;			// 影のインデックス番号
	int					life;				// 体力
	int					randx;				//エネミーのランダム位置
	int					randy;				//エネミーのランダム位置
	int					randz;				//エネミーのランダム位置
	int					descnt;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

ENEMY *GetEnemy();