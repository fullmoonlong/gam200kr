/**************************************************************************************
 *	File Name        : AttackComponent.h
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

enum SkillType {
	NOTHING,
	REPEAT,
	SPECIFIC
};

class BaseObjectAttackComponent : public Component
{
public:
	BaseObjectAttackComponent() : Component(ComponentType::ATTACKCOM) {};
	~BaseObjectAttackComponent() override {};
	virtual void Initialize() override {};

	void SetSpecificShot(Object* skill_projectile, float skill_delay_time, int skill_soundID);
	void SetRepeatShot(Object* skill_projectile, float skill_delay_time, int skill_full_times, int skill_soundID);

	Object* unit;
	Object* projectile;
	Object* skillProjectile;

	float time = 0;
	float delayTime = 0;
	int soundID;

	float skillDeltaTime = 0.f;
	float skillDelayTime = 0.f;
	int skillSoundID;
	int skillFullTimes;
	int skillTimes = 0;

	SkillType skillType;
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

	void RepeatShot(float dt);
	void SpecificShot(float dt);
	
	Object* unit;
	Object* projectile;
	Object* skillProjectile;

	float testgageDeltaTime = 0.f;
	float time = 0;
	float delayTime = 0;
	int soundID;
	
	float skillDeltaTime = 0.f;
	float skillDelayTime = 0.f;
	int skillSoundID;
	int skillFullTimes;
	int skillTimes = 0;
	
	SkillType skillType = NOTHING;

	vec2<float> startPosition{ 0, 0 };
};