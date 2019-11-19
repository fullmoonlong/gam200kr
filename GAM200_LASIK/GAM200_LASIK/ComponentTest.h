#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"
#include "Sound.hpp"

class TestComponent : public Component
{
public:
	TestComponent() : Component(ComponentType::TEST), object(){};
	~TestComponent() override;
	virtual void Initialize() override;
	virtual void Update(float dt) override;

	Object* object;
	Object* attack;
	float baseTime = 0.f;
	
};