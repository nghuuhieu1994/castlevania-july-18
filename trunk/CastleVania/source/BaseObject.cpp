#include "BaseObject.h"

BaseObject::BaseObject()
{

}

void BaseObject::InitializeData(CSpriteDx9* sprite)
{
	m_sprite = new CSpriteDx9(sprite);

	m_physics = new PhysicDx9();
	m_physics->InitializeObjectData(sprite->GetFrameSize(), 0, 0);
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
	m_sprite->Render(spriteBatch, m_physics->GetLocation(), SpriteEffect::None);
}

BaseObject::~BaseObject()
{

}