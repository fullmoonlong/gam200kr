/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: OpenGL_Window.cpp
*	
*	Implementing of openGL window functions
*	
*	2019/09/21
*/

#include "OpenGL_Window.h"

bool glWindow::CanCreateWindow(int width, int height, const char* title) noexcept
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	if (!glfwInit())
	{
		glfwTerminate();
		return false;
	} 

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* shareWindow = nullptr;

	window = glfwCreateWindow(width, height, title, monitor, shareWindow);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	TurnOnVSync(true);

	return true;
}

bool glWindow::IsVSyncOn() noexcept
{
	return isVSyncOn;
}

void glWindow::TurnOnVSync(bool status) noexcept
{
	isVSyncOn = status;
	glfwSwapInterval(isVSyncOn);
}

void glWindow::SwapBuffers() noexcept
{
	glfwSwapBuffers(window);
}

void glWindow::PollEvents() noexcept
{
	glfwPollEvents();
}
