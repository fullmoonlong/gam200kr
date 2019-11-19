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

#include <iostream>
#include "GL/glew.h"
#include "OpenGL_Window.h"
#include "PATH.hpp"
#include "EventHandler.hpp"
#include <stb_image.h>

EventHandler* eventHandler;

void frame_buffer_size_callback(GLFWwindow* /*window*/, int width, int height)
{
	glViewport(0, 0, width, height);
}

void resize_callback(GLFWwindow* /*window*/, int width, int height)
{
	eventHandler->HandleResizeEvent(width, height);
}

void window_close_callback(GLFWwindow* /*window*/)
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

void mouse_button_callback(GLFWwindow*, int button, int action, int /*mods*/)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			eventHandler->HandleMouseEvent(MouseButtons::LEFT_PRESS);
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			eventHandler->HandleMouseEvent(MouseButtons::LEFT_RELEASE);
			break;
		}
	}
}

void scroll_callback(GLFWwindow*, double, double y_offset)
{
	eventHandler->HandleScrollEvent(float(y_offset));
}

static void cursor_position_callback(GLFWwindow*, double xpos, double ypos)
{
	eventHandler->HandleMousePositionEvent(float(xpos), float(ypos));
}

bool Window::CanCreateWindow(int width, int height, EventHandler* event_handler, const char* title) noexcept
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
	glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cerr << glewGetErrorString(err);
		return false;
	}

	SetWindowIcon();
	
	return true;
}

bool Window::IsVSyncOn() noexcept
{
	return isVSyncOn;
}

void Window::ToggleVSync(bool status) noexcept
{
	isVSyncOn = status;
	glfwSwapInterval(isVSyncOn);
}

void Window::SwapBuffers() noexcept
{
	glfwSwapBuffers(window);
}

void Window::PollEvents() noexcept
{
	glfwPollEvents();
}

bool Window::IsFullScreen() noexcept
{
	return isFullScreen;
}

void Window::ToggleFullScreen() noexcept
{
	isFullScreen = !isFullScreen;
	if (!IsFullScreen())
	{
		glfwGetWindowPos(window, &posBackup[0], &posBackup[1]);
		glfwGetWindowSize(window, &sizeBackup[0], &sizeBackup[1]);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{
		glfwSetWindowMonitor(window, nullptr, posBackup[0], posBackup[1], sizeBackup[0], sizeBackup[1], 0);
	}
}

void Window::SetWindowTitle(const char* title) const noexcept
{
	glfwSetWindowTitle(window, title);
}

void Window::SetWindowIcon() const noexcept
{
	GLFWimage icon;
	icon.pixels = stbi_load(PATH::icon_image.generic_string().c_str() , &icon.width, &icon.height, 0, STBI_rgb_alpha);
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(icon.pixels);
}

int Window::GetWindowWidth() const noexcept
{
	return windowSize[0];
}

int Window::GetWindowHeight() const noexcept
{
	return windowSize[1];
}

void Window::SetWindowWidth(int new_width) noexcept
{
	windowSize[0] = new_width;
}

void Window::SetWindowHeight(int new_height) noexcept
{
	windowSize[1] = new_height;
}
