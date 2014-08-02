#ifndef __CSPRITE_H__
#define __CSPRITE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "CTextureDx9.h"
#include "CAnimationDx9.h"

//class CAnimationDx9;

class CSpriteDx9
{
private:
	// Hold the Texture to render
	CTextureDx9*		m_MyTexture;
	// Hold the animation action
	CAnimationDx9*		m_MyAnimation;
	// Num colum in a row of this sheet image
	int					m_ColFrame;
	// Num row in a colum of this sheet image
	int					m_RowFrame;
	// Total frame in this sheet Image
	int					m_TotalFrame;

public:
	CSpriteDx9();
	CSpriteDx9(D3DXVECTOR3* Position, LPCSTR fileName, D3DCOLOR  color, int ColFrame, int RowFrame, int TotalFrame);
	CSpriteDx9(const CSpriteDx9* otherSprite);
	void UpdateAnimation(CGameTimeDx9* gameTime, int timeAnimation);
	void LoadContent(LPDIRECT3DDEVICE9 _lpDirectDevice);
	//void Render(LPDIRECT3DDEVICE9 _lpDirectDevice, LPD3DXSPRITE _lpDSprite);

	//---------------------------------------------------
	/// This function contains blablabla...
	//---------------------------------------------------
	void Render(LPD3DXSPRITE _SpriteBatch, D3DXVECTOR3* _Location);
};


#endif