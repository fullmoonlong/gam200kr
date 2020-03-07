/**************************************************************************************
 *	File Name        : Application.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jookyung Lee
 *	Secondary Author : Wonju Cho
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "Application.h"
#include "PATH.hpp"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "ComponentAttack.h"
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
	window.CanCreateWindow(1280, 720, this, "Keyboard Warriors");
}

void Application::Update(float /*dt*/)
{
	clock.UpdateClock();

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		windowTitleWithFrameCount = windowTitle + " (fps: " + std::to_string(frameCount) + ")";
		window.SetWindowTitle(windowTitleWithFrameCount.c_str());
		clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	window.SwapBuffers();
	window.PollEvents();
}

void Application::ShutDown()
{
	isRunning = false;
	gameEngine->gamestate = GameState::EXIT;
}

void Application::HandleKeyPress(KeyboardButton button)
{
	switch (button) {
	case KeyboardButton::F:
		break;
	case KeyboardButton::V:
		if (window.IsVSyncOn() == false) {
			window.ToggleVSync(true);
			break;
		}
		else
		window.ToggleVSync(false);
		break;
	case KeyboardButton::Escape:
		this->ShutDown();
		break;
	default:
		break;
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