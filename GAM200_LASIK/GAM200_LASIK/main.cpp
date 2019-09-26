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

/*
 *	Separate solution or share folder
 *	Same graphics engine but different game with GAM200 in CS200
 */

#include <Windows.h>
#include <glfw3.h>
#include "Engine.h"

int WINAPI wWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PWSTR /*pCmdLine*/, int /*nCmdShow*/)
{
	Engine* ENGINE = new Engine();
	ENGINE->Run();

	return 0;
}

//int main()
//{
//		Engine* ENGINE = new Engine();
//		ENGINE->Run();
//
//		return 0;
//}