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
	virtual void Update(float /*dt*/) override {};
	virtual void SpawnEnemy(Object* obj, float dt);

	Object* object;
	int time;
};