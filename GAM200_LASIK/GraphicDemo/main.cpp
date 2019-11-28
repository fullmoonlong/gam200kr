/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: main.cpp
 *	
 *	Graphic demo main file
 *	
 *	2019/11/25
 *******************************************************/

#include "GraphicDemo.h"

int main()
{
	GraphicDemo demo;

	while (demo.IsRunning())
	{
		demo.Update();
	}

	return 0;
}