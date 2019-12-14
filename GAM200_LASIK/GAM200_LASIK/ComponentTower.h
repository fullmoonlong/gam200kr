/**************************************************************************************
 *	File Name        : ComponentTower.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"

class LairComponent : public Component
{
public:
	LairComponent() : Component(ComponentType::LAIR), object(), time(0){};
	~LairComponent() override;
	virtual void Initialize() override;
	virtual void SpawnEnemy(Object* obj, float dt);

	Object* object;
	float time;
};