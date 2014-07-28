#include "CGame.h"
#include "GameLog.h"

CGame::CGame()
{
	this->m_d3d = 0;
	this->m_d3ddv = 0;
	this->m_FrameRate = FRAME_RATE;
	this->m_hInstance = 0;
	this->m_hWnd = 0;
	this->m_scrHeight = HEIGHT;
	this->m_scrWidth = WIDTH;
	this->m_WindowMode = true;
}
CGame::CGame(HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode, int frameRate)
{
	this->m_hInstance = hInstance;
	this->m_scrWidth = scrWidth;
	this->m_scrHeight = scrHeight;
	this->m_WindowMode = WndMode;
	this->m_FrameRate = frameRate;
}
CGame::~CGame()
{
	if(this->m_d3d)
		this->m_d3d->Release();
	m_d3d = NULL;
	if(this->m_d3ddv)
		this->m_d3ddv->Release();
	m_d3ddv = NULL;
	if(this->m_hInstance)
		this->m_hInstance = NULL;
	if(this->m_hWnd)
		this->m_hWnd = NULL;
}

bool CGame::InitWindow()
{
	WNDCLASSEX WndcEx;
	ZeroMemory(&WndcEx, sizeof(WndcEx));
	WndcEx.cbClsExtra = 0;
	WndcEx.cbSize = sizeof(WNDCLASSEX);
	WndcEx.cbWndExtra = 0;
	WndcEx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	WndcEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndcEx.hIcon = NULL;
	WndcEx.hIconSm = NULL;
	WndcEx.hInstance = this->m_hInstance;
	WndcEx.lpfnWndProc = (WNDPROC)WndProceduce;
	WndcEx.lpszClassName = "CGame";
	WndcEx.lpszMenuName = NULL;
	WndcEx.style = NULL;

	if(!RegisterClassEx(&WndcEx))
	{
		//MessageBox(0,"Can't Regis the WndcEx!!!", "Error", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't Regis the WndcEx!!!");
		return false;
	}
	m_hWnd = CreateWindow(
		"CGame",
		GAMETITLE,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		WIDTH,
		HEIGHT,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if(!m_hWnd)
	{
		//MessageBox(0,"Can't CraeteWindow!", "Error", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't Create Window!");
		return false;
	}
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	return true;
}

bool CGame::InitDirect3D()
{
	this->m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!this->m_d3d)
	{
		//MessageBox(0, "Can't Create Direct3D Object!", "Error", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't Create Direct3D Object!");
		return false;
	}


	D3DPRESENT_PARAMETERS d3dpp;
	// dieu khien qua trinh hien thi cua so. Co net tuong don`g voi Wndc
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = this->m_scrHeight;
	d3dpp.BackBufferWidth = this->m_scrWidth;
	d3dpp.Windowed = this->m_WindowMode;
	d3dpp.hDeviceWindow = this->m_hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if(!this->m_WindowMode)
	{
		D3DDISPLAYMODE DisPlayMode;
		ZeroMemory(&DisPlayMode, sizeof(DisPlayMode));

		m_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisPlayMode);
		HRESULT hr;
		hr = m_d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DisPlayMode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, D3DFMT_A8R8G8B8);
		if(FAILED(hr))
		{
			//MessageBox(0, "Device format is unaccepatble for full screen mode", "Sorry", MB_OK);
			CGameLog::GetInstance("CGame")->SaveError("Device format is unacceptable for full screen mode");
			return false;
		}

		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.Windowed = false;
		d3dpp.BackBufferWidth = DisPlayMode.Width;
		d3dpp.BackBufferHeight = DisPlayMode.Height;
		d3dpp.hDeviceWindow = this->m_hWnd;			
	}

	if(FAILED(this->m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_d3ddv)))
	{
		if(FAILED(this->m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			m_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_d3ddv)))
		{
				if(FAILED(this->m_d3d->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				m_hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_d3ddv)))
				{
					//MessageBox(0,"Can't create Direct Divice!!!", "Error", MB_OK);
					CGameLog::GetInstance("CGame")->SaveError("Can't create Direct Device!!!");
					return false;
				}
		}
	}
												
	return true;
}

void CGame::Init()
{
	this->InitWindow();
	this->InitDirect3D();

	surFace = new CSurfaceDx9("Rectangle.png");
	surFace->LoadSurface(m_d3ddv);
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
			m_d3ddv->Clear(0,0,D3DCLEAR_TARGET,0x0af0f0c3, 1.0f, 0);
			if(m_d3ddv->BeginScene())
			{
				surFace->RenderSurface(m_d3ddv);
				m_d3ddv->EndScene();
			}
			// All of Process
			m_d3ddv->Present(0, 0, 0, 0);
		}
	}
}

void CGame::Exit()
{
	if(m_d3d)
	{
		m_d3d->Release();
		m_d3d = NULL;
	}
	if(m_d3ddv)
	{
		m_d3ddv->Release();
		m_d3ddv = NULL;
	}
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