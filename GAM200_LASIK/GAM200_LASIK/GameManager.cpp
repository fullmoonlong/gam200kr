/**************************************************************************************
 *	File Name        : GameManager.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019~2020 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include <iostream>
#include "GameManager.h"
#include "ObjectFactory.h"
#include "UnitStateComponent.hpp"

GameManager* GAMEMANAGER = nullptr;

GameManager::GameManager()
{
	GAMEMANAGER = this;
	std::cout << "GameManager Add Sucessful" << std::endl;
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
}

void GameManager::Update(float /*dt*/)
{
	if (isGameEnd == false)
	{
		CheckCollision();
		CheckAttackState();
	}
}

void GameManager::CheckCollision()
{
	for (auto object : OBJECTFACTORY->GetObjecteList())
	{
		for (auto object1 : OBJECTFACTORY->GetObjecteList())
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

void GameManager::CheckAttackState()
{
	int playerTotalNotWhileAttack = 0;
	int enemyTotalNotWhileAttack = 0;


	for (auto obj : OBJECTFACTORY->GetObjecteList())
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

void GameManager::SpawnUnit(Object* object)
{
	Object* newObject = object->Clone();

	newObject->SetObjectID(OBJECTFACTORY->GetLastObjectID());
	OBJECTFACTORY->objectIDMap.emplace(OBJECTFACTORY->GetLastObjectID(), newObject);
	OBJECTFACTORY->lastObjectID++;
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
