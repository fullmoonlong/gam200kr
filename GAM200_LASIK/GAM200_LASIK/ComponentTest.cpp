#include "ComponentTest.h"
#include <iostream>
#include "PATH.hpp"
#include "ObjectFactory.h"

TestComponent::~TestComponent()
{
}

void TestComponent::Initialize()
{
	std::cout << "Test Sucessful" << std::endl;
}
