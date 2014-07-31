#ifndef __GAMETIME_H__
#define	__GAMETIME_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

enum eTypeTime
{
	Milliseconds,
	Seconds,
	Minutes
};

class CGameTimeDx9
{
private:
	UINT64		mTimeStart;

public:
};

#endif