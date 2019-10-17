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
#include <graphic/OpenGL_Window.h>
#include <graphic/EventHandler.hpp>
#include <iostream>

EventHandler* eventHandler;

void frame_buffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

void resize_callback(GLFWwindow*, int width, int height)
{
	eventHandler->HandleResizeEvent(width, height);
}

void window_close_callback()
{
	eventHandler->HandleWindowClose();
}


void key_callback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			eventHandler->HandleKeyPress(KeyboardButtons::Escape);
			break;
		case GLFW_KEY_F:
			eventHandler->HandleKeyPress(KeyboardButtons::F);
			break;
		case GLFW_KEY_V:
			eventHandler->HandleKeyPress(KeyboardButtons::V);
			break;
		case GLFW_KEY_G:
			eventHandler->HandleKeyPress(KeyboardButtons::G);
			break;
		case GLFW_KEY_W:
			eventHandler->HandleKeyPress(KeyboardButtons::W);
			break;
		case GLFW_KEY_A:
			eventHandler->HandleKeyPress(KeyboardButtons::A);
			break;
		case GLFW_KEY_S:
			eventHandler->HandleKeyPress(KeyboardButtons::S);
			break;
		case GLFW_KEY_D:
			eventHandler->HandleKeyPress(KeyboardButtons::D);
			break;
		case GLFW_KEY_Z:
			eventHandler->HandleKeyPress(KeyboardButtons::Z);
			break;
		case GLFW_KEY_X:
			eventHandler->HandleKeyPress(KeyboardButtons::X);
			break;
		case GLFW_KEY_LEFT:
			eventHandler->HandleKeyPress(KeyboardButtons::Arrow_Left);
			break;
		case GLFW_KEY_RIGHT:
			eventHandler->HandleKeyPress(KeyboardButtons::Arrow_Right);
			break;
		case GLFW_KEY_UP:
			eventHandler->HandleKeyPress(KeyboardButtons::Arrow_Up);
			break;
		case GLFW_KEY_DOWN:
			eventHandler->HandleKeyPress(KeyboardButtons::Arrow_Down);
			break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			eventHandler->HandleKeyRelease(KeyboardButtons::W);
			break;
		case GLFW_KEY_A:
			eventHandler->HandleKeyRelease(KeyboardButtons::A);
			break;
		case GLFW_KEY_S:
			eventHandler->HandleKeyRelease(KeyboardButtons::S);
			break;
		case GLFW_KEY_D:
			eventHandler->HandleKeyRelease(KeyboardButtons::D);
			break;
		case GLFW_KEY_Z:
			eventHandler->HandleKeyRelease(KeyboardButtons::Z);
			break;
		case GLFW_KEY_X:
			eventHandler->HandleKeyRelease(KeyboardButtons::X);
			break;
		}
	}
}

//void mouse_input_callback()
//{
//	
//}

void scroll_callback(GLFWwindow*, double, double y_offset)
{
	eventHandler->HandleScrollEvent(float(y_offset));
}

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

	windowSize[0] = width;
	windowSize[1] = height;

	ToggleVSync(true);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	glfwSetWindowSizeCallback(window, resize_callback);
	//glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

int glWindow::GetWindowWidth() const noexcept
{
	return windowSize[0];
}

int glWindow::GetWindowHeight() const noexcept
{
	return windowSize[1];
}

void glWindow::SetWindowWidth(int new_width) noexcept
{
	windowSize[0] = new_width;
}

void glWindow::SetWindowHeight(int new_height) noexcept
{
	windowSize[1] = new_height;
}
