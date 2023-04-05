//=============================================================================
//
// 入力処理 [input.h]
// Author : Imai
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************

// プログラム分けするときに使う
#define	USE_KEYBOARD										// 宣言するとキーボードで操作可能になる
#define	USE_MOUSE											// 宣言するとマウスで操作可能になる
#define	USE_PAD												// 宣言するとパッドで操作可能になる


/* game pad情報 */
#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)
#define BUTTON_SQ		0x00000010l	// ■ボタン(.rgbButtons[0]&0x80)
#define BUTTON_X		0x00000020l	// Xボタン(.rgbButtons[1]&0x80)
#define BUTTON_O		0x00000040l	// Oボタン(.rgbButtons[2]&0x80)
#define BUTTON_TRI		0x00000080l	// ▲ボタン(.rgbButtons[3]&0x80)
#define BUTTON_L1		0x00000100l	// L1ボタン(.rgbButtons[4]&0x80)
#define BUTTON_R1		0x00000200l	// R1ボタン(.rgbButtons[5]&0x80)
#define BUTTON_L2		0x00000400l	// L2ボタン(.rgbButtons[6]&0x80)
#define BUTTON_R2		0x00000800l	// R2ボタン(.rgbButtons[7]&0x80)
#define BUTTON_SH	    0x00001000l	// SHAREボタン(.rgbButtons[8]&0x80)
#define BUTTON_OP		0x00002000l	// OPTIONSボタン(.rgbButtons[9]&0x80)
#define BUTTON_L3		0x00004000l	// L3ボタン(.rgbButtons[10]&0x80)
#define BUTTON_R3		0x00008000l	// R3ボタン(.rgbButtons[11]&0x80)
#define BUTTON_PS		0x00010000l	// PSボタン(.rgbButtons[12]&0x80)
#define BUTTON_TOUCH	0x00020000l	// TOUCHボタン(.rgbButtons[13]&0x80)
#define BUTTON_CROSS_UP		0x00040000l	// 十字の上ボタン(.rgbButtons[14]&0x80)
#define BUTTON_CROSS_DOWN	0x00080000l	// 十字の下ボタン(.rgbButtons[15]&0x80)
#define BUTTON_CROSS_LEFT	0x00100000l	// 十字の左ボタン(.rgbButtons[16]&0x80)
#define BUTTON_CROSS_RIGHT	0x00200000l	// 十字の右ボタン(.rgbButtons[18]&0x80)
#define BUTTON_RIGHT_UP		0x00400000l	// 十字の右ボタン(.rgbButtons[19]&0x80)
#define BUTTON_RIGHT_DOWN	0x00800000l	// 十字の右ボタン(.rgbButtons[20]&0x80)
#define BUTTON_RIGHT_LEFT	0x01000000l	// 十字の右ボタン(.rgbButtons[21]&0x80)
#define BUTTON_RIGHT_RIGHT	0x02000000l	// 十字の右ボタン(.rgbButtons[22]&0x80)


#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

//*****************************************************************************
// プロトタイプ宣言
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
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);


#endif