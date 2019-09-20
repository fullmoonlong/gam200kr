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
	}
}
