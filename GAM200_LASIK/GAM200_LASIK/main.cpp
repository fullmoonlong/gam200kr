/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
*	
*	File_name: main.cpp
*	
*	main loop
*	
*	2019/07/04
*/

/*
 *	Separate solution or share folder
 *	Same graphics engine but different game with GAM200 in CS200
 */

#include <glfw3.h>
#include "OpenGL_Window.h"
#include "Application.h"

int main()
{
	Application application;
	application.Run();

	return 0;
}
