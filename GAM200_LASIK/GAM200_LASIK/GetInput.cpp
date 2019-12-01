#include <iostream>
#include <string>
#include "GetInput.hpp"
#include "Object.h"
#include "ObjectFactory.h"

void GetInput::TakeAsInput(char input)
{
	string.push_back(input);
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
