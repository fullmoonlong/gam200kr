#include <iostream>
#include <string>
#include "GetInput.hpp"
#include "Object.h"
#include "ObjectFactory.h"

void GetInput::TakeAsInput()
{
	std::string stack;

	std::cin >> stack;

	input = stack;
}

int GetInput::MatchStringWithInput()
{
	if (input == knight)
	{
		// spawn knight
		return 1;
	}
	else if (input == archer)
	{
		// spawn archer
		return 2;
	}
	else if (input == magician)
	{
		// spawn magician
		return 3;
	}
	return 0;
}
