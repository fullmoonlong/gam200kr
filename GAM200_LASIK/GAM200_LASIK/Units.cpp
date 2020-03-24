/**************************************************************************************
 *	File Name        : Units.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : JeongHak Kim
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Units.hpp"
#include "AttackComponent.h"
#include "DataReader.hpp"
#include "UnitStateComponent.hpp"

void Unit::Initialize(const char* name) noexcept {
	AddComponent<BaseUnitState>();
	AddComponent<BaseObjectAttackComponent>();
	GetComponent<BaseUnitState>()->SetState(WALK);
	DataReader::ReadData(name, this);
}
