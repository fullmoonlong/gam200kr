/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/07/04
*/
#include "Object.h"
#include "Engine.h"
#include "Application.h"


#include <iostream>

Object* test;

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, "Prototype"); //initialize window
	test = new Object();
}

void Application::Update()
{
		glWindow.SwapBuffers();
		glWindow.PollEvents();
		
		std::cout << test->GetXpos() << " " << test->GetYpos() << std::endl;
		test->SetXpos(static_cast<int>(1));
		test->SetYpos(static_cast<int>(1));

		if (glfwGetKey(glWindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			gameEngine->Shutdown();
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


