/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Demo.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.28 2019
 *******************************************************/

#include <iostream>
#include "Demo.h"

bool Demo::IsRunning() const
{
	return isRunning;
}

Demo::Demo()
{
}

void Demo::Initialize()
{
	//isRunning = true;
	//
	//shapeDrawingDemo.Initialize();
}

void Demo::Update()
{

	//switch (demoIndex)
	//{
	//case DEMOINDEX::SHAPEDRAWING:
	//	shapeDrawingDemo.Update();
	//	break;
	//}
}

void Demo::ShutDown()
{
	isRunning = false;
}

void Demo::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Arrow_Left:
		// previous stage
		std::cout << "Previous Stage\n";
		break;
	case KeyboardButtons::Arrow_Right:
		// next stage
		std::cout << "Next Stage\n";
		break;
	}
}
