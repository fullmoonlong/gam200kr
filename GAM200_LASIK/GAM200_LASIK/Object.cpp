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
, min(rhs.min), max(rhs.max), speed(rhs.speed),objectName(rhs.objectName), position(rhs.position), size(rhs.size), componetList(rhs.componetList)
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
	this->GetComponent<UnitState>()->healthBar.Initialize(transform.GetTranslation(), this->GetComponent<UnitState>()->GetHealth());
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
		this->GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	}
	else if (unitdata == "Enemy")
	{
		this->GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	}
	else if (unitdata == "ProjectilesPlayer")
	{
		this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	}
	else if (unitdata == "ProjectilesEnemy")
	{
		this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	}

	data.GetString(&unitdata);
	SetName(unitdata);

	transform.SetTranslation(position);
	float half_width = size.x / 2;
	float half_height = size.y / 2;
	min = { position.x - half_width, position.y - half_height };
	max = { position.x + half_width, position.y + half_height };
	transform.SetScale({ size.x, size.y });

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());

	AddComponent<ObjectAttackComponent>();
}

void Object::Update(float dt) noexcept
{
	if (this->GetComponent<UnitState>()->GetState() == State::WALK)
	{
		float decision_x = speed.x * dt;
		float decision_y = speed.y * dt;
		float dx = transform.GetTranslation().x + decision_x;
		float dy = transform.GetTranslation().y + decision_y;
		transform.SetTranslation({ dx, dy });
		position.x = dx;
		position.y = dy;
		float half_width = size.x / 2.f;
		float half_height = size.y / 2.f;
		min = { position.x - half_width, position.y - half_height };
		max = { position.x + half_width, position.y + half_height };
	}
	else
	{
		position.x = transform.GetTranslation().x;
		position.y = transform.GetTranslation().y;
		float half_width = size.x / 2.f;
		float half_height = size.y / 2.f;
		min = { position.x - half_width, position.y - half_height };
		max = { position.x + half_width, position.y + half_height };
	}
	this->GetComponent<UnitState>()->healthBar.Update(transform.GetTranslation(), this->GetComponent<UnitState>()->GetHealth());
	
	if (this->GetComponent<UnitState>()->GetHealth() <= 0 && (this->GetComponent<UnitState>()->GetType() == UnitType::Player || this->GetComponent<UnitState>()->GetType() == UnitType::Enemy))
	{
		auto objID = OBJECTFACTORY->GetObjecteList().find(this->objectID);
		if (this->GetComponent<UnitState>()->GetType() == UnitType::Player)
		{
			for (std::vector<Object*>::iterator it = GAMEMANAGER->PlayerUnits.begin(); it != GAMEMANAGER->PlayerUnits.end(); it++)
			{
				if (*it == this)
				{
					GAMEMANAGER->PlayerUnits.erase(it);
					GAMEMANAGER->PlayerAmount--;
					break;
				}
			}
		}
		else if (this->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
		{
			for (std::vector<Object*>::iterator it = GAMEMANAGER->EnemyUnits.begin(); it != GAMEMANAGER->EnemyUnits.end(); it++)
			{
				if (*it == this)
				{
					GAMEMANAGER->EnemyUnits.erase(it);
					GAMEMANAGER->EnemyAmount--;
					break;
				}
			}
		}
		OBJECTFACTORY->Destroy(this);
	}

	if (this->GetName() == "Knight")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.6f)
			{
				SOUNDMANAGER->PlaySound(0, 3);
				vec2<float> a = { transform.GetTranslation().x + 48.f, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Archer")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.7f)
			{
				SOUNDMANAGER->PlaySound(0, 2);
				vec2<float> a = transform.GetTranslation();
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Magician")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 2.4f)
			{
				SOUNDMANAGER->PlaySound(0, 1);
				vec2<float> a = transform.GetTranslation();
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Skeleton")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.6f)
			{
				SOUNDMANAGER->PlaySound(0, 3);
				vec2<float> a = { transform.GetTranslation().x - 48.f, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Lich")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 3.0f)
			{
				SOUNDMANAGER->PlaySound(0, 1);
				vec2<float> a = { transform.GetTranslation().x, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Golem")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 1.5f)
			{
				SOUNDMANAGER->PlaySound(0, 3);
				vec2<float> a = { transform.GetTranslation().x - 256.f, transform.GetTranslation().y - 128 };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				GAMEMANAGER->SpawnUnit(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
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
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_move);
			this->animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_attack);
			this->animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Archer")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_move);
			animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_attack);
			animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Magician")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_move);
			animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_attack);
			animation.ChangeAnimation(5, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Skeleton")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_move);
			this->animation.ChangeAnimation(4, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_attack);
			this->animation.ChangeAnimation(7, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Lich")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_move);
			this->animation.ChangeAnimation(8, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_attack);
			this->animation.ChangeAnimation(1, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Golem")
	{
		if (this->GetComponent<UnitState>()->GetState() == State::WALK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_move);
			this->animation.ChangeAnimation(4, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
		}
		else if (this->GetComponent<UnitState>()->GetState() == State::ATTACK && this->GetComponent<UnitState>()->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_attack);
			this->animation.ChangeAnimation(18, 1);
			this->GetComponent<UnitState>()->SetSpriteChangeState(false);
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
	return !(max.x + this->GetComponent<UnitState>()->GetAttackRange().x < object.min.x || object.max.x < min.x - this->GetComponent<UnitState>()->GetAttackRange().x || max.y + this->GetComponent<UnitState>()->GetAttackRange().y < object.min.y || object.max.y < min.y - this->GetComponent<UnitState>()->GetAttackRange().y);
}

bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width / 2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}