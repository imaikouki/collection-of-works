//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Imai
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_MISSILE,		// �~�T�C�����ˉ�
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_COIN,		// �Փˉ�0
	SOUND_LABEL_SE_TPS,			//TPS�̎���BGM
	SOUND_LABEL_SE_FPS,			//FPS�̎���BGM
	SOUND_LABEL_SE_Flare,		//�t���A�ˏo����SE
	SOUND_LABEL_MAX ,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
HRESULT PlaySoundB(SOUND_LABEL label,int i);//i�̐������J��Ԃ�
void StopSound(SOUND_LABEL label);
void StopSound(void);
void StopSoundB(SOUND_LABEL label);
void StopSoundB(void);

#endif
