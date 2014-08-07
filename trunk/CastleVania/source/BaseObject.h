#if !defined __BASE_OBJECT_H__
#define __BASE_OBJECT_H__

#include "CSpriteDx9.h"
#include "PhysicsDx9.h"

class BaseObject
{
protected:
	CSpriteDx9* m_sprite;
	PhysicDx9*	m_physics;
public:
	BaseObject();
	void InitializeData(CSpriteDx9* sprite);
	void UpdateAnimation(CGameTimeDx9* gameTime);
	void UpdateMovement(CGameTimeDx9* gameTime);
	void Render(LPD3DXSPRITE spriteBatch, D3DXMATRIX* viewPortMatrix);
	~BaseObject();
};

#endif