/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/12/05
*/
#include "ComponentTower.h"
#include "ObjectFactory.h"
#include <iostream>

LairComponent::~LairComponent()
{
}

void LairComponent::Initialize()
{
}

void LairComponent::SpawnEnemy(Object* obj, float dt)
{
	time += dt;

	if (time > 6.0f)
	{
		OBJECTFACTORY->CopyObject(obj);
		time = 0.f;
	}
}
