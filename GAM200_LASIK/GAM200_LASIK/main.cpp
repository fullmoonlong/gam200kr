/**************************************************************************************
 *	File Name        : main.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jeonghak Kim
 *	Secondary Author : Doyeong Yi
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Engine.h"

//#include <Windows.h>
//int WINAPI wWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PWSTR /*pCmdLine*/, int /*nCmdShow*/)
int main()
{
	Engine* ENGINE = new Engine();
	ENGINE->Run();

	return 0;
}
