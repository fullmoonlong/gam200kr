/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/

#include "Object.h"
#include "FileLoadAndSave.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include "ComponentTest.h"

Object::Object()
	: objectID(0), position(0) {}

void Object::Initialize(const char* name) noexcept
{
	File data;

	data.Open(name);
	data.GetFloat(&position.x);
	data.GetFloat(&position.y);
	data.GetFloat(&size.x);
	data.GetFloat(&size.y);
	data.GetFloat(&speed.x);

	std::string unitdata;
	data.GetString(&unitdata);

	if (unitdata == "Player")
	{
		SetType(UnitType::Player);
	}
	else if (unitdata == "Enemy")
	{
		SetType(UnitType::Enemy);
	}
	else if (unitdata == "ProjectilesPlayer")
	{
		SetType(UnitType::ProjectilesPlayer);
	}
	else if (unitdata == "ProjectilesEnemy")
	{
		SetType(UnitType::ProjectilesEnemy);
	}

	data.GetString(&unitdata);
	SetName(unitdata);

	transform.SetTranslation(position);
	float half_width = size.x / 2;
	float half_height = size.y / 2;
	min = { position.x - half_width, position.y - half_height };
	max = { position.x + half_width, position.y + half_height };
	transform.SetScale({ size.x, size.y });
}

void Object::Update(float dt) noexcept
{
	for (auto com : componetList)
	{
		com->Update(dt);
	}
	if (state == State::WALK)
	{
		float decision_x = speed.x * dt;
		float decision_y = speed.y * dt;
		float dx = transform.GetTranslation().x + decision_x;
		float dy = transform.GetTranslation().y + decision_y;
		transform.SetTranslation({ dx, dy });
		position.x += decision_x;
		position.y += decision_y;
		float half_width = size.x / 2;
		float half_height = size.y / 2;
		min = { position.x - half_width, position.y - half_height };
		max = { position.x + half_width, position.y + half_height };
	}
	if (health <= 0 && (unitType == UnitType::Player || unitType == UnitType::Enemy))
	{
		OBJECTFACTORY->Destroy(this);
	}
}

Object* Object::Clone()
{
	return new Object(*this);
}

void Object::ChangeUnitAnimation()
{
	if (GetName() == "Knight")
	{
		if (GetState() == State::WALK && GetSpriteChangeState() == true)
		{
			animation.ChangeAnimation(PATH::knight_move, 8);
			SetSpriteChangeState(false);
		}
		else if (GetState() == State::ATTACK)
		{
			if (GetSpriteChangeState() == true && GetAttackState() == true)
			{
				animation.ChangeAnimation(PATH::knight_attack, 8);
				SetSpriteChangeState(false);
			}
		}

	}
	else if (GetName() == "Archer")
	{
		if (GetState() == State::WALK && GetSpriteChangeState() == true)
		{
			animation.ChangeAnimation(PATH::archer_move, 8);
			SetSpriteChangeState(false);
		}
		else if (GetState() == State::ATTACK)
		{
			if (GetSpriteChangeState() == true)
			{
				animation.ChangeAnimation(PATH::archer_attack, 8);
				SetSpriteChangeState(false);
			}
		}
	}
	else if (GetName() == "Magician")
	{
		if (GetState() == State::WALK && GetSpriteChangeState() == true)
		{
			animation.ChangeAnimation(PATH::wizard_move, 8);
			SetSpriteChangeState(false);
		}
		else if (GetState() == State::ATTACK)
		{
			if (GetSpriteChangeState() == true)
			{
				animation.ChangeAnimation(PATH::wizard_attack, 5);
				SetSpriteChangeState(false);
			}
		}
	}
}

bool Object::isCollideWith(Object& object) noexcept
{
	return !(max.x < object.min.x || object.max.x < min.x || max.y < object.min.y || object.max.y < min.y);
}

bool Object::isObjectInAttackRange(Object& object) noexcept
{
	return !(max.x + attackRange.x < object.min.x || object.max.x < min.x - attackRange.x || max.y + attackRange.y < object.min.y || object.max.y < min.y - attackRange.y);
}


bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width / 2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}