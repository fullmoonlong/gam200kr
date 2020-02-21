/**************************************************************************************
 *	File Name        : Units.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include <vec2.hpp>
#include "Units.hpp"
#include "ComponentTest.h"
#include "FileLoadAndSave.hpp"
#include "UnitStateComponent.hpp"

void Knight::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetKnightHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetKnightDamage());

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
}

void Archer::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetArcherHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetArcherDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange(this->GetArcherAttackRange());

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
}

void Magician::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetMagicianHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetMagicianDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange(this->GetMagicianAttackRange());

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
}
