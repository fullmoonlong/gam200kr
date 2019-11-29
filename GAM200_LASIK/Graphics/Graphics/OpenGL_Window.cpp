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
			eventHandler->HandleKeyPress(KeyboardButton::Escape);
			break;
		case GLFW_KEY_F:
			eventHandler->HandleKeyPress(KeyboardButton::F);
			break;
		case GLFW_KEY_V:
			eventHandler->HandleKeyPress(KeyboardButton::V);
			break;
		case GLFW_KEY_G:
			eventHandler->HandleKeyPress(KeyboardButton::G);
			break;
		case GLFW_KEY_W:
			eventHandler->HandleKeyPress(KeyboardButton::W);
			break;
		case GLFW_KEY_A:
			eventHandler->HandleKeyPress(KeyboardButton::A);
			break;
		case GLFW_KEY_S:
			eventHandler->HandleKeyPress(KeyboardButton::S);
			break;
		case GLFW_KEY_D:
			eventHandler->HandleKeyPress(KeyboardButton::D);
			break;
		case GLFW_KEY_Z:
			eventHandler->HandleKeyPress(KeyboardButton::Z);
			break;
		case GLFW_KEY_X:
			eventHandler->HandleKeyPress(KeyboardButton::X);
			break;
		case GLFW_KEY_I:
			eventHandler->HandleKeyPress(KeyboardButton::I);
			break;
		case GLFW_KEY_O:
			eventHandler->HandleKeyPress(KeyboardButton::O);
			break;
		case GLFW_KEY_LEFT:
			eventHandler->HandleKeyPress(KeyboardButton::Arrow_Left);
			break;
		case GLFW_KEY_RIGHT:
			eventHandler->HandleKeyPress(KeyboardButton::Arrow_Right);
			break;
		case GLFW_KEY_UP:
			eventHandler->HandleKeyPress(KeyboardButton::Arrow_Up);
			break;
		case GLFW_KEY_DOWN:
			eventHandler->HandleKeyPress(KeyboardButton::Arrow_Down);
			break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			eventHandler->HandleKeyRelease(KeyboardButton::Escape);
			break;
		case GLFW_KEY_F:
			eventHandler->HandleKeyRelease(KeyboardButton::F);
			break;
		case GLFW_KEY_V:
			eventHandler->HandleKeyRelease(KeyboardButton::V);
			break;
		case GLFW_KEY_G:
			eventHandler->HandleKeyRelease(KeyboardButton::G);
			break;
		case GLFW_KEY_W:
			eventHandler->HandleKeyRelease(KeyboardButton::W);
			break;
		case GLFW_KEY_A:
			eventHandler->HandleKeyRelease(KeyboardButton::A);
			break;
		case GLFW_KEY_S:
			eventHandler->HandleKeyRelease(KeyboardButton::S);
			break;
		case GLFW_KEY_D:
			eventHandler->HandleKeyRelease(KeyboardButton::D);
			break;
		case GLFW_KEY_Z:
			eventHandler->HandleKeyRelease(KeyboardButton::Z);
			break;
		case GLFW_KEY_X:
			eventHandler->HandleKeyRelease(KeyboardButton::X);
			break;
		case GLFW_KEY_I:
			eventHandler->HandleKeyRelease(KeyboardButton::I);
			break;
		case GLFW_KEY_O:
			eventHandler->HandleKeyRelease(KeyboardButton::O);
			break;
		case GLFW_KEY_LEFT:
			eventHandler->HandleKeyRelease(KeyboardButton::Arrow_Left);
			break;
		case GLFW_KEY_RIGHT:
			eventHandler->HandleKeyRelease(KeyboardButton::Arrow_Right);
			break;
		case GLFW_KEY_UP:
			eventHandler->HandleKeyRelease(KeyboardButton::Arrow_Up);
			break;
		case GLFW_KEY_DOWN:
			eventHandler->HandleKeyRelease(KeyboardButton::Arrow_Down);
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
			eventHandler->HandleMouseEvent(MouseButton::LEFT_PRESS);
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			eventHandler->HandleMouseEvent(MouseButton::LEFT_RELEASE);
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

void window_focus_callback(GLFWwindow*, int focus)
{
	eventHandler->HandleFocusEvent(focus);
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
	glfwSetWindowFocusCallback(window, window_focus_callback);

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
