/**************************************************************************************
 *	File Name        : Component.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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