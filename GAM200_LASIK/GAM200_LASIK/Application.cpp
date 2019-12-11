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

Application::Application()
{
	isRunning = true;
}

void Application::Initialize()
{
	window.CanCreateWindow(1280, 720, this, "Lasik");
	selectMenu.SelectMenu();
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		tower->animation.Initialize({ 1, 1, 10.0f }, shader);
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		lair->animation.Initialize({ 1, 1, 10.0f }, shader);
		proKevin->animation.Initialize({ 8, 1, 10.0f }, shader);
		knight->animation.Initialize({ 8, 1, 10.0f }, shader);
		archer->animation.Initialize({ 8, 1, 10.0f }, shader);
		magician->animation.Initialize({ 8, 1, 10.0f }, shader);
		fireball->animation.Initialize({ 3, 1, 5.0f }, shader);
		arrow.animation.Initialize({1, 1, 5.0f}, shader);
}

void Application::Update()
{
	clock.UpdateClock();

	selectMenu.SelectUpdate(camera, view);
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
	window.CleanUpWindow();
}

void Application::HandleKeyPress(KeyboardButton button)
{
	//bool isEnter = false;
	//if (isEnter != false)
	{
		switch (button)
		{
		case KeyboardButton::F:
			window.ToggleFullScreen();
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
