/**************************************************************************************
 *	File Name        : EnemyUnits.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include <vec2.hpp>
#include "Graphic.h"
#include "EnemyUnits.hpp"
#include "ObjectMaterial.h"
#include "ComponentAttack.h"
#include "ComponentSprite.h"
#include "FileLoadAndSave.hpp"
#include "UnitStateComponent.hpp"

Skeleton::~Skeleton()
{
}

void Skeleton::UnitInitialize(const char* name)
{
	material.shader = GRAPHIC->shader;
	material.vertices.InitializeWithMeshAndLayout(GRAPHIC->mesh, GRAPHIC->layout);
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetSkeletionHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetSkeletionDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });

	File data;
	vec2<float> firstPosition;
	vec2<float> firstSize;

	data.Open(name);
	data.GetFloat(&firstPosition.x);
	data.GetFloat(&firstPosition.y);
	data.GetFloat(&firstSize.x);
	data.GetFloat(&firstSize.y);
	data.GetFloat(&this->speed.x);

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
	this->SetName(unitdata);

	this->SetPosition(firstPosition);
	this->SetSize(firstSize);

	this->transform.SetTranslation(firstPosition);
	float half_width = firstSize.x / 2;
	float half_height = firstSize.y / 2;
	this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	this->transform.SetScale({ firstSize.x, firstSize.y });

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(this->transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());

	this->AddComponent<BaseObjectAttackComponent>();

	this->AddComponent<SpriteComponent>();
	this->GetComponent<SpriteComponent>()->moveSpritePath = PATH::skeleton_move;
	this->GetComponent<SpriteComponent>()->attackSpritePath = PATH::skeleton_attack;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.x = 4;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.y = 1;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.x = 7;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.y = 1;
}

Lich::~Lich()
{
}

void Lich::UnitInitialize(const char* name)
{
	material.shader = GRAPHIC->shader;
	material.vertices.InitializeWithMeshAndLayout(GRAPHIC->mesh, GRAPHIC->layout);
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetLichHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetLichDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange(this->GetLichAttackRange());

	File data;
	vec2<float> firstPosition;
	vec2<float> firstSize;

	data.Open(name);
	data.GetFloat(&firstPosition.x);
	data.GetFloat(&firstPosition.y);
	data.GetFloat(&firstSize.x);
	data.GetFloat(&firstSize.y);
	data.GetFloat(&this->speed.x);

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
	this->SetName(unitdata);

	this->SetPosition(firstPosition);
	this->SetSize(firstSize);

	this->transform.SetTranslation(firstPosition);
	float half_width = firstSize.x / 2;
	float half_height = firstSize.y / 2;
	this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	this->transform.SetScale({ firstSize.x, firstSize.y });

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(this->transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());

	this->AddComponent<BaseObjectAttackComponent>();

	this->AddComponent<SpriteComponent>();
	this->GetComponent<SpriteComponent>()->moveSpritePath = PATH::lich_move;
	this->GetComponent<SpriteComponent>()->attackSpritePath = PATH::lich_attack;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.x = 8;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.y = 1;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.x = 1;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.y = 1;
}

void Golem::UnitInitialize(const char* name)
{
	material.shader = GRAPHIC->shader;
	material.vertices.InitializeWithMeshAndLayout(GRAPHIC->mesh, GRAPHIC->layout);
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetGolemHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetGolemHealth());
	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });

	File data;
	vec2<float> firstPosition;
	vec2<float> firstSize;

	data.Open(name);
	data.GetFloat(&firstPosition.x);
	data.GetFloat(&firstPosition.y);
	data.GetFloat(&firstSize.x);
	data.GetFloat(&firstSize.y);
	data.GetFloat(&this->speed.x);

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
	this->SetName(unitdata);

	this->SetPosition(firstPosition);
	this->SetSize(firstSize);

	this->transform.SetTranslation(firstPosition);
	float half_width = firstSize.x / 2;
	float half_height = firstSize.y / 2;
	this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	this->transform.SetScale({ firstSize.x, firstSize.y });

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(this->transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());

	this->AddComponent<BaseObjectAttackComponent>();

	this->AddComponent<SpriteComponent>();
	this->GetComponent<SpriteComponent>()->moveSpritePath = PATH::golem_move;
	this->GetComponent<SpriteComponent>()->attackSpritePath = PATH::golem_attack;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.x = 4;
	this->GetComponent<SpriteComponent>()->moveSpriteColumnRow.y = 1;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.x = 18;
	this->GetComponent<SpriteComponent>()->attackSpriteColumnRow.y = 1;
}
