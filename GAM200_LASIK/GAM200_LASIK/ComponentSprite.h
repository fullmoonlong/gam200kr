/**************************************************************************************
 *	File Name        : ComponentSprite.h
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

class SpriteComponent : public Component
{
public:
	SpriteComponent() : Component(ComponentType::SPRITE) {};
	~SpriteComponent() override {};
	virtual void Initialize() override {};
	void ChangeAnimation();
	void SetUnit(Object* object_) { unit = object_; }

	Object* unit;
	std::filesystem::path moveSpritePath;
	std::filesystem::path attackSpritePath;

	vec2<int> moveSpriteColumnRow{ 0, 0 };
	vec2<int> attackSpriteColumnRow{ 0, 0 };
};