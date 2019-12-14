/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Jookyung Lee jookyung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "Application.h"
#include "PATH.hpp"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "ComponentTest.h"
#include "ComponentTower.h"
#include "GetInput.hpp"
#include "Screenshot.hpp"
#include "StateManager.h"
#include "Engine.h"

Application::Application()
{
	isRunning = true;
}

void Application::Initialize()
{
	window.CanCreateWindow(1280, 720, this, "Lasik");
}

void Application::Update(float /*dt*/)
{
	clock.UpdateClock();

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	window.SwapBuffers();
	window.PollEvents();
	deltaTime = clock.GetTimeFromLastUpdate();
}

void Application::ShutDown()
{
	isRunning = false;
	gameEngine->Shutdown();
}

void Application::HandleKeyPress(KeyboardButton button)
{
	//bool isEnter = false;
	//if (isEnter != false)
	{
		switch (button)
		{
		case KeyboardButton::F:
			//window.ToggleFullScreen();
			//STATEMANAGER->GetCurrentLevel()->HandleResizeEvent(window.GetWindowWidth(), window.GetWindowHeight());
			break;
		case KeyboardButton::V:
			if (window.IsVSyncOn() == false)
			{
				window.ToggleVSync(true);
				break;
			}
			window.ToggleVSync(false);
			break;
		case KeyboardButton::Escape:
			this->ShutDown();
			break;/*
		case KeyboardButton::Enter:
			if (isEnter == false)
			{
				isEnter = true;
				break;
			}
			isEnter = false;
			break;*/
		default:
			break;
		}
	}
	STATEMANAGER->GetCurrentLevel()->HandleKeyPress(button);
}

void Application::HandleKeyRelease(KeyboardButton button)
{
	STATEMANAGER->GetCurrentLevel()->HandleKeyRelease(button);
}

void Application::HandleMouseEvent(MouseButton button)
{
	STATEMANAGER->GetCurrentLevel()->HandleMouseEvent(button);
}

void Application::HandleResizeEvent(const int& new_width, const int& new_height)
{
	window.SetWindowWidth(new_width);
	window.SetWindowHeight(new_height);

	STATEMANAGER->GetCurrentLevel()->HandleResizeEvent(new_width, new_height);
}

void Application::HandleScrollEvent(float scroll_amount)
{
	STATEMANAGER->GetCurrentLevel()->HandleScrollEvent(scroll_amount);
}

void Application::HandleMousePositionEvent(float xpos, float ypos)
{
	STATEMANAGER->GetCurrentLevel()->HandleMousePositionEvent(xpos, ypos);
}

void Application::HandleWindowClose()
{
	ShutDown();
}
