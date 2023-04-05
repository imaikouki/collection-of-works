//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
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
// ����������
//=============================================================================
HRESULT InitTutorial(int type)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 3500.0f, 3500.0f);

	// �ǂ̏�����
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(-3500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(3500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 50, 70.0f, 70.0f);

	// ��(�����p)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// ��̏�����
	//InitMeshSky(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 8, 8000.0f, true);
	InitMeshSky(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 7000, 8, 8000.0f, true);

	// �e�̏�����
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	// �G�l�~�[�̏�����
	InitEnemy();

	InitAircraftCarrier();

	// �e�̏�����
	InitBullet();

	// �e�̏�����
	InitEnemyBullet();

	// �����̏�����
	InitExplosion();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���C�t�̏�����
	InitLife();

	// �^�C�}�[�̏�����
	InitCockpit();

	// �X�R�A�̏�����
	InitScore();


	//���[�_�[�̏�����
	InitRadar(0);

	//���[���̏�����
	InitRule(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorial(void)
{
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitMeshWall();

	//��̏I������
	UninitMeshSky();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�l�~�[�̏I������
	UninitEnemy();

	// �e�̏I������
	UninitBullet();

	// �e�̏I������
	UninitEnemyBullet();

	// �����̏I������
	UninitExplosion();

	// �G�t�F�g�̏I������
	UninitEffect();

	// ���C�t�̏I������
	UninitLife();

	// �^�C�}�[�̏I������
	UninitCockpit();

	// �X�R�A�̏I������
	UninitScore();

	//// �A�C�e���̏I������
	//UninitItem();

	//���[�_�[�̏I������
	UninitRadar();

	//���[���̏I������
	UninitRule();

	UninitAircraftCarrier();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorial(void)
{
	// �J�����X�V
	UpdateCamera();

	// �n�ʏ����̍X�V
	UpdateMeshField();

	// �Ǐ����̍X�V
	UpdateMeshWall();

	//��̍X�V����
	UpdateMeshSky();

	// �e�����̍X�V
	UpdateShadow();

	// �v���C���[�����̍X�V
	UpdatePlayer();

	// �G�l�~�[�����̍X�V
	UpdateEnemy();

	UpdateAircraftCarrier();

	// �e�����̍X�V
	UpdateBullet();

	// �e�����̍X�V
	UpdateEnemyBullet();

	// ���������̍X�V
	UpdateExplosion();

	// �G�t�F�N�g�����̍X�V
	UpdateEffect();

	// ���C�t�����̍X�V
	UpdateLife();

	// �^�C�}�[�����̍X�V
	UpdateCockpit();

	// �X�R�A�����̍X�V
	UpdateScore();


	//���[�_�[�̍X�V
	UpdateRadar();

	//���[���̍X�V����
	UpdateRule();

	////�A�C�e�������̍X�V
	//UpdateItem();

	//�����蔻��
	CheckHit();

	if (IsButtonTriggered(0, BUTTON_PS))
	{
		PlaySound(SOUND_LABEL_SE_COIN);
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorial(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// �n�ʏ����̕`��
	DrawMeshField();

	//��̕`�揈��
	DrawMeshSky();

	// �e�����̕`��
	DrawShadow();

	//���������Ă����
	if (GetKeyboardPress(DIK_G) || IsButtonPressed(0, BUTTON_CROSS_UP))
	{
		// �G�t�F�N�g�����̕`��
		DrawEffect();

		// �v���C���[�����̕`��
		DrawPlayer();
	}
	else
	{
		// �v���C���[�����̕`��
		DrawPlayer();

		// �G�t�F�N�g�����̕`��
		DrawEffect();
	}

	// �G�l�~�[�����̕`��
	DrawEnemy();

	//DrawAircraftCarrier();

	//// �A�C�e�������̕`��
	//DrawItem();

	// �e�����̕`��
	//DrawBullet();

	// �e�����̕`��
	DrawEnemyBullet();

	//// �Ǐ����̕`��
	//DrawMeshWall();

	// ���������̕`��
	DrawExplosion();

	//// ���C�t�����̕`��
	//DrawLife();

	// �^�C�}�[�����̕`��
	DrawCockpit();

	// ���[�_�[�̕`��
	DrawRadar();

	//���[���̕`��
	DrawRule();

	//// �X�R�A�����̕`��
	//DrawScore();
}
