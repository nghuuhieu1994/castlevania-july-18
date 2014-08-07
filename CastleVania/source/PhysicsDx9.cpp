#include "PhysicsDx9.h"
#include <stdio.h>

PhysicDx9::PhysicDx9() : m_size(NULL), m_location(NULL), m_velocityPerFrame(NULL)
{

}

void PhysicDx9::InitializeObjectData(D3DXVECTOR3 size, int locationX, int locationY)
{
	m_velocityPerFrame	= new D3DXVECTOR3(0.0f, 0.0f, 0.0f);// move 1 pixel / frame

	m_location			= new D3DXVECTOR3(locationX, locationY, 0.0f);

	m_size				= new D3DXVECTOR3(size.x, size.y, 0.0f);
}

void PhysicDx9::SetVelocityPerFrame(float velocityX, float velocityY)
{
	m_velocityPerFrame->x = velocityX;
	m_velocityPerFrame->y = velocityY;
}

void PhysicDx9::UpdateMovement(CGameTimeDx9* gameTime)
{
	float deltaTime = gameTime->getElapsedGameTime().getSeconds();
	
	deltaTime = deltaTime/((float)1/60);

	m_location->x += m_velocityPerFrame->x * deltaTime;
	m_location->y += m_velocityPerFrame->y * deltaTime;

	m_velocityPerFrame->x = 0;
	m_velocityPerFrame->y = 0;
}

D3DXVECTOR3* PhysicDx9::GetLocation()
{
	return m_location;
}

PhysicDx9::~PhysicDx9()
{

}