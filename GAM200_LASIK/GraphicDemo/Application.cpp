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

	demo[SHAPEDRAWING] = std::make_unique<ShapeDrawingDemo>(window);
}

void Application::Update()
{
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	
	switch (demoIndex)
	{
	case DEMOINDEX::SHAPEDRAWING:
		demo[demoIndex]->Update();
		break;
	}

	window.SwapBuffers();
	window.PollEvents();
}

void Application::ShutDown()
{
	isRunning = false;
}

void Application::HandleKeyPress(KeyboardButton button)
{
	demo[demoIndex]->HandleKeyPress(button);
	switch (button)
	{
	case KeyboardButton::Escape:
		this->ShutDown();
		break;
	case KeyboardButton::F:
		window.ToggleFullScreen();
		break;
	case KeyboardButton::V:
		window.ToggleVSync(!window.IsVSyncOn());
		break;
	case KeyboardButton::Arrow_Right:
		std::cout << "Next\n";
		camera.MoveRight(100);
		break;
	default:
		break;
	}
}

void Application::HandleResizeEvent(const int& new_width, const int& new_height)
{
	window.SetWindowWidth(new_width);
	window.SetWindowHeight(new_height);

	demo[demoIndex]->HandleResizeEvent(width, height);
}

void Application::HandleScrollEvent(float scroll_amount)
{
	const float zoomSpeed = .05f;
	float newZoom = view.GetZoom() + (scroll_amount * zoomSpeed);
	newZoom = std::clamp(newZoom, 0.5f, 2.0f);
	view.SetZoom(newZoom);
}

void Application::HandleWindowClose()
{
	ShutDown();
}
