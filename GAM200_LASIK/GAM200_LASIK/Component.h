/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/10/12
*/
#pragma once
#include "ComponentType.h"

class Object;
class Component
{
public:
	friend class Object;

	Component(ComponentType type) : componentType(type) {};
	virtual ~Component() { };

	virtual void Initialize() {};

	Object * GetOwner() const { return pOwner; }
	void SetOwner(Object * owner) { pOwner = owner; }
	ComponentType GetType() { return componentType; }
	Object* pOwner = nullptr;
	ComponentType componentType;
};