/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/12/13
*/
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

	Material material;
};