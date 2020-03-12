/**************************************************************************************
 *	File Name        : ComponentSprite.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "ComponentSprite.h"
#include "ObjectMaterial.h"
#include "UnitStateComponent.hpp"

void SpriteComponent::ChangeAnimation()
{
	if (unit != nullptr && (unit->GetComponent<UnitState>()->GetType() == UnitType::Player || UnitType::Enemy))
	{
		if (unit->GetComponent<UnitState>()->GetState() == State::WALK && unit->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			unit->GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(moveSpritePath);
			unit->GetComponent<MaterialComponent>()->material.animation.ChangeAnimation(moveSpriteColumnRow.x, moveSpriteColumnRow.y);
			unit->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (unit->GetComponent<UnitState>()->GetState() == State::ATTACK && unit->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			unit->GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(attackSpritePath);
			unit->GetComponent<MaterialComponent>()->material.animation.ChangeAnimation(attackSpriteColumnRow.x, attackSpriteColumnRow.y);
			unit->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
	}
}
