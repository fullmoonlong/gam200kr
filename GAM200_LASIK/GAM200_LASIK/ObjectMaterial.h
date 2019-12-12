#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"
#include "Sound.hpp"
#include "draw.hpp"

class MaterialComponent : public Component
{
public:
	MaterialComponent() : Component(ComponentType::MATERIAL) {};
	~MaterialComponent() override;
	virtual void Initialize() override;
	//void Attack();

	Material material;
};