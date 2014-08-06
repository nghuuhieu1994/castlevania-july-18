#if !defined __PHYSICS_DX_9__
#define __PHYSICS_DX_9__
#include <d3d9.h>
#include <d3dx9.h>
#include "CGameTimeDx9.h"

class PhysicDx9
{
	D3DXVECTOR3*		m_velocityPerFrame;
	D3DXVECTOR3*		m_location;
	D3DXVECTOR3*		m_size;
public:
	PhysicDx9();
	//--------------------------------------
	///	@desciption: Using this function to initialize width, height..
	///	@param width: width of object
	///	@param height: height of object
	//--------------------------------------
	void InitializeObjectData(D3DXVECTOR3 size, int locationX, int locationY);
	void UpdateMovement(CGameTimeDx9* gameTime);
	D3DXVECTOR3* GetLocation();
	~PhysicDx9();
};

#endif