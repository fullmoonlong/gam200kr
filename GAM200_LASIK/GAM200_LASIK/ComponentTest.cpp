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

void TestComponent::Update(float /*delta_time*/)
{
}
//
//void TestComponent::Attack()
//{
//	attack->transform.SetTranslation(object->transform.GetTranslation());
//	OBJECTFACTORY->CopyObject(attack);
//}
