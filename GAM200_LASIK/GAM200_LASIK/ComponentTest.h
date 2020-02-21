/**************************************************************************************
 *	File Name        : ComponentTest.h
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
#include "Sound.hpp"
#include "vec2.hpp"

class BaseObjectAttackComponent : public Component
{
public:
	BaseObjectAttackComponent() : Component(ComponentType::ATTACKCOM) {};
	~BaseObjectAttackComponent() override {};
	virtual void Initialize() override {};

	Object* unit;
	Object* projectile;

	float time = 0;
	float delayTime = 0;
	int soundID;

	vec2<float> startPosition{ 0, 0 };
};

class ObjectAttackComponent : public Component
{
public:
	ObjectAttackComponent() : Component(ComponentType::ATTACKCOM) {};
	~ObjectAttackComponent() override {};
	virtual void Initialize() override;
	void Update(float dt);
	
	void SetUnit(Object* object_) { unit = object_; }

	Object* unit;
	Object* projectile;

	float time = 0;
	float delayTime = 0;
	int soundID;

	vec2<float> startPosition{ 0, 0 };
};