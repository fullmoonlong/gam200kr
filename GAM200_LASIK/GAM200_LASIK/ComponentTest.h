#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"
#include "Sound.hpp"

class TestComponent : public Component
{
public:
	TestComponent() : Component(ComponentType::TEST) {};
	~TestComponent() override;
	virtual void Initialize() override;
	//void Attack();

	//Object* object;
	Object* attack;
	float time = 0;
};