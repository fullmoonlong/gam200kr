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

#include "PlatformWindowGLFW.hpp"
#include "OpenGLWindow.hpp"

OpenGLWindow::OpenGLWindow() noexcept
	: platformWindow(std::make_unique<PlatformWindow>()) {}

OpenGLWindow::~OpenGLWindow() noexcept
{}

bool OpenGLWindow::CanCreateWindow(int width, int height, EventHandler* event_handler, const char* title) noexcept
{
	return platformWindow->CanCreateWindow(width, height, event_handler, title);
}

void OpenGLWindow::SwapBuffers() noexcept
{
	platformWindow->SwapBuffers();
}

void OpenGLWindow::PollEvents() noexcept
{
	platformWindow->PollEvents();
}

void OpenGLWindow::ToggleVSync(bool status) noexcept
{
	platformWindow->ToggleVSync(status);
}

bool OpenGLWindow::IsVSyncOn() noexcept
{
	return platformWindow->IsVSyncOn();
}

void OpenGLWindow::ToggleFullScreen() noexcept
{
	platformWindow->ToggleFullScreen();
}

bool OpenGLWindow::IsFullScreen() noexcept
{
	return platformWindow->IsFullScreen();
}

void OpenGLWindow::SetWindowTitle(const char* title) const noexcept
{
	platformWindow->SetWindowTitle(title);
}

void OpenGLWindow::SetWindowIcon() const noexcept
{
	platformWindow->SetWindowIcon();
}

int OpenGLWindow::GetWindowWidth() const noexcept
{
	return platformWindow->GetWindowWidth();
}

void OpenGLWindow::SetWindowWidth(int new_width) noexcept
{
	platformWindow->SetWindowHeight(new_width);
}

int OpenGLWindow::GetWindowHeight() const noexcept
{
	return platformWindow->GetWindowHeight();
}

void OpenGLWindow::SetWindowHeight(int new_height) noexcept
{
	platformWindow->SetWindowHeight(new_height);
}
