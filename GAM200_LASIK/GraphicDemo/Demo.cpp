/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Demo.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.28 2019
 *******************************************************/

#include <iostream>
#include "Demo.hpp"

void Demo::HandleKeyPress(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::Arrow_Left:
		// previous stage
		std::cout << "Previous Stage\n";
		break;
	case KeyboardButton::Arrow_Right:
		// next stage
		std::cout << "Next Stage\n";
		break;
	}
}

void Demo::HandleResizeEvent(const int& new_width, const int& new_height)
{
	view.SetViewSize(new_width, new_height);
}