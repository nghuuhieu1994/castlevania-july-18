#include "CSpriteDx9.h"

CSpriteDx9::CSpriteDx9()
{

}
CSpriteDx9::CSpriteDx9(D3DXVECTOR3* Position, LPCSTR fileName, D3DCOLOR color, int ColFrame, int RowFrame, int TotalFrame)
{
	this->m_MyTexture = new CTextureDx9(Position, fileName, color);
	this->m_ColFrame = ColFrame;
	this->m_RowFrame = RowFrame;
	this->m_TotalFrame = TotalFrame;
}
void CSpriteDx9::LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice)
{
	this->m_MyTexture->LoadTextureFromeFile(_lpDirectDevice);
	int Width		= this->m_MyTexture->getINFO().Width / this->m_ColFrame;
	int Heigth		= this->m_MyTexture->getINFO().Height / this->m_RowFrame;
	this->m_MyAnimation = new CAnimationDx9(Width, Heigth, m_TotalFrame, m_ColFrame, m_RowFrame);
}

CSpriteDx9::CSpriteDx9(const CSpriteDx9* otherSprite)
{
	this->m_MyTexture = new CTextureDx9(otherSprite->m_MyTexture);
	this->m_MyAnimation = new CAnimationDx9(otherSprite->m_MyAnimation);
}

void CSpriteDx9::UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation)
{
	this->m_MyAnimation->UpdateAnimation(gameTime, timeAnimation); 
}

void CSpriteDx9::Render(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSprite)
{
	this->m_MyTexture->setRECT(this->m_MyAnimation->getRect());
	this->m_MyTexture->RenderTexture(_lpDirectDevice, _lpDSprite);
}