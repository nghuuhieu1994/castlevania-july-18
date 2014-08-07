#if !defined __CAMERA_H__
#define __CAMERA_H__

#include <d3dx9.h>
#include <d3d9.h>
#include "GameLog.h"

class Camera
{
	static Camera*		s_Instance;
	Camera();
	D3DXMATRIX			m_matrixTranslate;
public:
	static Camera*		GetInstance();
	void			UpdateCamera(D3DXVECTOR3* simonLocation);
	D3DXMATRIX			GetMatrixTranslate();
	~Camera();
};

#endif