#include "BaseObject.h"

BaseObject::BaseObject()
{

}

void BaseObject::InitializeData(CSpriteDx9* sprite)
{
	m_sprite = new CSpriteDx9(sprite);
	m_physics = new PhysicDx9();
	m_physics->InitializeObjectData(sprite->GetFrameSize(), 0, 50);
}

void BaseObject::UpdateAnimation(CGameTimeDx9* gameTime)
{
	m_sprite->UpdateAnimation(gameTime, 100);
}

void BaseObject::UpdateMovement(CGameTimeDx9* gameTime)
{
	m_physics->UpdateMovement(gameTime);
}

void BaseObject::Render(LPD3DXSPRITE spriteBatch, D3DXMATRIX* viewPortMatrix)
{
	char buff[100];

	sprintf(buff, "X: %f Y: %f \n", m_physics->GetLocation()->x, m_physics->GetLocation()->y);
	
	OutputDebugString(buff);
	m_sprite->Render(spriteBatch, m_physics->GetLocation());
}

BaseObject::~BaseObject()
{

}