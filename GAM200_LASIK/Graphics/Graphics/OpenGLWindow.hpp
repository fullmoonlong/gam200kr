/**************************************************************************************
 *	File Name        : OpenGLWindow.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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