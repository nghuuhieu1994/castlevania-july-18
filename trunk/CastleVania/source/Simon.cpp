#include "Simon.h"

Simon::Simon()
{

}

void Simon::GetInput(CInputDx9* input)
{
	if(input->IsKeyDown(DIK_RIGHT))
	{
		m_physics->SetVelocityPerFrame(2.0f, 0.0f);
		m_sprite->SetFlipY(-1.0f);
	}
	if(input->IsKeyDown(DIK_LEFT))
	{
		m_physics->SetVelocityPerFrame(-2.0f, 0.0f);
		m_sprite->SetFlipY(1.0f);
	}
	if(input->IsKeyDown(DIK_UP))
	{
		m_physics->SetVelocityPerFrame(0.0f, 1.0f);
		m_sprite->SetFlipY(1.0f);
	}
	if(input->IsKeyDown(DIK_DOWN))
	{
		m_physics->SetVelocityPerFrame(0.0f,-1.0f);
		m_sprite->SetFlipY(1.0f);
	}
}

CSpriteDx9* Simon::GetSprite()
{
	return m_sprite;
}

PhysicDx9*	Simon::GetPhysics()
{
	return m_physics;
}

Simon::~Simon()
{

}