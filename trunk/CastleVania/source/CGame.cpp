#include "CGame.h"
#include "GameLog.h"
#include <d3dtypes.h>

CGame::CGame() : 
	m_handleWindow(NULL), 
	m_lpDirect3D(NULL), 
	m_lpDirect3DDevice(NULL), 
	m_lpSpriteDirect3DHandle(NULL)
{
	
}

CGame::CGame(HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode, int frameRate)
{

}

CGame::~CGame()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)
	SAFE_DELETE(m_handleWindow)
}

bool CGame::InitializeHandleWindow(HINSTANCE hInstance)
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbClsExtra		= 0;
	WndcEx.cbSize			= sizeof(WNDCLASSEX);
	WndcEx.cbWndExtra		= 0;
	WndcEx.hbrBackground	= (HBRUSH)COLOR_BACKGROUND;
	WndcEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	WndcEx.hIcon			= NULL;
	WndcEx.hIconSm			= NULL;
	WndcEx.hInstance		= hInstance;
	WndcEx.lpfnWndProc		= (WNDPROC)WndProceduce;
	WndcEx.lpszClassName	= "CGame";
	WndcEx.lpszMenuName		= NULL;
	WndcEx.style			= NULL;

	if(!RegisterClassEx(&WndcEx))
	{
		CGameLog::GetInstance("CGame")->SaveError("Can't Regist the WndcEx!!!");
		return false;
	}

	m_handleWindow = CreateWindow(
		"CGame",
		GAMETITLE,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(!m_handleWindow)
	{
		CGameLog::GetInstance("CGame")->SaveError("Can't Create Window!");
		return false;
	}

	ShowWindow(m_handleWindow, SW_SHOW);
	UpdateWindow(m_handleWindow);

	return true;
}

bool CGame::InitializeDirect3DEnvironment()
{
	this->m_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!this->m_lpDirect3D)
	{
		CGameLog::GetInstance("CGame")->SaveError("Can't Create Direct3D Object!");
		return false;
	}

	return true;
}

bool CGame::InitializeDirect3DDevice(bool isWindowed)
{
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (isWindowed)//if Play in Window Mode
	{
		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.BackBufferHeight	= 600;
		d3dpp.BackBufferWidth	= 800;
		d3dpp.Windowed			= true;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD; 
	}
	else//if Play in Full ScreenMode
	{
		D3DDISPLAYMODE DisPlayMode;
		ZeroMemory(&DisPlayMode, sizeof(DisPlayMode));

		m_lpDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisPlayMode);

		HRESULT handleResult;
		handleResult = m_lpDirect3D->CheckDeviceFormat(
			D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL, 
			DisPlayMode.Format, 
			D3DUSAGE_RENDERTARGET, 
			D3DRTYPE_SURFACE, 
			D3DFMT_A8R8G8B8);

		if(FAILED(handleResult))
		{
			CGameLog::GetInstance("CGame")->SaveError("Device format is unacceptable for full screen mode");
			return false;
		}

		d3dpp.BackBufferCount	= 1;
		d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
		d3dpp.Windowed			= false;
		d3dpp.BackBufferWidth	= DisPlayMode.Width;
		d3dpp.BackBufferHeight	= DisPlayMode.Height;
		d3dpp.hDeviceWindow		= this->m_handleWindow;
		d3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD; 
	}

	m_lpDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_handleWindow,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_lpDirect3DDevice);

	if(FAILED(m_lpDirect3DDevice))
	{
		CGameLog::GetInstance("CGame")->SaveError("Can't create Direct3D Device");
		return false;
	}

	return true;
}

bool CGame::InitializDirect3DSpriteHandle()
{
	D3DXCreateSprite(m_lpDirect3DDevice, &m_lpSpriteDirect3DHandle);
	bool isSpriteCreated;
	isSpriteCreated = !FAILED(m_lpSpriteDirect3DHandle);

	if(!isSpriteCreated)
	{
		CGameLog::GetInstance("CGame")->SaveError("Can't create Direct3D Sprite Handle");
		return false;
	}
	return true;
}

bool CGame::Initialize(HINSTANCE hInstance, bool isWindowed)
{
	this->InitializeHandleWindow(hInstance);
	this->InitializeDirect3DEnvironment();
	this->InitializeDirect3DDevice(isWindowed);
	this->InitializDirect3DSpriteHandle();
	//m_GameTime = new CGameTimeDx9();

	sprite = new CSpriteDx9(new D3DXVECTOR3(0, 0, 0),"resources/background1.png",0xFFFFFFFF, 1, 1, 1);
	sprite->LoadContent(m_lpDirect3DDevice);
	return true;
}

void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//m_GameTime->UpdateGameTime();

			m_lpDirect3DDevice->Clear(0 , 0,D3DCLEAR_TARGET,D3DCOLOR_XRGB( 0, 0, 0), 1.0f, 0);
			if(m_lpDirect3DDevice->BeginScene())
			{

				m_lpSpriteDirect3DHandle->Begin(D3DXSPRITE_ALPHABLEND);

				//sprite->UpdateAnimation(m_GameTime, 100);
				
				//sprite->Render(m_LPDirect3DDevice, m_LPSpriteDirect3DHandle);
				sprite->Render(m_lpSpriteDirect3DHandle, &D3DXVECTOR3( 0, 0, 0));
				

				m_lpSpriteDirect3DHandle->End();

				m_lpDirect3DDevice->EndScene();
			}
			m_lpDirect3DDevice->Present( 0, 0, 0, 0);
		}
	}
}

void CGame::Exit()
{
	SAFE_RELEASE(m_lpDirect3D)
	SAFE_RELEASE(m_lpDirect3DDevice)
}

LRESULT CALLBACK CGame::WndProceduce(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message,wParam, lParam);
}