/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi		doyoung.lee@digipen.edu
*	
*	File_name: main.cpp
*	
*	main loop
*	
*	2019/07/04
*/

#include "Application.h"

int main()
{
	Application app;

	while (app.isRunning)
	{
		app.Update();
	}
	
	return 0;
}


//#include <Windows.h>
//
//int WINAPI wWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PWSTR /*pCmdLine*/, int /*nCmdShow*/)
//{
//	Engine* ENGINE = new Engine();
//	ENGINE->Run();
//
//	return 0;
//}