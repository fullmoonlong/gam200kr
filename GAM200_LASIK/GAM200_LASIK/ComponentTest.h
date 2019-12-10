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
	virtual void Update(float time_) override;
	//void Attack();

	//Object* object;
	Object* attack;
	float time = 0;
};