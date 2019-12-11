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
#include "ShapeDrawingDemo.hpp"
#include "TextureDrawingDemo.hpp"
#include "SolarSystemDemo.hpp"
#include "AnimationDemo.hpp"

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
	demo[TEXTUREDRAWING] = std::make_unique<TextureDrawingDemo>(window);
	demo[SOLARSYSTEM] = std::make_unique<SolarSystemDemo>(window);
	demo[ANIMATION] = std::make_unique<AnimationDemo>(window);
}

void Application::Update(float dt)
{
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	
	demo[demoIndex]->Update(dt);

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
		demo[demoIndex]->ResetCamera();
		++demoIndex;
		if (demoIndex >= static_cast<int>(demo.size()))
		{
			demoIndex = 0;
		}
		break;
	case KeyboardButton::Arrow_Left:
		demo[demoIndex]->ResetCamera();
		if (demoIndex == 0)
		{
			demoIndex = static_cast<int>(demo.size()) - 1;
			break;
		}
		--demoIndex;
		break;
	default:
		break;
	}
}

void Application::HandleKeyRelease(KeyboardButton button)
{
	demo[demoIndex]->HandleKeyRelease(button);
}

void Application::HandleScrollEvent(float scroll_amount)
{
	const float zoomSpeed = .05f;
	float newZoom = view.GetZoom() + (scroll_amount * zoomSpeed);
	newZoom = std::clamp(newZoom, 0.5f, 2.0f);
	view.SetZoom(newZoom);
	demo[demoIndex]->HandleScrollEvent(scroll_amount);
}
void Application::HandleMousePositionEvent(float xpos, float ypos)
{
	demo[demoIndex]->HandleMousePositionEvent(xpos, ypos);
}

void Application::HandleMouseEvent(MouseButton button)
{
	demo[demoIndex]->HandleMouseEvent(button);
}

void Application::HandleResizeEvent(const int& new_width, const int& new_height)
{
	window.SetWindowWidth(new_width);
	window.SetWindowHeight(new_height);

	demo[demoIndex]->HandleResizeEvent(new_width, new_height);
}

void Application::HandleWindowClose()
{
	ShutDown();
}

void Application::HandleFocusEvent(int focus)
{
	demo[demoIndex]->HandleFocusEvent(focus);
	if (focus != GLFW_TRUE)
	{
		std::cout << "NOT FOCUSED\n";
	}
}