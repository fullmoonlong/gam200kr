/**************************************************************************************
 *	File Name        : EnemyUnits.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include <vec2.hpp>
#include "EnemyUnits.hpp"
#include "ComponentTest.h"
#include "DataReader.hpp"
#include "FileLoadAndSave.hpp"
#include "UnitStateComponent.hpp"

void Skeleton::UnitInitialize(const char* name) 
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetSkeletionHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetSkeletionDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });

	//File data;
	//vec2<float> firstPosition;
	//vec2<float> firstSize;

	//data.Open(name);
	//data.GetFloat(&firstPosition.x);
	//data.GetFloat(&firstPosition.y);
	//data.GetFloat(&firstSize.x);
	//data.GetFloat(&firstSize.y);
	//data.GetFloat(&this->speed.x);

	//std::string unitdata;
	//data.GetString(&unitdata);

	//if (unitdata == "Player")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	//}
	//else if (unitdata == "Enemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	//}
	//else if (unitdata == "ProjectilesPlayer")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	//}
	//else if (unitdata == "ProjectilesEnemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	//}

	//data.GetString(&unitdata);
	//this->SetName(unitdata);

	//this->SetPosition(firstPosition);
	//this->SetSize(firstSize);

	//this->transform.SetTranslation(firstPosition);
	//float half_width = firstSize.x / 2;
	//float half_height = firstSize.y / 2;
	//this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	//this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	//this->transform.SetScale({ firstSize.x, firstSize.y });

	DataReader::ReadData(name, this);
	
	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());

	AddComponent<BaseObjectAttackComponent>();
}

void Lich::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetLichHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetLichDamage());
	this->GetComponent<BaseUnitState>()->SetAttackRange(this->GetLichAttackRange());

	//File data;
	//vec2<float> firstPosition;
	//vec2<float> firstSize;

	//data.Open(name);
	//data.GetFloat(&firstPosition.x);
	//data.GetFloat(&firstPosition.y);
	//data.GetFloat(&firstSize.x);
	//data.GetFloat(&firstSize.y);
	//data.GetFloat(&this->speed.x);

	//std::string unitdata;
	//data.GetString(&unitdata);

	//if (unitdata == "Player")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	//}
	//else if (unitdata == "Enemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	//}
	//else if (unitdata == "ProjectilesPlayer")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	//}
	//else if (unitdata == "ProjectilesEnemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	//}

	//data.GetString(&unitdata);
	//this->SetName(unitdata);

	//this->SetPosition(firstPosition);
	//this->SetSize(firstSize);

	//this->transform.SetTranslation(firstPosition);
	//float half_width = firstSize.x / 2;
	//float half_height = firstSize.y / 2;
	//this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	//this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	//this->transform.SetScale({ firstSize.x, firstSize.y });

	DataReader::ReadData(name, this);
	
	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());

	AddComponent<BaseObjectAttackComponent>();
}

void Golem::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(this->GetGolemHealth());
	this->GetComponent<BaseUnitState>()->SetDamage(this->GetGolemHealth());
	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });

	//File data;
	//vec2<float> firstPosition;
	//vec2<float> firstSize;

	//data.Open(name);
	//data.GetFloat(&firstPosition.x);
	//data.GetFloat(&firstPosition.y);
	//data.GetFloat(&firstSize.x);
	//data.GetFloat(&firstSize.y);
	//data.GetFloat(&this->speed.x);

	//std::string unitdata;
	//data.GetString(&unitdata);

	//if (unitdata == "Player")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	//}
	//else if (unitdata == "Enemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	//}
	//else if (unitdata == "ProjectilesPlayer")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	//}
	//else if (unitdata == "ProjectilesEnemy")
	//{
	//	this->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	//}

	//data.GetString(&unitdata);
	//this->SetName(unitdata);

	//this->SetPosition(firstPosition);
	//this->SetSize(firstSize);

	//this->transform.SetTranslation(firstPosition);
	//float half_width = firstSize.x / 2;
	//float half_height = firstSize.y / 2;
	//this->min = { this->GetXposition() - half_width, this->GetYposition() - half_height };
	//this->max = { this->GetXposition() + half_width, this->GetYposition() + half_height };
	//this->transform.SetScale({ firstSize.x, firstSize.y });

	DataReader::ReadData(name, this);
	
	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());

	AddComponent<BaseObjectAttackComponent>();
}
