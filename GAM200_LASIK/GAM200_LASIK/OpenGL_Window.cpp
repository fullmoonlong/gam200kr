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

#include <GL\glew.h>
#include "OpenGL_Window.h"
#include <iostream>
#include "EventHandler.hpp"

EventHandler* eventHandler;
bool isTriggered = false;

void frame_buffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

//void resize_callback()
//{
//	eventHandler->HandleResizeEvent();
//}

void window_close_callback()
{
	eventHandler->HandleWindowClose();
}

void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
	if (isTriggered == true && action == GLFW_PRESS)
	{
		isTriggered = true;
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			eventHandler->HandleKeyPress(KeyboardButtons::Escape);
			break;
		//case GLFW_KEY_F:
		//	break;
		//	//TODO: some key board cases
		default:
			break;
		}
	}
	else // Triggered
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			eventHandler->HandleKeyTriggered(KeyboardButtons::Escape);
			break;
		default:
			break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		isTriggered = false;
		//switch (key)
		//{
		//case GLFW_KEY_ESCAPE:
		//	break;
		//case GLFW_KEY_F:
		//	break;
		//}
	}
}

//void mouse_input_callback()
//{
//	
//}

bool glWindow::CanCreateWindow(int width, int height, EventHandler* event_handler, const char* title) noexcept
{
	eventHandler = event_handler;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	if (!glfwInit())
	{
		glfwTerminate();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* shareWindow = nullptr;
	
	window = glfwCreateWindow(width, height, title, monitor, shareWindow);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	ToggleVSync(true);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	//glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetKeyCallback(window, key_callback);
	
	ToggleVSync(true);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << glewGetErrorString(err);
		return false;
	}

	return true;
}

bool glWindow::IsVSyncOn() noexcept
{
	return isVSyncOn;
}

void glWindow::ToggleVSync(bool status) noexcept
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

void glWindow::ToggleFullScreen() noexcept
{
	if (!IsFullScreen())
	{
		glfwGetWindowPos(window, &windowPos[0], &windowPos[1]);
		glfwGetWindowSize(window, &windowSize[0], &windowSize[1]);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
		isFullScreen = true;
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, windowPos[0], windowPos[1], windowSize[0], windowSize[1], 0);
		isFullScreen = false;
	}
}

void glWindow::SetWindowTitle(const char* title) const noexcept
{
	glfwSetWindowTitle(window, title);
}
