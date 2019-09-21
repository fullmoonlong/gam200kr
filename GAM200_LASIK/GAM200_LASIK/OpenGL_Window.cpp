/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: OpenGL_Window.cpp
*	
*	Implementing of openGL window functions
*	
*	2019/09/21
*	
*	DoYoung Implemented fullscreen functions
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

	ToggleOnVSync(true);

	return true;
}

bool glWindow::IsVSyncOn() noexcept
{
	return isVSyncOn;
}

void glWindow::ToggleOnVSync(bool status) noexcept
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

bool glWindow::IsFullScreen() noexcept
{
	return isFullScreen;
}

void glWindow::ToggleFullScreen(GLFWwindow* selectedWindow) noexcept
{
	if (!IsFullScreen())
	{
		glfwGetWindowPos(selectedWindow, &windowPos[0], &windowPos[1]);
		glfwGetWindowSize(selectedWindow, &windowSize[0], &windowSize[1]);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(selectedWindow, monitor, 0, 0, mode->width, mode->height, 0);
		isFullScreen = true;
	}
	else
	{
		glfwSetWindowMonitor(selectedWindow, nullptr, windowPos[0], windowPos[1], windowSize[0], windowSize[1], 0);
		isFullScreen = false;
	}
}
