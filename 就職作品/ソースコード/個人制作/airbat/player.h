//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Imai
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_SIZE_X       (40.0f)				//�v���C���[�̑傫��X
#define PLAYER_SIZE_Y       (40.0f)				//�v���C���[�̑傫��Y
#define PLAYER_SIZE_Z       (40.0f)				//�v���C���[�̑傫��Z
#define ACCEL_TIME			(360)				//�������̉�������
#define	TAKE_OFF_TIME		(ACCEL_TIME - 80)		//�����܂ł̎���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rotDest;	// �ړI�̌���
	D3DXVECTOR3 vec;		// �v���C���[�̃x�N�g��

	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	bool use;				//�g�p
	int life;				//�̗�
	bool spdmode;			//�X�s�[�h���[�h
	float	 xrot;			//X����]
	float	 yrot;			//X����]
	bool flaremode;			//�t���A���[�h
	int	flarecnt;			//�t���A�̃J�E���g
	int	flarepace;			//�t���A�̃y�[�X
	int	flaretime;			//�t���A�̃^�C�}
	int killcnt;			//�G��|������
	float acceleration;		//�����x
	int accelnow;			//�������̉���
	int capacity;			//�e�̑��e��
	int bulletreloadtime;	//�e�̃����[�h�ɕK�v�Ȏ���
	bool bulletuse;			//�e���g�p��
	bool missilemode;       //�e�̎��
	int missilecapacity;	//�~�T�C���̑��e��
	int missilereloadtime;	//�~�T�C���̃����[�h�ɕK�v�Ȏ���
	int missilepace;		//�t���A�̃y�[�X
	bool missleuse;			//�~�T�C�����g�p��

	D3DXQUATERNION quorot;				//��ɍX�V����N�H�[�^�j�I��		
	D3DXQUATERNION quorot2;				//�l���i�[����N�H�[�^�j�I��

	D3DXVECTOR3 Upvec;					//������x�N�g��
	D3DXVECTOR3 Unitx;					//X��
	D3DXVECTOR3 Unity;					//Y��
	D3DXVECTOR3 Unitz;					//Z��

	D3DXVECTOR3 axis;					//��]��̕����x�N�g��	

} PLAYER;          

//*****************************************************************************
// �v���g�^�C�v�錾
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
