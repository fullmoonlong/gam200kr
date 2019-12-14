/**************************************************************************************
 *	File Name        : GetInput.cpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : Jookyung Lee
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include <string>
#include "GetInput.hpp"
#include "Object.h"
#include "ObjectFactory.h"

void GetInput::TakeAsInput(char input)
{
	string.push_back(input);
}

void GetInput::Erasing()
{
	if (string.size() > 0)
	{
		string.pop_back();
	}
}

int GetInput::MatchStringWithInput()
{
	if (string == knight)
	{
		// spawn knight
		return 1;
	}
	else if (string == archer)
	{
		// spawn archer
		return 2;
	}
	else if (string == magician)
	{
		// spawn magician
		return 3;
	}
	return 0;
}
