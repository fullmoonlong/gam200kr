/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: main.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.25 2019
 *******************************************************/

#include "Application.h"

int main()
{
	//ShapeDrawingDemo demo;

	Application app;
	
	//demo.Initialize();

	while (app.IsRunning())
	{
		app.Update();
	}

	return 0;
}