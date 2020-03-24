/**************************************************************************************
 *	File Name        : AttackComponent.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "AttackComponent.h"
#include "PATH.hpp"
#include "ObjectFactory.h"
#include "UnitStateComponent.hpp"
#include "GameManager.h"
void ObjectAttackComponent::Initialize()
{
}

void ObjectAttackComponent::Update(float dt)
{
	if (unit->GetComponent<UnitState>()->GetIsSkillHave() == true && unit->GetComponent<UnitState>()->GetIsSkillStateOn() == false)
	{
		testgageDeltaTime += dt;
		if (testgageDeltaTime > 1.f)
		{
			unit->GetComponent<UnitState>()->SetSkillGauge((unit->GetComponent<UnitState>()->GetSkillGauge() + 10));
			testgageDeltaTime = 0.f;
		}
	}

	if (unit->GetComponent<UnitState>()->GetState() == State::ATTACK) {
		if (unit->GetComponent<UnitState>()->GetIsSkillHave() == true)
		{
			if (unit->GetComponent<UnitState>()->GetSkillGauge() >= unit->GetComponent<UnitState>()->GetFullSkillGauge())
			{
				unit->GetComponent<UnitState>()->SetSkillGauge((unit->GetComponent<UnitState>()->GetFullSkillGauge()));
				if (skillTimes == SkillType::REPEAT)
				{
					RepeatShot(dt);
				}
				else if (skillTimes == SkillType::SPECIFIC)
				{
					SpecificShot(dt);
				}
			}
		}

		time += dt;
		if (time > delayTime&& unit->GetComponent<UnitState>()->GetIsSkillStateOn() == false) {
			SOUNDMANAGER->PlaySound(0, soundID);
			projectile->transform.SetTranslation({ unit->transform.GetTranslation().x + startPosition.x, unit->transform.GetTranslation().y + startPosition.y });
			GAMEMANAGER->SpawnUnit(projectile);
			time = 0.f;
		}
	}
}

void ObjectAttackComponent::RepeatShot(float dt)
{
	unit->GetComponent<UnitState>()->SetIsSkillStateOn(true);
	unit->GetComponent<UnitState>()->SetSkillGauge(0);
	while (skillFullTimes == skillTimes) 
	{
		skillDeltaTime += dt;
		if (skillDeltaTime > skillDelayTime)
		{
			SOUNDMANAGER->PlaySound(0, skillSoundID);
			skillProjectile->transform.SetTranslation({ unit->transform.GetTranslation().x + startPosition.x, unit->transform.GetTranslation().y + startPosition.y });
			GAMEMANAGER->SpawnUnit(skillProjectile);
			skillDeltaTime = 0.f;
			skillTimes++;
		}
	}
	time = 0.f;
	skillTimes = 0;
	unit->GetComponent<UnitState>()->SetIsSkillStateOn(false);
}

void ObjectAttackComponent::SpecificShot(float dt)
{
	unit->GetComponent<UnitState>()->SetIsSkillStateOn(true);
	skillDeltaTime += dt;
	if (skillDeltaTime > skillDelayTime)
	{
		unit->GetComponent<UnitState>()->SetSkillGauge(0);
		SOUNDMANAGER->PlaySound(0, skillSoundID);
		skillProjectile->transform.SetTranslation({ unit->transform.GetTranslation().x + startPosition.x, unit->transform.GetTranslation().y + startPosition.y });
		GAMEMANAGER->SpawnUnit(skillProjectile);
		time = 0.f;
		skillDeltaTime = 0.f;
		unit->GetComponent<UnitState>()->SetIsSkillStateOn(false);
	}
}

void BaseObjectAttackComponent::SetSpecificShot(Object* skill_projectile, float skill_delay_time, int skill_soundID)
{
	if (skillTimes == SkillType::NOTHING)
	{
		unit->GetComponent<BaseUnitState>()->SetIsSkillHave(true);
		skillTimes = SkillType::SPECIFIC;
		skillProjectile = skill_projectile;
		skillDelayTime = skill_delay_time;
		skillSoundID = skill_soundID;
	}
}

void BaseObjectAttackComponent::SetRepeatShot(Object* skill_projectile, float skill_delay_time, int skill_full_times, int skill_soundID)
{
	if (skillTimes == SkillType::NOTHING)
	{
		unit->GetComponent<BaseUnitState>()->SetIsSkillHave(true);
		skillTimes = SkillType::REPEAT;
		skillProjectile = skill_projectile;
		skillDelayTime = skill_delay_time;
		skillFullTimes = skill_full_times;
		skillSoundID = skill_soundID;
	}
}
