#if !defined __SIMON_H__
#define __SIMON_H__
#include "BaseObject.h"
#include "CInputDx9.h"

class Simon : public BaseObject
{
protected:
public:
	Simon();
	void GetInput(CInputDx9* input);
	CSpriteDx9* GetSprite();
	PhysicDx9*	GetPhysics();
	~Simon();
};

#endif