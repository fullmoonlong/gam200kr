#include "ComponentTest.h"
#include <iostream>


TestComponent::~TestComponent()
{
}

void TestComponent::Initialize()
{
	std::cout << "Test Sucessful" << std::endl;
}

void TestComponent::Update()
{
	x++;
	y++;
}
