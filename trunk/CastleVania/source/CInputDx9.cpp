#include "CInputDx9.h"

CInputDx9::CInputDx9() : 
	m_lpDirectInput(NULL),
	m_lpKeyBoardDevice(NULL),
	m_lpMouseDevice(NULL)
{

}

void CInputDx9::InitializeInput()
{
	HRESULT result;

	result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_lpDirectInput,
		NULL);

	if (result != D3D_OK)
	{
		//(Logger::GetLogger("DXGame::Init_Input()").Error("Can't Init DirectX Input"));
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Init DirectX Input");
	}

	result = m_lpDirectInput->CreateDevice(GUID_SysKeyboard, &m_lpKeyBoardDevice, NULL);

	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Init DirectX Input Keyboard Device");
	}

	result = m_lpDirectInput->CreateDevice(GUID_SysMouse, &m_lpMouseDevice, NULL);

	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Init DirectX Input Mouse Device");
	}
}

void CInputDx9::InitializeKeyBoardDevice(HWND handleWindow)
{
	HRESULT result;
	result = m_lpKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Set Data Format Keyboard");
	}

	result = m_lpKeyBoardDevice->SetCooperativeLevel(handleWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Set Cooperative Level of Keyboard");
	}

	result = m_lpKeyBoardDevice->Acquire();
	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Acquire Keyboard");
	}
}

void CInputDx9::InitializeMouseDevice(HWND handleWindow)
{
	HRESULT result;

	ZeroMemory(&m_mouseState, sizeof(m_mouseState));

	result=m_lpMouseDevice->SetDataFormat(&c_dfDIMouse);

	if(result != DI_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't set Data format of Mouse");
	}

	result=m_lpMouseDevice->SetCooperativeLevel(handleWindow,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);

	if(result != DI_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't set Cooperative Level of Mouse");	
	}

	result = m_lpMouseDevice->Acquire();
	if (result != D3D_OK)
	{
		CGameLog::GetInstance("CInputDx9")->SaveError("Can't Acquire Keyboard");
	}
}

bool CInputDx9::IsMouseRightClick()
{
	return ((m_mouseState.rgbButtons[1] & 0x80)!=0);
}

bool CInputDx9::IsMouseLeftClick()
{
	return ((m_mouseState.rgbButtons[0] & 0x80)!=0);
}

void CInputDx9::UpdateKeyBoard()
{
	//m_lpKeyBoardDevice->Acquire(); // Acquire device
	m_lpKeyBoardDevice->GetDeviceState(sizeof(m_keyBoardBuffer), (LPVOID)&m_keyBoardBuffer);
}

bool CInputDx9::IsKeyDown(int keyCode)
{
	if (m_keyBoardBuffer[keyCode] & 0x80)
		return true;
	return false;
}

void CInputDx9::UpdateMouse()
{
	HRESULT result = m_lpMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);

	if(FAILED(result))
	{
		ZeroMemory(&m_mouseState, sizeof(m_mouseState));
		m_lpMouseDevice->Acquire();
	}
}

D3DXVECTOR2 CInputDx9::GetCursorLocation()
{
	return D3DXVECTOR2(m_mouseState.lX, m_mouseState.lY);
}

CInputDx9::~CInputDx9()
{

}