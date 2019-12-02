/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/26
*/
#include "Sound.hpp"
#include "ObjectFactory.h"
#include "Object.h"
#include <iostream>
#include <stdlib.h>

extern ObjectFactory* OBJECTFACTORY = nullptr;

ObjectFactory::ObjectFactory()
{
	std::cout << "ObjectFactory Add Successful" << std::endl;
	OBJECTFACTORY = this;
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::Update()
{
	for (auto object : objectsToBeDeleted)
	{
		if (object == nullptr)
		{
			continue;
		}
		auto objID = objectIDMap.find(object->objectID);
		if (object->GetType() == UnitType::Player)
		{
			for (std::vector<Object*>::iterator it = PlayerUnits.begin(); it != PlayerUnits.end(); it++)
			{
				if (*it == object)
				{
					PlayerUnits.erase(it);
					break;
				}
			}
			playerAmounts--;
		}
		else if (object->GetType() == UnitType::Enemy)
		{
			for (std::vector<Object*>::iterator it = EnemyUnits.begin(); it != EnemyUnits.end(); it++)
			{
				if (*it == object)
				{
					EnemyUnits.erase(it);
					break;
				}
			}
			enemyAmounts--;
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
	playerAmounts = 0;
	enemyAmounts = 0;

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

	//GiveObjectID(newObject);
	newObject->objectID = lastObjectID;
	objectIDMap.emplace(lastObjectID, newObject);
	lastObjectID++;
	if (newObject->GetType() == UnitType::Player)
	{
		playerAmounts++;
		PlayerUnits.push_back(newObject);
	}
	else if (newObject->GetType() == UnitType::Enemy)
	{
		enemyAmounts++;
		EnemyUnits.push_back(newObject);
	}
}

void ObjectFactory::CheckCollision()
{
	for (auto object : objectIDMap)
	{
		for (auto object1 : objectIDMap)
		{
			if (object != object1)
			{
				if (object.second->GetType() != object1.second->GetType())
				{
					if (object.second->isObjectInAttackRange(*object1.second))
					{
						if (object.second->GetState() != State::ATTACK)
						{
							if (object.second->GetType() == UnitType::Player || object.second->GetType() == UnitType::Enemy)
							{
								object.second->SetState(State::ATTACK);
								object.second->SetAttackState(true);
								object.second->SetSpriteChangeState(true);
							}
						}
					}
					if (object.second->isCollideWith(*object1.second) && object.second->GetType() == UnitType::ProjectilesPlayer && object1.second->GetType() == UnitType::Enemy)
					{
						object1.second->SetHealth(object1.second->GetHealth() - object.second->GetDamage());
						OBJECTFACTORY->Destroy(object.second);
					}
					if (object.second->isCollideWith(*object1.second) && object.second->GetType() == UnitType::ProjectilesEnemy && object1.second->GetType() == UnitType::Player)
					{
						object1.second->SetHealth(object1.second->GetHealth() - object.second->GetDamage());
						OBJECTFACTORY->Destroy(object.second);
					}
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
		if (obj.second->GetAttackState() == false && obj.second->GetType() == UnitType::Player)
		{
			playerTotalNotWhileAttack++;
		}
		else if (obj.second->GetAttackState() == false && obj.second->GetType() == UnitType::Enemy)
		{
			enemyTotalNotWhileAttack++;
		}
	}

	for (auto obj : objectIDMap)
	{
		if (obj.second->GetType() == UnitType::Enemy)
		{
			if ((playerTotalNotWhileAttack == playerAmounts) && obj.second->GetAttackState() == true)
			{
				if (obj.second == nullptr)
				{
					continue;
				}
				obj.second->SetSpriteChangeState(true);
				obj.second->SetAttackState(false);
				obj.second->SetState(State::WALK);
			}
		}
		else if (obj.second->GetType() == UnitType::Player)
		{
			if ((enemyTotalNotWhileAttack == enemyAmounts) && obj.second->GetAttackState() == true)
			{
				if (obj.second == nullptr)
				{
					continue;
				}
				obj.second->SetSpriteChangeState(true);
				obj.second->SetAttackState(false);
				obj.second->SetState(State::WALK);
			}
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
					if (object.second->GetType() != object1.second->GetType())
					{
						if (object.second->isObjectInAttackRange(*object1.second))
						{
							if (object.second->GetState() == State::ATTACK)
							{
								object1.second->SetHealth(object1.second->GetHealth() - object.second->GetDamage());
							}
						}
					}
				}
			}
		}
	}
}
