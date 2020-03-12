/**************************************************************************************
 *	File Name        : EnemyUnits.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

//#include "EnemyUnits.hpp"
//#include "ComponentTest.h"
//#include "DataReader.hpp"
//#include "FileLoadAndSave.hpp"
//#include "UnitStateComponent.hpp"
//
//void Skeleton::UnitInitialize(const char* name) 
//{
//	this->AddComponent<BaseUnitState>();
//	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
//	this->GetComponent<BaseUnitState>()->SetHealth(this->GetSkeletionHealth());
//	this->GetComponent<BaseUnitState>()->SetDamage(this->GetSkeletionDamage());
//	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });
//
//	DataReader::ReadData(name, this);
//	
//	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());
//
//	AddComponent<BaseObjectAttackComponent>();
//}
//
//void Lich::UnitInitialize(const char* name)
//{
//	this->AddComponent<BaseUnitState>();
//	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
//	this->GetComponent<BaseUnitState>()->SetHealth(this->GetLichHealth());
//	this->GetComponent<BaseUnitState>()->SetDamage(this->GetLichDamage());
//	this->GetComponent<BaseUnitState>()->SetAttackRange(this->GetLichAttackRange());
//	
//	DataReader::ReadData(name, this);
//	
//	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());
//
//	AddComponent<BaseObjectAttackComponent>();
//}
//
//void Golem::UnitInitialize(const char* name)
//{
//	this->AddComponent<BaseUnitState>();
//	this->GetComponent<BaseUnitState>()->SetState(State::WALK);
//	this->GetComponent<BaseUnitState>()->SetHealth(this->GetGolemHealth());
//	this->GetComponent<BaseUnitState>()->SetDamage(this->GetGolemHealth());
//	this->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });
//
//	DataReader::ReadData(name, this);
//	
//	GetComponent<BaseUnitState>()->healthBar.Initialize(transform.GetTranslation(), GetComponent<BaseUnitState>()->GetHealth());
//
//	AddComponent<BaseObjectAttackComponent>();
//}
