/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/10/12
*/
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