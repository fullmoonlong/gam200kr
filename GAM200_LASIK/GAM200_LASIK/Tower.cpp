/**************************************************************************************
 *	File Name        : Tower.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Tower.h"
#include "ComponentTower.h"
#include "FileLoadAndSave.hpp"
#include "DataReader.hpp"

void Tower::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(towerHealth);
	this->GetComponent<BaseUnitState>()->SetDamage(towerDamage);

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

	DataReader::ReadData(name, this);

	transform.SetTranslation(position);
	transform.SetScale(size);
	
	const float halfWidth  = size.x / 2;
	const float halfHeight = size.y / 2;
	min.x = position.x - halfWidth;
	min.y = position.y - halfHeight;
	max.x = position.x + halfWidth;
	max.y = position.y + halfHeight;

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(this->transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());
}

void Lair::UnitInitialize(const char* name)
{
	this->AddComponent<BaseUnitState>();
	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
	this->GetComponent<BaseUnitState>()->SetHealth(lairHealth);
	this->GetComponent<BaseUnitState>()->SetDamage(lairDamage);

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

	transform.SetTranslation(position);
	transform.SetScale(size);

	const float halfWidth  = size.x / 2;
	const float halfHeight = size.y / 2;
	min.x = position.x - halfWidth;
	min.y = position.y - halfHeight;
	max.x = position.x + halfWidth;
	max.y = position.y + halfHeight;

	this->GetComponent<BaseUnitState>()->healthBar.Initialize(this->transform.GetTranslation(), this->GetComponent<BaseUnitState>()->GetHealth());

	this->AddComponent<LairComponent>();
}
