/**************************************************************************************
 *	File Name        : BaseInitialize.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#pragma once
#include "Object.h"

#pragma once
#include <vec2.hpp>
#include "ComponentTest.h"
#include "DataReader.hpp"
#include "FileLoadAndSave.hpp"
#include "UnitStateComponent.hpp"

inline void BaseInitialize(const char* name, Object* object)
{
	//File data;
	//vec2<float> position;
	//vec2<float> size;

	//data.Open(name);
	//data.GetFloat(&position.x);
	//data.GetFloat(&position.y);
	//data.GetFloat(&size.x);
	//data.GetFloat(&size.y);
	//data.GetFloat(&object->speed.x);

	//std::string unitdata;
	//data.GetString(&unitdata);

	//if (unitdata == "Player")
	//{
	//	object->GetComponent<BaseUnitState>()->SetType(UnitType::Player);
	//}
	//else if (unitdata == "Enemy")
	//{
	//	object->GetComponent<BaseUnitState>()->SetType(UnitType::Enemy);
	//}
	//else if (unitdata == "ProjectilesPlayer")
	//{
	//	object->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesPlayer);
	//}
	//else if (unitdata == "ProjectilesEnemy")
	//{
	//	object->GetComponent<BaseUnitState>()->SetType(UnitType::ProjectilesEnemy);
	//}

	//data.GetString(&unitdata);
	//object->SetName(unitdata);

	//object->SetPosition(position);
	//object->SetSize(size);

	//object->transform.SetTranslation(position);
	//float half_width = size.x / 2;
	//float half_height = size.y / 2;
	//object->min = { object->GetXposition() - half_width, object->GetYposition() - half_height };
	//object->max = { object->GetXposition() + half_width, object->GetYposition() + half_height };
	//object->transform.SetScale({ size.x, size.y });

	DataReader::ReadData(name, object);

	object->GetComponent<BaseUnitState>()->healthBar.Initialize(object->transform.GetTranslation(), object->GetComponent<BaseUnitState>()->GetHealth());

	object->AddComponent<ObjectAttackComponent>();
}