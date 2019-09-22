/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/07/04
*/

#include "Application.h"

Application::Application()
{
	gameState = GameState::PLAY;
}

Application::~Application()
{
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, "Prototype"); //initialize window
}

void Application::Update()
{
	while (gameState != GameState::EXIT) // while game running
	{
		glWindow.SwapBuffers();
		glWindow.PollEvents();
		if (glfwGetKey(glWindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			gameState = GameState::EXIT;
		}
		else if (glfwGetKey(glWindow.window, GLFW_KEY_V) == GLFW_PRESS)
		{
			glWindow.ToggleOnVSync(!glWindow.IsVSyncOn());
		}
		else if (glfwGetKey(glWindow.window, GLFW_KEY_F) == GLFW_PRESS)
		{
			glWindow.ToggleFullScreen(glWindow.window);
		}
	}
}

void Application::Shutdown() //not yet
{
}

void Application::Run()
{
	Initialize();
	Update(); //updating game statment when game is running
}
