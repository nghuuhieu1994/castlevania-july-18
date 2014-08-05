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
	
}
CTextureDx9::CTextureDx9(D3DXVECTOR3* position, LPCSTR fileName, D3DCOLOR color)
{
	this->m_Position = new D3DXVECTOR3(*position);
	this->m_fileName = fileName;
	this->m_lpDTexture = NULL;
	this->m_Center = NULL;
	this->m_Color = color;
	m_Center = new D3DXVECTOR3(0, 0, 0);
	m_alphaRender = 255;
	m_alphaOffsetPerFrame = -5;
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
	D3DXMATRIX matRotate;
	
	D3DXMatrixIdentity(&matRotate);
	m_alphaRender += m_alphaOffsetPerFrame;
	if(m_alphaRender < 50 || m_alphaRender > 250)
	{
		m_alphaOffsetPerFrame *= -1;
	}
	/*D3DXVECTOR2 vCenter((int)getINFO().Width/2, (int)getINFO().Height/2);
	D3DXVECTOR2 vPosition( 0 ,0);
	D3DXMatrixTransformation2D(&matRotate, NULL, NULL, NULL, &vCenter, 3.1415f, &vPosition);*/
	//m_Center = new D3DXVECTOR3(getINFO().Width/2, getINFO().Height/2, 0);
	
	//matRotate._11 = -1;//cos(180)
	//matRotate._33 = -1;//cos(180)
	//matRotate._13 = 0;//-sin(180)
	//matRotate._31 = 0;//sin(180)

	//matRotate._41 = -200;
	//matRotate._42 = 100;

	//SpriteBatch->SetTransform(&matRotate);
	
	/*m_Center->x			= 0;
	m_Center->y			= 0;
	m_Center->z			= 0;*/
	//set transformation matrix
    
	//Location->x = Location->x - getINFO().Width;
	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(m_alphaRender,255,255,255);  	
	SpriteBatch->Draw(
		this->m_lpDTexture, 
		SourceRectangle,
		m_Center,
		Location,
		AlphaValue);

	//delete m_Center;
}