#ifndef __CGAME_H__
#define __CGAME_H__

#include <d3d9.h>
#include <iostream>
#include "CGlobal.h"
#include "CSurfaceDx9.h"
#include "CTextureDx9.h"
#include "CSpriteDx9.h"
#include "CGameTimeDx9.h"
using namespace std;

class CGame
{
private:
	static LRESULT CALLBACK WndProceduce(HWND hWnd, UINT  message, WPARAM wParam, LPARAM lParam);
protected:
	HWND			m_hWnd; // the handle of an window
	HINSTANCE		m_hInstance; //  

	LPDIRECT3D9			m_d3d;
	LPDIRECT3DDEVICE9	m_d3ddv;
	LPD3DXSPRITE		m_SpriteHandler;

	CGameTimeDx9*		m_GameTime;

	int				m_scrWidth;
	int				m_scrHeight;
	int				m_FrameRate;
	bool			m_WindowMode;

	bool			InitWindow();
	bool			InitDirect3D();

	/*CSurfaceDx9*	surFace;
	CSurfaceDx9*	surFace2;
	CTextureDx9*	texture;*/
	CSpriteDx9*		sprite;


public:
	CGame();
	CGame(HINSTANCE hInstance, int scrWidth, int scrHeight, bool WndMode, int frameRate);
	void Init();
	void Run();
	void Exit();
	~CGame();
};
#endif