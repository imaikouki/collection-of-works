//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Imai
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "bulletscore.h"
#include "sound.h"
#include "fade.h"
#include "main.h"
#include "missile.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/b2.x"	// 読み込むモデル名
#define	PLAYER_RADIUS		(10.0f)						// 半径
//#define	VALUE_MOVE_PLAYER	(0.155f)				// 移動速度
#define	VALUE_MOVE_PLAYER	(10.0f)						// 移動速度
#define	VALUE_MOVE_PLAYER_SPEED	(20.0f)						// 移動速度

#define	RATE_MOVE_PLAYER	(0.015f)					// 移動慣性係数
#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// 回転速度
#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転慣性係数
#define	VALUE_MOVE_BULLET	(11.0f)						// 弾の移動速度
#define MAX_MOVE_X			(7000.0f)					//X座標の限界
#define MAX_MOVE_Y			(900.0f)					//X座標の限界
#define MAX_MOVE_Z			(7000.0f)					//Z座標の限界
#define ROTSPDX			    (0.3f)					//Z座標の限界
#define ROTSPDY			    (1.0f)					//Z座標の限界
#define ROTSPDZ			    (1.0f)					//Z座標の限界
#define MAXROTX				(1.5f)					//最大の回転加速度
#define MAXROTZ				(1.5f)					//最大の回転加速度
#define CAPACITY			(100)					//弾の最大数
#define	MISSILE_CAPACITY		(10)				//ミサイルの最大数
#define BULLET_RELOAD_TIME	(300)					//弾のリロードに必要な時間
#define MISSILE_RELOAD_TIME	(420)					//ミサイルのリロードに必要な時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshPlayer;				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffPlayer;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer;			// 属性情報の総数

D3DXMATRIX			g_mtxWorldPlayer;			// ワールドマトリックス
PLAYER				g_player;					// プレイヤーワーク

