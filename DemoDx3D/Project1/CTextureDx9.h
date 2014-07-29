#ifndef __CTEXTURE_H__
#define	__CTEXTURE_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "VectorDx9.h"
class CTextureDx9
{
private:	
	// Lp to an instance of interface D3DTexture
	LPDIRECT3DTEXTURE9	m_lpDTexture;
	// Link to file Image
	LPCSTR				m_fileName;
	// include all info of the Image
	D3DXIMAGE_INFO		m_Info;
	// Position of this texture in game
	VectorDx9			m_Position;
	// Create texture from file
	bool CreateTextureFromeFile(LPDIRECT3DDEVICE9	m_lpDirectDevice);
public:
	// Cosntructor none parametor
	CTextureDx9(LPDIRECT3DDEVICE9	m_lpDirectDevice);
	// Constructor 2 parametor position and fileName
	CTextureDx9(VectorDx9* position, LPCSTR fileName);
	CTextureDx9(const CTextureDx9* textureDx9);
	~CTextureDx9();
};

#endif