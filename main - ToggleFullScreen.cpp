/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	GAM200 Engine Prototype
*	2019/07/04
*/

/*
 *	Separate solution or share folder
 *	Same graphics engine but different game with GAM200 in CS200
 */

#include <glfw3.h>

//bool isFullScreen = false;
//int windowPos[2];
//int windowSize[2]; //need to put in window class
//
//void ToggleFullScreen(GLFWwindow* window) noexcept
//{
//	if (isFullScreen == false)
//	{
//		glfwGetWindowPos(window, &windowPos[0], &windowPos[1]);
//		glfwGetWindowSize(window, &windowSize[0], &windowSize[1]);
//
//		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
//		isFullScreen = true;
//	}
//	else
//	{
//		glfwSetWindowMonitor(window, nullptr, windowPos[0], windowPos[1], windowSize[0],
//			windowSize[1], 0);
//		isFullScreen = false;
//	}
//}

int main()
{
	bool isRunning = false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	if (!glfwInit())
	{
		glfwTerminate();
		return -1;		//return false
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Prototype", nullptr, nullptr);
	
	if (!window)
	{
		glfwTerminate();
		return -1;		//return false
	}

	glfwSwapInterval(1);

	isRunning = true;

	while (isRunning)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			isRunning = false;
		}
	//	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	//	{
	//		ToggleFullScreen(window);
	//	}
	//}
}
