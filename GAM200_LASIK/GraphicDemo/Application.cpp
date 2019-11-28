/********************************************************
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Application.cpp
*	
*	Graphic demo main file
*	
*	Nov.29 2019
*******************************************************/

#include <iostream>
#include "Application.h"

bool Application::IsRunning() const
{
	return isRunning;
}

Application::Application()
{
	Initialize();
}

void Application::Initialize()
{
	if (!window.CanCreateWindow(width, height, this, "Graphic Demo"))
	{
		return;
	}
	isRunning = true;

	shapeDrawingDemo.Initialize();
}

void Application::Update()
{
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());

	switch (demoIndex)
	{
	case DEMOINDEX::SHAPEDRAWING:
		shapeDrawingDemo.Update();
		break;
	}

	window.SwapBuffers();
	window.PollEvents();
}

void Application::ShutDown()
{
	isRunning = false;
}

void Application::HandleKeyPress(KeyboardButtons button)
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
