/**************************************************************************************
*	File Name        : ObjectFactory.cpp
*	Project Name     : Keyboard Warriors
*	Primary Author   : Doyeong Yi
*	Secondary Author :
*	Copyright Information :
*    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
**************************************************************************************/

#include "Object.h"
#include <iostream>
#include <stdlib.h>
#include "Sound.hpp"
#include "ObjectFactory.h"
#include "UnitStateComponent.hpp"

extern ObjectFactory* OBJECTFACTORY = nullptr;

ObjectFactory::ObjectFactory()
{
	std::cout << "ObjectFactory Add Successful" << std::endl;
	OBJECTFACTORY = this;
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::Update(float /*dt*/)
{
	for (auto object : objectsToBeDeleted)
	{
		if (object == nullptr)
		{
			continue;
		}
		auto objID = objectIDMap.find(object->objectID);
		if (object->GetComponent<UnitState>()->GetType() == UnitType::Player)
		{
			for (std::vector<Object*>::iterator it = PlayerUnits.begin(); it != PlayerUnits.end(); it++)
			{
				if (*it == object)
				{
					PlayerUnits.erase(it);
					PlayerAmount--;
					break;
				}
			}
		}
		else if (object->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
		{
			for (std::vector<Object*>::iterator it = EnemyUnits.begin(); it != EnemyUnits.end(); it++)
			{
				if (*it == object)
				{
					EnemyUnits.erase(it);
					EnemyAmount--;
					break;
				}
			}
		}

		if (objID != objectIDMap.end())
		{
			delete object;
			objectIDMap.erase(objID);
		}
	}
	objectsToBeDeleted.clear();
	CheckCollision();
	CheckAttackState();
}

void ObjectFactory::Destroy(Object* object)
{
	objectsToBeDeleted.push_back(object);
}

void ObjectFactory::GiveObjectID(Object* object)
{
	object->objectID = lastObjectID;
	objectIDMap[lastObjectID] = object;
	lastObjectID++;
}

int ObjectFactory::GetObjectID(int id)
{
	return objectIDMap[id]->objectID;
}

Object* ObjectFactory::CreateEmptyObject()
{
	Object* object = new Object();
	GiveObjectID(object);
	return object;
}

void ObjectFactory::DestroyAllObjects()
{
	lastObjectID = 0;
	PlayerAmount = 0;
	EnemyAmount = 0;
	for (auto object : objectIDMap)
	{
		delete object.second;
	}
	objectIDMap.clear();
}

Object* ObjectFactory::FindObjectwithName(const std::string& name)
{
	for (auto object : objectIDMap)
	{
		if (object.second->objectName == name)
			return object.second;
	}
	return nullptr;
}

Object* ObjectFactory::FindObjectwithID(ObjectID id)
{
	for (auto object : objectIDMap)
	{
		if (object.second->objectID == id)
			return object.second;
	}
	return nullptr;
}

void ObjectFactory::CopyObject(Object* object)
{
	Object* newObject = object->Clone();

	newObject->objectID = lastObjectID;
	objectIDMap.emplace(lastObjectID, newObject);
	lastObjectID++;
	newObject->GetComponent<UnitState>()->SetSpriteChangeState(true);
	if (newObject->GetComponent<UnitState>()->GetType() == UnitType::Player)
	{
		PlayerUnits.push_back(newObject);
		PlayerAmount++;
	}
	else if (newObject->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
	{
		EnemyUnits.push_back(newObject);
		EnemyAmount++;
	}
}

void ObjectFactory::CheckCollision()
{
	for (auto object : objectIDMap)
	{
		for (auto object1 : objectIDMap)
		{
			if (object.second->isCollideWith(*object1.second) && object.second->GetComponent<UnitState>()->GetType() == UnitType::ProjectilesPlayer && object1.second->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
			{
				if (object1.second->GetComponent<UnitState>()->GetInvincibilityState() == false)
				{
					object1.second->GetComponent<UnitState>()->SetHealth(object1.second->GetComponent<UnitState>()->GetHealth() - object.second->GetComponent<UnitState>()->GetDamage());

				}					
				OBJECTFACTORY->Destroy(object.second);
			}
			if (object.second->isCollideWith(*object1.second) && object.second->GetComponent<UnitState>()->GetType() == UnitType::ProjectilesEnemy && object1.second->GetComponent<UnitState>()->GetType() == UnitType::Player)
			{
				if (object1.second->GetComponent<UnitState>()->GetInvincibilityState() == false)
				{
					object1.second->GetComponent<UnitState>()->SetHealth(object1.second->GetComponent<UnitState>()->GetHealth() - object.second->GetComponent<UnitState>()->GetDamage());
				}
				OBJECTFACTORY->Destroy(object.second);
			}
		}
	}
	for (auto player : PlayerUnits)
	{
		bool pl = false;
		bool en = false;
		for (auto enemy : EnemyUnits)
		{
			if (player->isObjectInAttackRange(*enemy))
			{
				player->GetComponent<UnitState>()->SetState(State::ATTACK);
				pl = true;
				if (player->GetComponent<UnitState>()->GetAttackState() == false)
				{
					player->GetComponent<UnitState>()->SetAttackState(true);
					enemy->GetComponent<UnitState>()->SetAttackState(true);
					player->GetComponent<UnitState>()->SetSpriteChangeState(true);
				}
			}

			if (enemy->isObjectInAttackRange(*player))
			{
				enemy->GetComponent<UnitState>()->SetState(State::ATTACK);
				en = true;
				if (enemy->GetComponent<UnitState>()->GetAttackState() == false)
				{
					player->GetComponent<UnitState>()->SetAttackState(true);
					enemy->GetComponent<UnitState>()->SetAttackState(true);
					enemy->GetComponent<UnitState>()->SetSpriteChangeState(true);
				}
			}
		}
	}
}

void ObjectFactory::CheckAttackState()
{
	int playerTotalNotWhileAttack = 0;
	int enemyTotalNotWhileAttack = 0;


	for (auto obj : objectIDMap)
	{
		if (obj.second == nullptr)
		{
			continue;
		}
		if (obj.second->GetComponent<UnitState>()->GetAttackState() == false && obj.second->GetComponent<UnitState>()->GetType() == UnitType::Player)
		{
			playerTotalNotWhileAttack++;
		}
		else if (obj.second->GetComponent<UnitState>()->GetAttackState() == false && obj.second->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
		{
			enemyTotalNotWhileAttack++;
		}
	}

	for (auto enemy : EnemyUnits)
	{
		if ((playerTotalNotWhileAttack == static_cast<int>(PlayerUnits.size())) && enemy->GetComponent<UnitState>()->GetAttackState() == true)
		{
			if (enemy == nullptr)
			{
				continue;
			}
			enemy->GetComponent<UnitState>()->SetSpriteChangeState(true);
			enemy->GetComponent<UnitState>()->SetAttackState(false);
			enemy->GetComponent<UnitState>()->SetState(State::WALK);
		}
	}
	for (auto player : PlayerUnits)
	{
		if ((enemyTotalNotWhileAttack == static_cast<int>(EnemyUnits.size())) && player->GetComponent<UnitState>()->GetAttackState() == true)
		{
			if (player == nullptr)
			{
				continue;
			}
			player->GetComponent<UnitState>()->SetSpriteChangeState(true);
			player->GetComponent<UnitState>()->SetAttackState(false);
			player->GetComponent<UnitState>()->SetState(State::WALK);
		}
	}
}

void ObjectFactory::DamageTest(int time)
{
	if (time % 2 == 0)
	{
		for (auto object : objectIDMap)
		{
			for (auto object1 : objectIDMap)
			{
				if (object != object1)
				{
					if (object.second->GetComponent<UnitState>()->GetType() != object1.second->GetComponent<UnitState>()->GetType())
					{
						if (object.second->isObjectInAttackRange(*object1.second))
						{
							if (object.second->GetComponent<UnitState>()->GetState() == State::ATTACK)
							{
								object1.second->GetComponent<UnitState>()->SetHealth(object1.second->GetComponent<UnitState>()->GetHealth() - object.second->GetComponent<UnitState>()->GetDamage());
							}
						}
					}
				}
			}
		}
	}
}