float moveaccelx;
float moveaccelz;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pD3DTexturePlayer = NULL;
	g_pMeshPlayer = NULL;
	g_pD3DXMatBuffPlayer = NULL;

	g_player.pos = D3DXVECTOR3(0.0f,260.0f, 0.0f);
	g_player.vec = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;
	g_player.use = true;
	g_player.life = 60;
	g_player.spdmode = false;
	g_player.xrot = 0.0f;
	g_player.yrot = 0.0f;
	g_player.flarecnt = 0;
	g_player.flarepace = 0;
	g_player.flaremode = false;
	g_player.flaretime = 300;
	g_player.killcnt = 0;
	g_player.acceleration = 0.0f;
	g_player.accelnow = 0;
	moveaccelx = 0.0f;
	moveaccelz = 0.0f;
	g_player.missilemode = false;
	g_player.capacity = CAPACITY;
	g_player.bulletreloadtime = 0;
	g_player.bulletuse = true;
	g_player.missilecapacity = MISSILE_CAPACITY;
	g_player.missilereloadtime = 0;
	g_player.missilepace = 30;
	g_player.missleuse = true;
	g_player.Unitx = D3DXVECTOR3(1.0f, 0.0f, 0.0f); // 任意の中心軸
	g_player.Unity = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // 任意の中心軸
	g_player.Unitz = D3DXVECTOR3(0.0f, 0.0f, 1.0f); // 任意の中心軸
	g_player.axis =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.quorot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	g_player.quorot2 = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	g_player.Upvec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	if(FAILED(D3DXLoadMeshFromX(MODEL_PLAYER,
								D3DXMESH_SYSTEMMEM,
								pDevice,
								NULL,
								&g_pD3DXMatBuffPlayer,
								NULL,
								&g_nNumMatPlayer,
								&g_pMeshPlayer)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー
#endif

	// 影の設定
	g_player.nIdxShadow = SetShadow(g_player.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);		// 影の設定

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if(g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	if(g_pMeshPlayer != NULL)
	{// メッシュの開放
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	if(g_pD3DXMatBuffPlayer != NULL)
	{// マテリアルの開放
		g_pD3DXMatBuffPlayer->Release();
		g_pD3DXMatBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//クォータニオンの初期化
	g_player.quorot2 = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	// カメラの向き取得
	D3DXVECTOR3 rotCamera;
	rotCamera = GetRotCamera();
	
	//離陸の処理
	if (g_player.accelnow <= ACCEL_TIME)
	{
		g_player.accelnow++;

		if (g_player.accelnow >= TAKE_OFF_TIME &&g_player.accelnow <= ACCEL_TIME)
		{
			g_player.axis = Transform(-g_player.Unitx, g_player.quorot);
			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(0.1f));
		}

	}

	else
	{
		if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_RIGHT_UP))	//上押されたとき
		{
			g_player.axis = Transform(g_player.Unitx, g_player.quorot);


			if (moveaccelx <= MAXROTX)
			{
				moveaccelx += 0.1f;
			}

			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDX * moveaccelx));
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_RIGHT_DOWN))	//下押されたとき
		{
			g_player.axis = Transform(g_player.Unitx, g_player.quorot);

			if (moveaccelx >= -MAXROTX)
			{
				moveaccelx -= 0.1f;
			}

			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDX * moveaccelx));
		}

		//今の姿勢にクォータニオンで回転
		D3DXQuaternionMultiply(&g_player.quorot, &g_player.quorot, &g_player.quorot2);

		if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT_RIGHT))	//右押されたとき
		{
			g_player.axis = Transform(g_player.Unitz, g_player.quorot);

			if (moveaccelz <= MAXROTZ)
			{
				moveaccelz -= 0.1f;
			}

			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDZ * moveaccelz));
		}
		else if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_RIGHT_LEFT))	//左押されたとき
		{
			g_player.axis = Transform(g_player.Unitz, g_player.quorot);

			if (moveaccelz >= -MAXROTZ)
			{
				moveaccelz += 0.1f;
			}

			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDZ * moveaccelz));
		}

		//今の姿勢にクォータニオンで回転
		D3DXQuaternionMultiply(&g_player.quorot, &g_player.quorot, &g_player.quorot2);

		if (GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT))	//右押されたとき
		{
			g_player.axis = Transform(g_player.Unity, g_player.quorot);
			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDY / 5));
		}
		else if (GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT))	//左押されたとき
		{
			g_player.axis = Transform(-g_player.Unity, g_player.quorot);
			//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
			D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(ROTSPDY / 5));
		}
	}

	if (g_player.pos.x < -10000.0f || g_player.pos.x > 10000.0f || g_player.pos.y > 6000.0f || g_player.pos.z > 10000.0f || g_player.pos.z < -10000.0f)
	{
		g_player.axis = Transform(-g_player.Unitx, g_player.quorot);

		//ｚ軸を中心に 0度　回転するクォータニオン'y'を生成
		D3DXQuaternionRotationAxis(&g_player.quorot2, &g_player.axis, D3DXToRadian(1));

	}


	//今の姿勢にクォータニオンで回転
	D3DXQuaternionMultiply(&g_player.quorot, &g_player.quorot, &g_player.quorot2);

	//移動方向ベクトルを出す
	g_player.axis = Transform(g_player.Unitz, g_player.quorot);

	//移動量の計算
	if (g_player.spdmode == false)
	{
		g_player.move.x = g_player.axis.x * VALUE_MOVE_PLAYER;
		g_player.move.y = g_player.axis.y * VALUE_MOVE_PLAYER;
		g_player.move.z = g_player.axis.z * VALUE_MOVE_PLAYER;

	}
	else if(g_player.spdmode == true)
	{
		g_player.move.x = g_player.axis.x * VALUE_MOVE_PLAYER_SPEED;
		g_player.move.y = g_player.axis.y * VALUE_MOVE_PLAYER_SPEED;
		g_player.move.z = g_player.axis.z * VALUE_MOVE_PLAYER_SPEED;
	}

	if (g_player.acceleration <= 1.0f)
	{
		g_player.acceleration = g_player.acceleration + 0.005f;
	}

	//チュートリアルは移動させない
	MODE g_mode=GetMode();
	switch (g_mode)
	{
	case MODE_GAME:
		//走りっぱなし
		g_player.pos += g_player.move * g_player.acceleration;

		if (g_player.accelnow <= 180)
		{
			g_player.pos.y = 260.0f;
		}

		break;

	case MODE_TUTORIAL:
		//その場にとどまる
		g_player.accelnow += ACCEL_TIME;
		break;
	}

	//加速モード
	if (GetKeyboardTrigger(DIK_X) || IsButtonTriggered(0, BUTTON_L3))
	{
		if (g_player.spdmode == false)
		{
			g_player.spdmode = true;
		}
		else
		{
			g_player.spdmode = false;
		}
	}

	if (g_player.flarecnt == 0)	//フレアのリロードが終わったとき
	{
		if (g_player.flaremode == false)//フレアモードオフ
		{
			if (GetKeyboardTrigger(DIK_Z) || IsButtonTriggered(0, BUTTON_CROSS_DOWN))//フレア発射
			{
				g_player.flaremode = true;

				//フレア発射音声 
				PlaySoundB(SOUND_LABEL_SE_Flare,100);

			}
		}

		if (g_player.flaremode == true)//フレアモードがオンの時
		{
			if (g_player.flaretime >= 0)//フレアの発射時間
			{
				if (g_player.flarepace == 0)//フレアの発射ペース
				{
					D3DXVECTOR3 pos;

					pos.x = g_player.pos.x;
					pos.y = g_player.pos.y;
					pos.z = g_player.pos.z;

					g_player.axis = Transform(-g_player.Unity, g_player.quorot);

					// 真ん中のエフェクトの設定
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 14.0f, 14.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.30f), 10.0f, 10.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.15f), 5.0f, 5.0f, 600);

					g_player.axis = Transform(D3DXVECTOR3(1.0f, -1.0f, 0.0f), g_player.quorot);

					// 右のエフェクトの設定
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 14.0f, 14.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.30f), 10.0f, 10.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.15f), 5.0f, 5.0f, 600);

					g_player.axis = Transform(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), g_player.quorot);

					// 左のエフェクトの設定
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 14.0f, 14.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.30f), 10.0f, 10.0f, 600);
					SetEffect(pos, g_player.axis * 2,
						D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.15f), 5.0f, 5.0f, 600);

					g_player.flarepace = 20;
					g_player.flaretime--;
				}
				else
				{
					g_player.flarepace--;
				}

				g_player.flaretime--;
			}
			else
			{
				g_player.flaretime = 300;
				g_player.flaremode = false;
				g_player.flarecnt = 600;
				StopSoundB(SOUND_LABEL_SE_Flare);
			}
		}
	}
	else
	{
		g_player.flarecnt--;
	}

	//弾の切り替え
	if (IsButtonTriggered(0, BUTTON_TRI) || GetKeyboardTrigger(DIK_1))
	{
		if (g_player.missilemode == false)
		{
			g_player.missilemode = true;
			ChangeBulletScore(g_player.missilecapacity);
		}

		else
		{
			g_player.missilemode = false;
			ChangeBulletScore(g_player.capacity);
		}
	}

	if (g_player.bulletreloadtime > 0)
	{
		g_player.bulletreloadtime -= 1;
	}

	if (g_player.missilereloadtime > 0)
	{
		g_player.missilereloadtime -= 1;
	}

	if (g_player.missilepace > 0)
	{
		g_player.missilepace -= 1;
	}

	if (g_player.bulletuse == false && g_player.bulletreloadtime == 0)
	{
		g_player.capacity = CAPACITY;
		g_player.bulletuse = true;

		if (g_player.missilemode == false)
		{
			ChangeBulletScore(g_player.capacity);
		}
	}

	if (g_player.missleuse == false && g_player.missilereloadtime == 0)
	{
		g_player.missilecapacity = MISSILE_CAPACITY;
		g_player.missleuse = true;
		if (g_player.missilemode == true)
		{
			ChangeBulletScore(g_player.missilecapacity);
		}
	}
	
	// 弾発射
	if(GetKeyboardPress(DIK_SPACE) || IsButtonPressed(0, BUTTON_L1) || IsMouseRightPressed())
	{
		
		if (g_player.missilemode == false)
		{
			if (g_player.bulletreloadtime == 0)
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				pos.x = g_player.pos.x;
				pos.y = g_player.pos.y;
				pos.z = g_player.pos.z;

				move.x = g_player.move.x * VALUE_MOVE_BULLET;
				move.y = g_player.move.y * VALUE_MOVE_BULLET;
				move.z = g_player.move.z * VALUE_MOVE_BULLET;

				SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

				// SE再生
				PlaySound(SOUND_LABEL_SE_SHOT);

				g_player.capacity -= 1;

				if (g_player.capacity == 0)
				{
					g_player.bulletreloadtime = BULLET_RELOAD_TIME;
					g_player.bulletuse = false;
				}
				ChangeBulletScore(g_player.capacity);
			}
		}

		if (g_player.missilemode == true)
		{
			if (g_player.missilereloadtime == 0)
			{
				if (g_player.missilepace == 0)
				{
					g_player.axis = Transform(g_player.Unitx, g_player.quorot);

					D3DXVECTOR3 pos;
					D3DXVECTOR3 move;

					if (g_player.missilecapacity % 2 == 0)
					{
						pos = g_player.pos + g_player.axis * 15;
					}
					else
					{
						pos = g_player.pos - g_player.axis * 15;
					}

					move.x = g_player.move.x * VALUE_MOVE_BULLET;
					move.y = g_player.move.y * VALUE_MOVE_BULLET;
					move.z = g_player.move.z * VALUE_MOVE_BULLET;

					SetMissile(pos, move, 4.0f, 4.0f, 60 * 4);

					// SE再生
					PlaySound(SOUND_LABEL_SE_MISSILE);

					g_player.missilecapacity -= 1;
					g_player.missilepace = 30;

					if (g_player.missilecapacity == 0)
					{
						g_player.missilereloadtime = MISSILE_RELOAD_TIME;
						g_player.missleuse = false;
					}
					ChangeBulletScore(g_player.missilecapacity);
				}
			}
		}
	}

	// 影の位置設定
	{
		SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

		float fSizeX = 20.0f + (g_player.pos.y - 10.0f) * 0.05f;
		if(fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (g_player.pos.y - 10.0f) * 0.05f;
		if(fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(g_player.nIdxShadow, fSizeX, fSizeY);

		float colA = (200.0f - (g_player.pos.y - 10.0f)) / 400.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

	//エフェクト処理
	D3DXVECTOR3 pos;

	g_player.axis = Transform(-g_player.Unitz, g_player.quorot);

	pos = g_player.pos + g_player.axis*3;

	if (g_player.spdmode == false)
	{
		// 真ん中のエフェクトの設定
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.85f, 0.0f, 0.0f, 1.0f), 14.0f, 14.0f, 5);
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.0f, 0.0f, 0.30f), 10.0f, 10.0f, 5);
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.0f, 0.0f, 0.15f), 5.0f, 5.0f, 5);

		g_player.axis = Transform(g_player.Unitx, g_player.quorot);

		// 右のエフェクトの設定
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.20f), 14.0f / 3.0f, 14.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.1f), 10.0f / 3.0f, 10.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f / 3.0f, 5.0f / 3.0f, 600);

		g_player.axis = Transform(-g_player.Unitx, g_player.quorot);

		// 左のエフェクトの設定
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.20f), 14.0f / 3.0f, 14.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.1f), 10.0f / 3.0f, 10.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f / 3.0f, 5.0f / 3.0f, 600);

	}
	else
	{
		// 真ん中のエフェクトの設定
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.85f, 0.0f, 0.0f, 1.0f), 14.0f, 14.0f, 5);
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.0f, 0.0f, 0.30f), 10.0f, 10.0f, 5);
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.0f, 0.0f, 0.15f), 5.0f, 5.0f, 5);

		g_player.axis = Transform(g_player.Unitx, g_player.quorot);

		// 右のエフェクトの設定
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.20f), 14.0f / 3.0f, 14.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.1f), 10.0f / 3.0f, 10.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f / 3.0f, 5.0f / 3.0f, 600);

		g_player.axis = Transform(-g_player.Unitx, g_player.quorot);

		// 右のエフェクトの設定
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.20f), 14.0f / 3.0f, 14.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.1f), 10.0f / 3.0f, 10.0f / 3.0f, 600);
		SetEffect(pos + g_player.axis * 25, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f / 3.0f, 5.0f / 3.0f, 600);
	}

	//海水に落ちたらゲーム終了
	if (g_player.pos.y <= 0)
	{
			SetFade(FADE_OUT);
	}

	g_player.axis = Transform(g_player.Unity, g_player.quorot);
	g_player.Upvec = g_player.axis;

	moveaccelx *= 0.9f;
	moveaccelz *= 0.9f;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	CAMERA*camera = GetCamera();

	if (camera->fpsmode == false || IsButtonPressed(0, BUTTON_CROSS_UP))
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxRot, mtxTranslate;
		D3DXMATERIAL *pD3DXMat;

		D3DXMATRIX TurnMat; // 回転行列

		//クォータニオンをマトリックスに変換
		D3DXMatrixRotationQuaternion(&TurnMat, &g_player.quorot);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldPlayer);

		// 回転を反映
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &TurnMat);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_player.pos.x, g_player.pos.y, g_player.pos.z);
		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			// 描画
			g_pMeshPlayer->DrawSubset(nCntMat);
		}

		{// マテリアルをデフォルトに戻す
			D3DXMATERIAL mat;

			mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			pDevice->SetMaterial(&mat.MatD3D);
		}
	}
}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.pos;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

//=============================================================================
// ベクトルをクォータニオンで回転させる処理
//=============================================================================
D3DVECTOR Transform(const D3DVECTOR vec, const D3DXQUATERNION qua)
{
	// クォータニオンの各成分を2倍にする
	float x = qua.x * 2;
	float y = qua.y * 2;
	float z = qua.z * 2;

   // 回転変換の各成分を計算する
	float wx = qua.w*x;
	float wy = qua.w*y;
	float wz = qua.w*z;

	float xx = qua.x*x;
	float xy = qua.x*y;
	float xz = qua.x*z;

	float yy = qua.y*y;
	float yz = qua.y*z;

	float zz = qua.z*z;

	// 回転変換を適用して新しいベクトルを計算する
	return D3DXVECTOR3(
		((vec.x * ((1.0f - yy) - zz)) + (vec.y * (xy - wz))) + (vec.z * (xz + wy)),
		((vec.x * (xy + wz)) + (vec.y * ((1.0f - xx) - zz))) + (vec.z * (yz - wx)),
		((vec.x * (xz - wy)) + (vec.y * (yz + wx))) + (vec.z * ((1.0f - xx) - yy)));
}