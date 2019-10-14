#pragma once
#include "Component.h"
#include "ComponentType.h"

class TestComponent : public Component
{
public:
	TestComponent() : Component(ComponentType::TEST), x(0.f), y(0.0) {};
	~TestComponent() override;
	virtual void Initialize() override;
	virtual void Update() override;

	float x;
	float y;
};