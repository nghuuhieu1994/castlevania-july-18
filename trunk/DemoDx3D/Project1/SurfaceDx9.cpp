#include "CSurfaceDx9.h"
#include "GameLog.h"

CSurfaceDx9::CSurfaceDx9()
{
	this->m_lpDSurface = NULL;
	this->m_lpDBackBuffer = NULL;
	this->m_fileName = NULL;
}
CSurfaceDx9::CSurfaceDx9(LPCSTR fileName)
{
	this->m_fileName = fileName;
	this->m_lpDSurface = NULL;
	this->m_lpDBackBuffer = NULL;
}
CSurfaceDx9::CSurfaceDx9(const CSurfaceDx9* surfaceDx9)
{
	this->m_fileName = *(new LPCSTR(surfaceDx9->m_fileName));
	this->m_Info = *(new D3DXIMAGE_INFO(surfaceDx9->m_Info));
	this->m_lpDSurface = *(new LPDIRECT3DSURFACE9(surfaceDx9->m_lpDSurface));
	//this->m_lpDirectDevice = surfaceDx9->m_lpDirectDevice;
	// i think all of Object wanna render in a Game must use only 1 Device9
}

bool CSurfaceDx9::CreateOffScreenSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice)
{
	HRESULT result;
	LPDIRECT3DSURFACE9 s;
	result = m_lpDirectDevice->CreateOffscreenPlainSurface(
		m_Info.Width,
		m_Info.Height,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&this->m_lpDSurface,
		NULL);

	if(result != D3D_OK)
	{
		//MessageBox(NULL,m_fileName,"Error!!! Can't Create Offscreen", MB_OK);
		CGameLog::GetInstance("SurfaceDx9")->SaveError("Can't Create Offscreen");
		return false;
	}
	return true;
}
bool CSurfaceDx9::LoadSurfaceFromFile()
{
	HRESULT result;
	result = D3DXLoadSurfaceFromFile(
		m_lpDSurface,
		NULL,
		NULL,
		m_fileName,
		NULL,
		D3DX_DEFAULT,
		0,
		NULL);

	if(FAILED(result))
	{
		//MessageBox(NULL, m_fileName,"Error!!! Can't Load Surface from File!!!", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't Load Surface from file");
		return false;
	}
	return true;
}

LPDIRECT3DSURFACE9 CSurfaceDx9::LoadSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice)
{
	HRESULT result;
	result = D3DXGetImageInfoFromFile(m_fileName, &m_Info);

	if(FAILED(result))
	{
		//MessageBox(NULL, m_fileName, "Can't get Image from file", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't get Image from file");
		return NULL;
	}

	this->CreateOffScreenSurface(m_lpDirectDevice);

	this->LoadSurfaceFromFile();
	
	result = m_lpDirectDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_lpDBackBuffer);
	if(FAILED(result))
	{
		//MessageBox(NULL, m_fileName, "Error!!! Can't get Surface to backBuffer", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't get Surface to BackBuffer");
		return NULL;
	}
	m_Rect.top = 100;
	m_Rect.left = 100;
	m_Rect.bottom = m_Rect.top + m_Info.Height;
	m_Rect.right = m_Rect.left + m_Info.Width;
	return (this->m_lpDSurface);
}
void CSurfaceDx9::RenderSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice)
{
	if(!m_lpDirectDevice)
	{
		//MessageBox(NULL, "Can't find Direct Device", "ERROR", MB_OK);
		CGameLog::GetInstance("CGame")->SaveError("Can't find Direct Device");
		return;
	}
	m_lpDirectDevice->StretchRect(
		m_lpDSurface, 
		NULL,
		m_lpDBackBuffer,
		&m_Rect,
		D3DTEXF_NONE);
}

CSurfaceDx9::~CSurfaceDx9()
{
	if(!m_lpDBackBuffer)
	{
		m_lpDBackBuffer->Release();
		m_lpDBackBuffer = NULL;
	}

	if(!m_lpDSurface)
	{
		m_lpDSurface->Release();
		m_lpDSurface = NULL;
	}
}