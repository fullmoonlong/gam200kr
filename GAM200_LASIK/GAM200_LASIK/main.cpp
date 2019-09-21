/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: main.cpp
*	
*	GAM200 Engine Prototype
*	
*	2019/07/04
*/

/*
 *	Separate solution or share folder
 *	Same graphics engine but different game with GAM200 in CS200
 */

#include <glfw3.h>
#include "OpenGL_Window.h"

int main()
{
	bool isRunning = false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glWindow glWindow;

	glWindow.CanCreateWindow(800, 600, "Prototype");

	isRunning = true;

	while (isRunning)
	{
		glWindow.SwapBuffers();
		glWindow.PollEvents();
		if (glfwGetKey(glWindow.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		{
			isRunning = false;
		}
		else if (glfwGetKey(glWindow.window, GLFW_KEY_V) == GLFW_PRESS)
		{
			glWindow.TurnOnVSync(!glWindow.IsVSyncOn());
		}
	}
}
