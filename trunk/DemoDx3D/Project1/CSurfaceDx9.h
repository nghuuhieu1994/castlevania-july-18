#ifndef __CSURFACE_H__
#define __CSURFACE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
class CSurfaceDx9;

class CSurfaceDx9
{
private:

	LPDIRECT3DSURFACE9		m_lpDSurface;
	LPDIRECT3DSURFACE9		m_lpDBackBuffer;
	
	LPCSTR					m_fileName;
	D3DXIMAGE_INFO			m_Info;

	RECT					m_Rect;

	bool	CreateOffScreenSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice);
	bool	LoadSurfaceFromFile();
public:
	CSurfaceDx9();
	CSurfaceDx9(LPCSTR  fileName);
	CSurfaceDx9(const  CSurfaceDx9* surfaceDx9);
	LPDIRECT3DSURFACE9 LoadSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice);
	void RenderSurface(LPDIRECT3DDEVICE9		m_lpDirectDevice);
	~CSurfaceDx9();
};

#endif