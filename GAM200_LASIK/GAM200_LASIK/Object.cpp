/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*			JeongHak Kim	junghak.kim@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/

#include "Object.h"
#include "FileLoadAndSave.hpp"
#include "ObjectFactory.h"
#include <iostream>
#include "ComponentTest.h"
#include "ObjectMaterial.h"


Object::Object()
	: objectID(0), position(0) {}

Object::Object(const Object& rhs) : transform(rhs.transform), material(rhs.material), animation(rhs.animation)
, min(rhs.min), max(rhs.max), health(rhs.health), damage(rhs.damage), healthBar(rhs.healthBar), attackRange(rhs.attackRange)
, speed(rhs.speed), objectName(rhs.objectName), position(rhs.position), size(rhs.size), unitType(rhs.unitType)
, state(rhs.state), componetList(rhs.componetList)
{
	AddComponent<MaterialComponent>();
	GetComponent<MaterialComponent>()->material.shader = material.shader;
	GetComponent<MaterialComponent>()->material.vertices = material.vertices;
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

	healthBar.Initialize(transform.GetTranslation(), GetHealth());

	AddComponent<ObjectAttackComponent>();
}

void Object::Update(float dt) noexcept
{
	if (state == State::WALK)
	{
		float decision_x = speed.x * dt;
		float decision_y = speed.y * dt;
		float dx = transform.GetTranslation().x + decision_x;
		float dy = transform.GetTranslation().y + decision_y;
		transform.SetTranslation({ dx, dy });
		position.x = dx;
		position.y = dy;
		float half_width = size.x / 2;
		float half_height = size.y / 2;
		min = { position.x - half_width, position.y - half_height };
		max = { position.x + half_width, position.y + half_height };
	}

	else
	{
		position.x = transform.GetTranslation().x;
		position.y = transform.GetTranslation().y;
		float half_width = size.x / 2;
		float half_height = size.y / 2;
		min = { position.x - half_width, position.y - half_height };
		max = { position.x + half_width, position.y + half_height };
	}
	healthBar.Update(transform.GetTranslation(), GetHealth());
	if (health <= 0 && (unitType == UnitType::Player || unitType == UnitType::Enemy))
	{
		OBJECTFACTORY->Destroy(this);
	}

	if (this->GetName() == "Knight")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.6f)
			{
				SOUNDMANAGER->PlaySound(0, 4);
				vec2<float> a = { transform.GetTranslation().x + 48.f, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Archer")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.7f)
			{
				SOUNDMANAGER->PlaySound(0, 3);
				vec2<float> a = transform.GetTranslation();
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Magician")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 2.4f)
			{
				SOUNDMANAGER->PlaySound(0, 2);
				vec2<float> a = transform.GetTranslation();
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Skeleton")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 0.6f)
			{
				SOUNDMANAGER->PlaySound(0, 4);
				vec2<float> a = { transform.GetTranslation().x - 48.f, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Lich")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 3.0f)
			{
				SOUNDMANAGER->PlaySound(0, 2);
				vec2<float> a = { transform.GetTranslation().x, transform.GetTranslation().y };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "Golem")
	{
		if (this->GetState() == State::ATTACK)
		{
			this->GetComponent<ObjectAttackComponent>()->time += dt;
			if (this->GetComponent<ObjectAttackComponent>()->time > 1.5f)
			{
				SOUNDMANAGER->PlaySound(0, 4);
				vec2<float> a = { transform.GetTranslation().x - 256.f, transform.GetTranslation().y - 128 };
				this->GetComponent<ObjectAttackComponent>()->attack->transform.SetTranslation(a);

				OBJECTFACTORY->CopyObject(GetComponent<ObjectAttackComponent>()->attack);
				this->GetComponent<ObjectAttackComponent>()->time = 0;
			}
		}
	}
	else if (this->GetName() == "swordAttack" || this->GetName() == "enemyAttack")
	{
		this->GetComponent<ObjectAttackComponent>()->time += dt;
		if (this->GetComponent<ObjectAttackComponent>()->time > 0.4f)
		{
			OBJECTFACTORY->Destroy(this);
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
		if (this->GetState() == State::WALK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_move);
			this->animation.ChangeAnimation(8, 1);
			this->SetSpriteChangeState(false);
		}
		else if (this->GetState() == State::ATTACK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::knight_attack);
			this->animation.ChangeAnimation(8, 1);
			this->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Archer")
	{
		if (GetState() == State::WALK && GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_move);
			animation.ChangeAnimation(8, 1);
			SetSpriteChangeState(false);
		}
		else if (GetState() == State::ATTACK && GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::archer_attack);
			animation.ChangeAnimation(8, 1);
			SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Magician")
	{
		if (GetState() == State::WALK && GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_move);
			animation.ChangeAnimation(8, 1);
			SetSpriteChangeState(false);
		}
		else if (GetState() == State::ATTACK && GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::magician_attack);
			animation.ChangeAnimation(5, 1);
			SetSpriteChangeState(false);
		}
	}
	else if (GetName() == "Skeleton")
	{
		if (this->GetState() == State::WALK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_move);
			this->animation.ChangeAnimation(4, 1);
			this->SetSpriteChangeState(false);
		}
		else if (this->GetState() == State::ATTACK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::skeleton_attack);
			this->animation.ChangeAnimation(7, 1);
			this->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Lich")
	{
		if (this->GetState() == State::WALK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_move);
			this->animation.ChangeAnimation(8, 1);
			this->SetSpriteChangeState(false);
		}
		else if (this->GetState() == State::ATTACK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::lich_attack);
			this->animation.ChangeAnimation(1, 1);
			this->SetSpriteChangeState(false);
		}

	}
	else if (GetName() == "Golem")
	{
		if (this->GetState() == State::WALK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_move);
			this->animation.ChangeAnimation(4, 1);
			this->SetSpriteChangeState(false);
		}
		else if (this->GetState() == State::ATTACK && this->GetSpriteChangeState() == true)
		{
			GetComponent<MaterialComponent>()->material.texture.LoadTextureFrom(PATH::golem_attack);
			this->animation.ChangeAnimation(18, 1);
			this->SetSpriteChangeState(false);
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
	return !(max.x + attackRange.x < object.min.x || object.max.x < min.x - attackRange.x || max.y + attackRange.y < object.min.y || object.max.y < min.y - attackRange.y);
}

bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width / 2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}