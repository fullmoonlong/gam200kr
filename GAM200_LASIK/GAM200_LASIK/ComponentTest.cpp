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
	if (object->GetState() == State::ATTACK)
	{
			baseTime += 0.1f;
			if (baseTime <= 80.f)
			{
				baseTime = 0;
				attack->transform.SetTranslation(object->transform.GetTranslation());
				OBJECTFACTORY->CopyObject(attack);
			}
	}
}
