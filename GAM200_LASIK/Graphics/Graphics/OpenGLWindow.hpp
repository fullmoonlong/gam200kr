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

#pragma once
#include <memory>

class EventHandler;
class PlatformWindow;

class OpenGLWindow
{
public:
	OpenGLWindow() noexcept;
	~OpenGLWindow() noexcept;

	bool CanCreateWindow(int width, int height, EventHandler* event_handler, const char* title) noexcept;
	void SwapBuffers() noexcept;
	void PollEvents() noexcept;

	void ToggleVSync(bool status) noexcept;
	bool IsVSyncOn() noexcept;
	void ToggleFullScreen() noexcept;
	bool IsFullScreen() noexcept;

	void SetWindowTitle(const char* title) const noexcept;
	void SetWindowIcon() const noexcept;

	int GetWindowWidth() const noexcept;
	void SetWindowWidth(int new_width) noexcept;
	int GetWindowHeight() const noexcept;
	void SetWindowHeight(int new_height) noexcept;
private:
	std::unique_ptr<PlatformWindow> platformWindow;
};