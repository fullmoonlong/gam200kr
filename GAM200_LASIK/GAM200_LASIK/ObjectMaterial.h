/**************************************************************************************
 *	File Name        : ObjectMaterial.h
 *	Project Name     : Keyboard Warrior
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
#include "draw.hpp"

class MaterialComponent : public Component
{
public:
	MaterialComponent() : Component(ComponentType::MATERIAL) {};
	~MaterialComponent() override;
	virtual void Initialize() override;

	Material material;
};