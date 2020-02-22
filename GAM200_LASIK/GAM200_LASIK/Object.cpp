/**************************************************************************************
 *	File Name        : Object.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : Jookyung Lee
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "Object.h"
#include "GameManager.h"
#include "ObjectFactory.h"
#include "ComponentTest.h"
#include "ObjectMaterial.h"
#include "FileLoadAndSave.hpp"
#include "UnitStateComponent.hpp"


Object::Object()
	: objectID(0), position(0) {}

Object::Object(const Object& rhs) : transform(rhs.transform), material(rhs.material), animation(rhs.animation)
, min(rhs.min), max(rhs.max), speed(rhs.speed),objectName(rhs.objectName), position(rhs.position), size(rhs.size), componentList(rhs.componentList)
{
	AddComponent<MaterialComponent>();
	GetComponent<MaterialComponent>()->material.shader = material.shader;
	GetComponent<MaterialComponent>()->material.vertices = material.vertices;

	AddComponent<UnitState>();
	GetComponent<UnitState>()->SetType(GetComponent<BaseUnitState>()->GetType());
	GetComponent<UnitState>()->SetState(GetComponent<BaseUnitState>()->GetState());
	GetComponent<UnitState>()->SetAttackRange(GetComponent<BaseUnitState>()->GetAttackRange());
	GetComponent<UnitState>()->SetAttackState(GetComponent<BaseUnitState>()->GetAttackState());
	GetComponent<UnitState>()->SetSpriteChangeState(GetComponent<BaseUnitState>()->GetSpriteChangeState());
	GetComponent<UnitState>()->SetHealth(GetComponent<BaseUnitState>()->GetHealth());
	GetComponent<UnitState>()->SetDamage(GetComponent<BaseUnitState>()->GetDamage());
	GetComponent<UnitState>()->SetInvincibilityState(GetComponent<BaseUnitState>()->GetInvincibilityState());
	GetComponent<UnitState>()->healthBar.material = GetComponent<BaseUnitState>()->healthBar.material;
	GetComponent<UnitState>()->healthBar.mesh = GetComponent<BaseUnitState>()->healthBar.mesh;
	GetComponent<UnitState>()->healthBar.transform = GetComponent<BaseUnitState>()->healthBar.transform;
	GetComponent<UnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<UnitState>()->GetHealth());

	if (GetName() != "Lair" && GetName() != "Tower")
	{
		if (GetComponent<UnitState>()->GetType() != UnitType::ProjectilesPlayer && GetComponent<UnitState>()->GetType() != UnitType::ProjectilesEnemy)
		{
			AddComponent<ObjectAttackComponent>();
			GetComponent<ObjectAttackComponent>()->SetUnit(this);
			GetComponent<ObjectAttackComponent>()->projectile = GetComponent<BaseObjectAttackComponent>()->projectile;
			GetComponent<ObjectAttackComponent>()->delayTime = GetComponent<BaseObjectAttackComponent>()->delayTime;
			GetComponent<ObjectAttackComponent>()->soundID = GetComponent<BaseObjectAttackComponent>()->soundID;
			GetComponent<ObjectAttackComponent>()->startPosition.x = GetComponent<BaseObjectAttackComponent>()->startPosition.x;
			GetComponent<ObjectAttackComponent>()->startPosition.y = GetComponent<BaseObjectAttackComponent>()->startPosition.y;
		}
	}
}

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
		GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	}
	else if (unitdata == "Enemy")
	{
		GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	}
	else if (unitdata == "ProjectilesPlayer")
	{
		GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	}
	else if (unitdata == "ProjectilesEnemy")
	{
		GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	}

	data.GetString(&unitdata);
	SetName(unitdata);

	transform.SetTranslation(position);
	const float half_width = size.x / 2;
	const float half_height = size.y / 2;
	min = { position.x - half_width, position.y - half_height };
	max = { position.x + half_width, position.y + half_height };
	transform.SetScale({ size.x, size.y });

	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());

	AddComponent<ObjectAttackComponent>();
}

void Object::Update(float dt) noexcept
{
	if (GetComponent<UnitState>()->GetState() == State::WALK) {
		const vec2<float> changedPosition = transform.GetTranslation() + speed * dt;
		transform.SetTranslation(changedPosition);
		position = changedPosition;
		const float halfWidth = size.x / 2.f;
		const float halfHeight = size.y / 2.f;
		min = { position.x - halfWidth, position.y - halfHeight };
		max = { position.x + halfWidth, position.y + halfHeight };
	}
}

Object* Object::Clone() const
{
	return new Object(*this);
}

void Object::ChangeUnitAnimation()
{
	if (GetName() == "Knight")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_move);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_attack);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Archer")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_move);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_attack);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Magician")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_move);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_attack);
			animation.ChangeAnimation(5, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Skeleton")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_move);
			animation.ChangeAnimation(4, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_attack);
			animation.ChangeAnimation(7, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Lich")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_move);
			animation.ChangeAnimation(8, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_attack);
			animation.ChangeAnimation(1, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Golem")
	{
		if (GetComponent<UnitState>()->GetState() == State::WALK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_move);
			animation.ChangeAnimation(4, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (GetComponent<UnitState>()->GetState() == State::ATTACK && GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_attack);
			animation.ChangeAnimation(18, 1);
			GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else
	{
		GetComponent<MaterialComponent>()->material.texture = material.texture;
	}
}

bool Object::isCollideWith(Object& object) noexcept
{
	return !(max.x < object.min.x || object.max.x < min.x || max.y < object.min.y || object.max.y < min.y);
}

bool Object::isObjectInAttackRange(Object& object) noexcept
{
	return !(max.x + GetComponent<UnitState>()->GetAttackRange().x < object.min.x || object.max.x < min.x - GetComponent<UnitState>()->GetAttackRange().x || max.y + GetComponent<UnitState>()->GetAttackRange().y < object.min.y || object.max.y < min.y - GetComponent<UnitState>()->GetAttackRange().y);
}

bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width / 2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}