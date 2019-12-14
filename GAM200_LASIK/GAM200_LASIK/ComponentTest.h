/**************************************************************************************
 *	File Name        : ComponentTest.h
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"
#include "Sound.hpp"

class ObjectAttackComponent : public Component
{
public:
	ObjectAttackComponent() : Component(ComponentType::ATTACKCOM) {};
	~ObjectAttackComponent() override;
	virtual void Initialize() override;

	Object* attack;
	float time = 0;
};