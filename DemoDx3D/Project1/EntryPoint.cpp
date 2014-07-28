#include "CGame.h"
#include <d3d9.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpStrCmdLine, int nShowCmd)
{
	CGame* Run = new CGame(hInstance, WIDTH, HEIGHT, CGlobal::IsWindowMode, FRAME_RATE);
	Run->Init();
	Run->Run();
	Run->Exit();
	return 0;
}