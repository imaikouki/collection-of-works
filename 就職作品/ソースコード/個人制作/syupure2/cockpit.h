//=============================================================================
//
// �R�b�N�s�b�g���� [cockpit.h]
// Author : Imai
//
//=============================================================================
#ifndef _COCKPIT_H_
#define _COCKPIT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCockpit(void);
void UninitCockpit(void);
void UpdateCockpit(void);
void DrawCockpit(void);

void EnableCockpit(bool bEnable);
void ResetCockpit(int nTime = 999);

#endif
