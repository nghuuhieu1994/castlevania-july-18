#include "CTextureDx9.h"
#include "GameLog.h"
bool CTextureDx9::CreateTextureFromeFile(LPDIRECT3DDEVICE9		m_lpDirectDevice)
{
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(m_fileName, &m_Info);
	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get Image info frome file");
		return false;
	}
	hr = D3DXCreateTextureFromFileEx(
		m_lpDirectDevice,
		m_fileName,
		m_Info.Width,
		m_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0,0,0),
		&m_Info,
		NULL,
		&this->m_lpDTexture);
	// now i have to comeback to my dorm. Then i'll fuck all the framework
	return true;
}