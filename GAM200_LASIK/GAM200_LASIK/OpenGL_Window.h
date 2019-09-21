/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: OpenGL_Window.cpp
*	
*	Header for related to window.
*	
*	2019/09/21
*	
*	DoYoung Implemented fullscreen functions
*/

#pragma once
#include <glfw3.h>

class glWindow
{
public:
	GLFWwindow* window;

	bool CanCreateWindow(int width, int height, const char* title) noexcept;
	bool IsVSyncOn() noexcept;
	void ToggleOnVSync(bool status) noexcept;
	void SwapBuffers() noexcept;
	void PollEvents() noexcept;
	bool IsFullScreen() noexcept;
	void ToggleFullScreen(GLFWwindow* selectedWindow) noexcept;

private:
	bool isVSyncOn = true;
	bool isFullScreen = false;
	int windowPos[2] = { 0,0 };
	int windowSize[2] = { 0,0 };

};
