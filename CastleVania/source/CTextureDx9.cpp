#include "CTextureDx9.h"
#include "GameLog.h"
LPDIRECT3DTEXTURE9 CTextureDx9::LoadTextureFromeFile(LPDIRECT3DDEVICE9	_lpDirectDevice)
{
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(m_fileName, &m_Info);
	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get Image info frome file");
		return NULL;
	}

	hr = D3DXCreateTextureFromFileEx(
		_lpDirectDevice,
		m_fileName,
		m_Info.Width,
		m_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,0,255),//use color ( 255, 255, 0, 255) to transparent texture
		&m_Info,
		NULL,
		&this->m_lpDTexture);

	if(FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't Create Texture from file");
		return NULL;
	}

	this->m_SourceRect = 
		new RectangleDx9(
						0, 
						0, 
						m_Info.Height,
						m_Info.Width);

	return this->m_lpDTexture;
}

CTextureDx9::CTextureDx9() : m_lpDTexture(NULL), m_SourceRect(NULL)
{
	//this->m_lpDTexture = NULL;
	
}
CTextureDx9::CTextureDx9(D3DXVECTOR3* position, LPCSTR fileName, D3DCOLOR color)
{
	this->m_Position = new D3DXVECTOR3(*position);
	this->m_fileName = fileName;
	this->m_lpDTexture = NULL;
	this->m_Center = NULL;
	this->m_Color = color;
	//m_Center = new D3DXVECTOR3(0, 0, 0);
}
CTextureDx9::CTextureDx9(const CTextureDx9* textureDx9)
{
	m_lpDTexture = *(new LPDIRECT3DTEXTURE9(textureDx9->m_lpDTexture));
	this->m_fileName = NULL;
}

D3DXIMAGE_INFO CTextureDx9::getINFO()
{
	return this->m_Info;
}

void CTextureDx9::setRECT(RECT* otherRECT)
{
	
	
}

//void CTextureDx9::RenderTexture(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSprite)
//{
//	if(_lpDirectDevice == NULL)
//	{
//		CGameLog::GetInstance("CTextureDx9Render")->SaveError("Can't find lpDirectDevice to render");
//		return;
//	}
//	if(_lpDSprite == NULL)
//	{
//		CGameLog::GetInstance("CTextureDx9Render")->SaveError("Can't find lpDSprire to render");
//		return;
//	}
//
//	_lpDSprite->Draw(this->m_lpDTexture,
//		&this->m_SourceRect->getRECT(),
//		this->m_Center,
//		this->m_Position,
//		m_Color);
//}

void CTextureDx9::RenderTexture(LPD3DXSPRITE SpriteBatch, RECT* SourceRectangle, D3DXVECTOR3* Location)
{
	if(SpriteBatch == NULL)
	{
		CGameLog::GetInstance("CTextureDx9Render")->SaveError("Can't find lpDSprire to render");
		return;
	}
	m_Center = new D3DXVECTOR3(0, 0, 0);
	SpriteBatch->Draw(
		this->m_lpDTexture, 
		SourceRectangle,
		m_Center,
		Location,
		0xFFFFFFFF);
	delete m_Center;
}