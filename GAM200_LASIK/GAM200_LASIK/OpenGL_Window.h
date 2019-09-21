/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: OpenGL_Window.cpp
*	
*	Header for related to window.
*	
*	2019/09/21
*/

#pragma once
#include <glfw3.h>

class glWindow
{
public:
	GLFWwindow* window;

	bool CanCreateWindow(int width, int height, const char* title) noexcept;
	bool IsVSyncOn() noexcept;
	void TurnOnVSync(bool status) noexcept;
	void SwapBuffers() noexcept;
	void PollEvents() noexcept;

private:
	bool isVSyncOn = true;

};
