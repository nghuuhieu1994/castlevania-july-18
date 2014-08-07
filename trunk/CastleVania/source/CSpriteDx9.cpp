#include "CSpriteDx9.h"
#include "GameLog.h"
#include "Camera.h"

CSpriteDx9::CSpriteDx9()
{

}

CSpriteDx9::CSpriteDx9(D3DXVECTOR3* Position, LPCSTR fileName, D3DCOLOR color, int ColFrame, int RowFrame, int TotalFrame)
{

}

void CSpriteDx9::LoadTexture(LPDIRECT3DDEVICE9 _lpDirectDevice, LPCSTR fileName)
{
	
	this->m_animation = new CAnimationDx9();
	
	HRESULT hr;
	hr = D3DXGetImageInfoFromFile(fileName, &m_Info);
	if (FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't get Image info frome file");
		return;
	}

	hr = D3DXCreateTextureFromFileEx(
		_lpDirectDevice,
		fileName,
		m_Info.Width,
		m_Info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),//use color ( 255, 255, 0, 255) to transparent texture
		&m_Info,
		NULL,
		&this->m_lpDTexture);

	if (FAILED(hr))
	{
		CGameLog::GetInstance("CTextureDx9")->SaveError("Can't Create Texture from file");
		return;
	}

}

CSpriteDx9::CSpriteDx9(const CSpriteDx9* otherSprite)
{
	//this->m_Texture = new CTextureDx9(otherSprite->m_Texture);
	m_lpDTexture			= otherSprite->m_lpDTexture;
	m_totalFrameOfSprite	= otherSprite->m_totalFrameOfSprite;
	m_listSourceRectangle	= otherSprite->m_listSourceRectangle;
	m_alphaOffsetPerFrame	= otherSprite->m_alphaOffsetPerFrame;
	m_alphaRender			= otherSprite->m_alphaRender;
	m_spriteEffect			= otherSprite->m_spriteEffect;
	m_animation				= new CAnimationDx9(otherSprite->m_animation);
	m_FlipY					= otherSprite->m_FlipY;
}

void CSpriteDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	this->m_animation->UpdateAnimation(gameTime, timeAnimation); 
}

void CSpriteDx9::InitializeSpriteData(int frameWidth, int frameHeight, int sheetColumn, int sheetRow, int totalFrameOfSprite)
{
	this->m_totalFrameOfSprite = totalFrameOfSprite;


	for (int i = 0; i < totalFrameOfSprite; i++)
	{
		RECT tempRect;
		tempRect.top = (i / sheetColumn) * frameHeight;
		tempRect.left = (i % sheetColumn) * frameWidth;
		tempRect.bottom = frameHeight + tempRect.top;
		tempRect.right = frameWidth + tempRect.left;
		m_listSourceRectangle.push_back(tempRect);
	}

	m_spriteEffect = SpriteEffect::None;
	m_FlipY = 1.0f;
}

CAnimationDx9* CSpriteDx9::getAnimation()
{
	return this->m_animation;
}

void CSpriteDx9::Render(LPD3DXSPRITE _SpriteBatch, D3DXVECTOR3* _Location)
{
	/*D3DXMATRIX matrixTransform;

	D3DXMatrixIdentity(&matrixTransform);
	m_spriteEffect(&matrixTransform, &m_listSourceRectangle.at(0));

	_SpriteBatch->SetTransform(&matrixTransform);
	/*
	D3DXVECTOR3 center;
	center.x = GetFrameSize().x / 2;
	center.y = GetFrameSize().y / 2;
	center.z = GetFrameSize().z;*/
	D3DXMATRIX matrixTransform;

	D3DXMatrixIdentity(&matrixTransform);
	//m_spriteEffect(&matrixTransform, &m_listSourceRectangle.at(0));

	D3DXMatrixScaling(&matrixTransform, m_FlipY, 1.0f, 1.0f);

	_SpriteBatch->SetTransform(&matrixTransform);

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	matrix._22 = -1.0f;

	matrix._41 = Camera::GetInstance()->GetMatrixTranslate()._41;
	matrix._42 = Camera::GetInstance()->GetMatrixTranslate()._42;

	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, _Location, &matrix);

	float halfWidth = GetFrameSize().x / 2;
	float halfHeight = GetFrameSize().y / 2;
	D3DXVECTOR3 p(vp_pos.x + halfWidth, vp_pos.y - halfHeight, 0);
	D3DXVECTOR3 center(halfWidth, halfHeight, 0);
	if (m_FlipY < 0)
	{
		p.x = -p.x;
	}
	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(255, 255, 255, 255);
	_SpriteBatch->Draw(
		this->m_lpDTexture,
		&m_listSourceRectangle.at(m_animation->GetCurrentFrameIndex()),
		&center,
		&p,
		AlphaValue); 
}

void CSpriteDx9::SetSpriteEffect(void (*spriteEffect)(D3DXMATRIX*, RECT*))
{
	m_spriteEffect = spriteEffect;
}

D3DXVECTOR3	CSpriteDx9::GetFrameSize()
{
	return D3DXVECTOR3(m_listSourceRectangle[0].right, m_listSourceRectangle[0].bottom, 0.0f);
}

void CSpriteDx9::Render(LPD3DXSPRITE spriteBatch, D3DXVECTOR3* location, void(*spriteEffect)(D3DXMATRIX*, RECT*))
{
	D3DXMATRIX matrixTransform;

	D3DXMatrixIdentity(&matrixTransform);
	spriteEffect(&matrixTransform, &m_listSourceRectangle.at(0));

	spriteBatch->SetTransform(&matrixTransform);
	
	DWORD AlphaValue;
	AlphaValue = D3DCOLOR_ARGB(255, 255, 255, 255);
	spriteBatch->Draw(
		this->m_lpDTexture,
		&m_listSourceRectangle.at(m_animation->GetCurrentFrameIndex()),
		NULL,
		location,
		AlphaValue);
}