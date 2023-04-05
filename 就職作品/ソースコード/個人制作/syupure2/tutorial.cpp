//=============================================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author : Imai
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "life.h"
#include "cockpit.h"
#include "score.h"
#include "item.h"
#include "sound.h"
#include "enemy.h"
#include "enemybullet.h"
#include "colision.h"
#include "radar.h"
#include "meshsky.h"
#include "input.h"
#include "fade.h"
#include "rule.h"
#include "aircraftcarrier.h"

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTutorial(int type)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 3500.0f, 3500.0f);

	// 壁の初期化
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(-3500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(3500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);

	// 壁(裏側用)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// 空の初期化
	//InitMeshSky(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 8, 8000.0f, true);
	InitMeshSky(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7000, 8, 8000.0f, true);

	// 影の初期化
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	// エネミーの初期化
	InitEnemy();

	InitAircraftCarrier();

	// 弾の初期化
	InitBullet();

	// 弾の初期化
	InitEnemyBullet();

	// 爆発の初期化
	InitExplosion();

	// エフェクトの初期化
	InitEffect();

	// ライフの初期化
	InitLife();

	// タイマーの初期化
	InitCockpit();

	// スコアの初期化
	InitScore();


	//レーダーの初期化
	InitRadar(0);

	//ルールの初期化
	InitRule(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTutorial(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitMeshWall();

	//空の終了処理
	UninitMeshSky();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	// エネミーの終了処理
	UninitEnemy();

	// 弾の終了処理
	UninitBullet();

	// 弾の終了処理
	UninitEnemyBullet();

	// 爆発の終了処理
	UninitExplosion();

	// エフェトの終了処理
	UninitEffect();

	// ライフの終了処理
	UninitLife();

	// タイマーの終了処理
	UninitCockpit();

	// スコアの終了処理
	UninitScore();

	//// アイテムの終了処理
	//UninitItem();

	//レーダーの終了処理
	UninitRadar();

	//ルールの終了処理
	UninitRule();

	UninitAircraftCarrier();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTutorial(void)
{
	// カメラ更新
	UpdateCamera();

	// 地面処理の更新
	UpdateMeshField();

	// 壁処理の更新
	UpdateMeshWall();

	//空の更新処理
	UpdateMeshSky();

	// 影処理の更新
	UpdateShadow();

	// プレイヤー処理の更新
	UpdatePlayer();

	// エネミー処理の更新
	UpdateEnemy();

	UpdateAircraftCarrier();

	// 弾処理の更新
	UpdateBullet();

	// 弾処理の更新
	UpdateEnemyBullet();

	// 爆発処理の更新
	UpdateExplosion();

	// エフェクト処理の更新
	UpdateEffect();

	// ライフ処理の更新
	UpdateLife();

	// タイマー処理の更新
	UpdateCockpit();

	// スコア処理の更新
	UpdateScore();


	//レーダーの更新
	UpdateRadar();

	//ルールの更新処理
	UpdateRule();

	////アイテム処理の更新
	//UpdateItem();

	//当たり判定
	CheckHit();

	if (IsButtonTriggered(0, BUTTON_PS))
	{
		PlaySound(SOUND_LABEL_SE_COIN);
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTutorial(void)
{
	// カメラの設定
	SetCamera();

	// 地面処理の描画
	DrawMeshField();

	//空の描画処理
	DrawMeshSky();

	// 影処理の描画
	DrawShadow();

	//後ろを向いている間
	if (GetKeyboardPress(DIK_G) || IsButtonPressed(0, BUTTON_CROSS_UP))
	{
		// エフェクト処理の描画
		DrawEffect();

		// プレイヤー処理の描画
		DrawPlayer();
	}
	else
	{
		// プレイヤー処理の描画
		DrawPlayer();

		// エフェクト処理の描画
		DrawEffect();
	}

	// エネミー処理の描画
	DrawEnemy();

	//DrawAircraftCarrier();

	//// アイテム処理の描画
	//DrawItem();

	// 弾処理の描画
	//DrawBullet();

	// 弾処理の描画
	DrawEnemyBullet();

	//// 壁処理の描画
	//DrawMeshWall();

	// 爆発処理の描画
	DrawExplosion();

	//// ライフ処理の描画
	//DrawLife();

	// タイマー処理の描画
	DrawCockpit();

	// レーダーの描画
	DrawRadar();

	//ルールの描画
	DrawRule();

	//// スコア処理の描画
	//DrawScore();
}
