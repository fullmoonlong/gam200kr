/**************************************************************************************
 *	File Name        : ComponentAttack.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "ComponentAttack.h"
#include "PATH.hpp"
#include "ObjectFactory.h"
#include "UnitStateComponent.hpp"
#include "GameManager.h"
void ObjectAttackComponent::Initialize()
{
}

void ObjectAttackComponent::Update(float dt)
{
	if (unit->GetComponent<UnitState>()->GetState() == State::ATTACK) {
		time += dt;
		if (time > delayTime) {
			SOUNDMANAGER->PlaySound(0, soundID);
			projectile->transform.SetTranslation({ unit->transform.GetTranslation().x + startPosition.x, unit->transform.GetTranslation().y + startPosition.y });
			GAMEMANAGER->SpawnUnit(projectile);
			time = 0;
		}
	}
}
