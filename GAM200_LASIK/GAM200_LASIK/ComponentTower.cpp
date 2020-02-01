/**************************************************************************************
 *	File Name        : ComponentTower.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "GameManager.h"
#include "ComponentTower.h"
#include "ObjectFactory.h"

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
		GAMEMANAGER->SpawnUnit(obj);
		time = 0.f;
	}
}
