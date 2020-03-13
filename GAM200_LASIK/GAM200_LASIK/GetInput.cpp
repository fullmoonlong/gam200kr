/**************************************************************************************
 *	File Name        : GetInput.cpp
 *	Project Name     : Keyboard Warriors
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

void GetInput::TakeAsSymbol(char input)
{
	symbol.push_back(input);
}

void GetInput::Erasing()
{
	if (string.size() > 0)
	{
		string.pop_back();
	}
	else if (symbol.size() > 0)
	{
		symbol.pop_back();
	}
}

int GetInput::MatchStringWithInput()
{
	// units
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
	// units
	// levels
	else if (string == tutorial)
	{
		return 4;
	}
	else if (string == level1)
	{
		return 5;
	}
	else if (string == upgrade)
	{
		return 6;
	}
	else if (string == levelSelect)
	{
		return 7;
	}
	//levels
	//upgrade

	else if (string == arthur)
	{
		return 20;
	}
	else if (string == artemis)
	{
		return 21;
	}
	else if (string == siegfried)
	{
		return 22;
	}
	else if (string == valkyrie)
	{
		return 23;
	}
	return 0;
}
