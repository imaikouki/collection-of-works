//=============================================================================
//
// ���͏��� [input.h]
// Author : Imai
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_


//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD										// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE											// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD												// �錾����ƃp�b�h�ő���\�ɂȂ�


/* game pad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_SQ		0x00000010l	// ���{�^��(.rgbButtons[0]&0x80)
#define BUTTON_X		0x00000020l	// X�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_O		0x00000040l	// O�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_TRI		0x00000080l	// ���{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L1		0x00000100l	// L1�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R1		0x00000200l	// R1�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L2		0x00000400l	// L2�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R2		0x00000800l	// R2�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_SH	    0x00001000l	// SHARE�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_OP		0x00002000l	// OPTIONS�{�^��(.rgbButtons[9]&0x80)
#define BUTTON_L3		0x00004000l	// L3�{�^��(.rgbButtons[10]&0x80)
#define BUTTON_R3		0x00008000l	// R3�{�^��(.rgbButtons[11]&0x80)
#define BUTTON_PS		0x00010000l	// PS�{�^��(.rgbButtons[12]&0x80)
#define BUTTON_TOUCH	0x00020000l	// TOUCH�{�^��(.rgbButtons[13]&0x80)
#define BUTTON_CROSS_UP		0x00040000l	// �\���̏�{�^��(.rgbButtons[14]&0x80)
#define BUTTON_CROSS_DOWN	0x00080000l	// �\���̉��{�^��(.rgbButtons[15]&0x80)
#define BUTTON_CROSS_LEFT	0x00100000l	// �\���̍��{�^��(.rgbButtons[16]&0x80)
#define BUTTON_CROSS_RIGHT	0x00200000l	// �\���̉E�{�^��(.rgbButtons[18]&0x80)
#define BUTTON_RIGHT_UP		0x00400000l	// �\���̉E�{�^��(.rgbButtons[19]&0x80)
#define BUTTON_RIGHT_DOWN	0x00800000l	// �\���̉E�{�^��(.rgbButtons[20]&0x80)
#define BUTTON_RIGHT_LEFT	0x01000000l	// �\���̉E�{�^��(.rgbButtons[21]&0x80)
#define BUTTON_RIGHT_RIGHT	0x02000000l	// �\���̉E�{�^��(.rgbButtons[22]&0x80)


#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);


#endif