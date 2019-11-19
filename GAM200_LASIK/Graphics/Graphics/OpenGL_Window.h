/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: OpenGL_Window.h
 *	
 *	Header for window
 *	
 *	2019/09/21
 *	
 *	DoYoung Implemented fullscreen functions
 */

#pragma once
#include "glfw3.h"

class EventHandler;

class [[nodiscard]] Window
{
public:
	GLFWwindow* window;

	bool CanCreateWindow(int width, int height, EventHandler* event_handler, const char* title) noexcept;
	bool IsVSyncOn() noexcept;
	void ToggleVSync(bool status) noexcept;
	void SwapBuffers() noexcept;
	void PollEvents() noexcept;
	bool IsFullScreen() noexcept;
	void ToggleFullScreen() noexcept;
	void SetWindowTitle(const char* title) const noexcept;
	void SetWindowIcon() const noexcept;
	int GetWindowWidth() const noexcept;
	int GetWindowHeight() const noexcept;

	void SetWindowWidth(int new_width) noexcept;
	void SetWindowHeight(int new_height) noexcept;
	
private:
	bool isVSyncOn = false;
	bool isFullScreen = false;
	int windowPos[2] = { 0,0 };
	int windowSize[2] = { 0,0 };
	int sizeBackup[2] = { 0,0 };
	int posBackup[2] = { 0,0 };
};
