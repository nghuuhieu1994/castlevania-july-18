#include "Camera.h"

Camera* Camera::s_Instance = NULL;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_matrixTranslate);
	m_matrixTranslate._41 = 0;
	m_matrixTranslate._42 = 600;
}

Camera* Camera::GetInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new Camera();
	}
	return s_Instance;
}

void Camera::UpdateCamera(D3DXVECTOR3* simonLocation)
{
	if (simonLocation->x > 300)
	{
		m_matrixTranslate._41 = - (simonLocation->x - 300);
	}

}

D3DXMATRIX Camera::GetMatrixTranslate()
{
	return m_matrixTranslate;
}

Camera::~Camera()
{
	SAFE_DELETE(s_Instance);
}