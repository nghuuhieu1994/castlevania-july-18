#ifndef __CINPUT_H__
#define __CINPUT_H__
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameLog.h"

class CInputDx9
{
	//Manage Input of Game
	LPDIRECTINPUT8			m_lpDirectInput;
	
	LPDIRECTINPUTDEVICE8	m_lpKeyBoardDevice;
	
	LPDIRECTINPUTDEVICE8	m_lpMouseDevice;

	DIMOUSESTATE2			m_mouseState;

	D3DXVECTOR2				m_cursorLocation;

	char					m_keyBoardBuffer[256];
public:
	CInputDx9();
	void InitializeInput();
	void InitializeKeyBoardDevice(HWND handleWindow);
	void InitializeMouseDevice(HWND handleWindow);

	void UpdateMouse();

	void UpdateKeyBoard();

	D3DXVECTOR2 GetCursorLocation();

	bool IsKeyDown(int keyCode);

	bool IsMouseRightClick();

	bool IsMouseLeftClick();

	~CInputDx9();
};

#endif