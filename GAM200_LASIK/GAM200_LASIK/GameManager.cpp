/**************************************************************************************
 *	File Name        : GameManager.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019~2020 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "Graphic.h"
#include "GameManager.h"
#include "ObjectFactory.h"
#include "ComponentAttack.h"
#include "ComponentSprite.h"
#include "UnitStateComponent.hpp"
#include "ObjectMaterial.h"

GameManager* GAMEMANAGER = nullptr;

GameManager::GameManager()
{
	GAMEMANAGER = this;
	std::cout << "GameManager Add Sucessful" << std::endl;
	//Initialize();
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	const vec2<float> velocity{ ((rand() % 100) - 50) / 50.0f, ((rand() % 100) - 50) / 50.0f };
	pg.CreateParticles(30, { 0.f }, velocity, 1.0f);
}

void GameManager::Update(float dt)
{
	if (isGameEnd == false)
	{
		for (auto player : PlayerUnits)
		{
			if (player != nullptr)
			{
				UnitUpdate(player, dt);
			}
		}
		for (auto enemy : EnemyUnits)
		{
			if (enemy != nullptr)
			{
				UnitUpdate(enemy, dt);
			}
		}
		CheckCollision(); 
		DeleteUnits();
	}
}

void GameManager::CheckCollision()
{
	for (auto object : OBJECTFACTORY->GetObjectList())
	{
		for (auto object1 : OBJECTFACTORY->GetObjectList())
		{
			if (object.second->isCollideWith(*object1.second) && object.second->GetComponent<UnitState>()->GetType() == UnitType::ProjectilesPlayer && object1.second->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
			{
				if (object1.second->GetComponent<UnitState>()->GetInvincibilityState() == false)
				{
					object1.second->GetComponent<UnitState>()->SetHealth(object1.second->GetComponent<UnitState>()->GetHealth() - object.second->GetComponent<UnitState>()->GetDamage());
					GRAPHIC->DeleteMaterial(&object.second->GetComponent<MaterialComponent>()->material);
				}
				if (object.second->GetName() == "Fireball") {
					pg.DrawParticles();
				}
				OBJECTFACTORY->Destroy(object.second);
			}
			if (object.second->isCollideWith(*object1.second) && object.second->GetComponent<UnitState>()->GetType() == UnitType::ProjectilesEnemy && object1.second->GetComponent<UnitState>()->GetType() == UnitType::Player)
			{
				if (object1.second->GetComponent<UnitState>()->GetInvincibilityState() == false)
				{
					object1.second->GetComponent<UnitState>()->SetHealth(object1.second->GetComponent<UnitState>()->GetHealth() - object.second->GetComponent<UnitState>()->GetDamage());
					GRAPHIC->DeleteMaterial(&object.second->GetComponent<MaterialComponent>()->material);
				}
				OBJECTFACTORY->Destroy(object.second);
			}
		}
	}

	for (auto player : PlayerUnits)
	{
		if (player->GetComponent<UnitState>()->GetAttackState() == false)
		{
			for (auto enemy : EnemyUnits)
			{
				if (player->isObjectInAttackRange(*enemy))
				{
					player->GetComponent<UnitState>()->SetState(State::ATTACK);
					player->GetComponent<UnitState>()->SetAttackState(true);
					player->GetComponent<UnitState>()->SetSpriteChangeState(true);
					break;
				}
			}
		}

		else if (player->GetComponent<UnitState>()->GetAttackState() == true)
		{
			bool n = false;
			for (auto enemy : EnemyUnits)
			{
				if (player->isObjectInAttackRange(*enemy))
				{
					n = true;
					break;
				}
			}
			if (n == false)
			{
				player->GetComponent<UnitState>()->SetSpriteChangeState(true);
				player->GetComponent<UnitState>()->SetAttackState(false);
				player->GetComponent<UnitState>()->SetState(State::WALK);
			}
		}
	}

	for (auto enemy : EnemyUnits)
	{
		if (enemy->GetComponent<UnitState>()->GetAttackState() == false)
		{
			for (auto player : PlayerUnits)
			{
				if (enemy->isObjectInAttackRange(*player))
				{
					enemy->GetComponent<UnitState>()->SetState(State::ATTACK);
					enemy->GetComponent<UnitState>()->SetAttackState(true);
					enemy->GetComponent<UnitState>()->SetSpriteChangeState(true);
					break;
				}
			}
		}

		else if (enemy->GetComponent<UnitState>()->GetAttackState() == true)
		{
			bool n = false;
			for (auto player : PlayerUnits)
			{
				if (enemy->isObjectInAttackRange(*player))
				{
					n = true;
					break;
				}
			}
			if (n == false)
			{
				enemy->GetComponent<UnitState>()->SetSpriteChangeState(true);
				enemy->GetComponent<UnitState>()->SetAttackState(false);
				enemy->GetComponent<UnitState>()->SetState(State::WALK);
			}
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
	if (newObject->GetComponent<UnitState>()->GetType() == UnitType::Player) {
		PlayerUnits.emplace_back(newObject);
		PlayerAmount++;
	}
	else if (newObject->GetComponent<UnitState>()->GetType() == UnitType::Enemy) {
		EnemyUnits.emplace_back(newObject);
		EnemyAmount++;
	}
}

void GameManager::UnitUpdate(Object* object, float dt)
{
	if (object->GetName() != "Tower" && object->GetName() != "Lair")
	{
		object->GetComponent<ObjectAttackComponent>()->Update(dt);
		object->GetComponent<SpriteComponent>()->ChangeAnimation();
	}
	object->GetComponent<UnitState>()->healthBar.Update(object->transform.GetTranslation(), object->GetComponent<UnitState>()->GetHealth());
	
	const UnitType unitType = object->GetComponent<UnitState>()->GetType();
	if (object->GetComponent<UnitState>()->GetHealth() <= 0)
	{
		toBeDeleteList.push_back(object);
	}
}

void GameManager::DeleteUnits()
{
	//const UnitType unitType = object->GetComponent<UnitState>()->GetType();
	for (int i = 0; i < toBeDeleteList.size(); i++)
	{
		if (toBeDeleteList[i] == nullptr)
		{
			continue;
		}
		if (toBeDeleteList[i]->GetComponent<UnitState>()->GetType() == UnitType::Player)
		{
			for (std::vector<Object*>::iterator it = GAMEMANAGER->PlayerUnits.begin(); it != GAMEMANAGER->PlayerUnits.end(); ++it)
			{
				if (*it == toBeDeleteList[i])
				{
					GRAPHIC->DeleteMaterial(&toBeDeleteList[i]->GetComponent<MaterialComponent>()->material);
					GRAPHIC->DeleteMaterial(&toBeDeleteList[i]->GetComponent<UnitState>()->healthBar.material);
					GAMEMANAGER->PlayerUnits.erase(it);
					break;
				}
			}
		}
		else if (toBeDeleteList[i]->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
		{
			for (std::vector<Object*>::iterator it = GAMEMANAGER->EnemyUnits.begin(); it != GAMEMANAGER->EnemyUnits.end(); ++it)
			{
				if (*it == toBeDeleteList[i])
				{
					GRAPHIC->DeleteMaterial(&toBeDeleteList[i]->GetComponent<MaterialComponent>()->material);
					GRAPHIC->DeleteMaterial(&toBeDeleteList[i]->GetComponent<UnitState>()->healthBar.material);
					GAMEMANAGER->EnemyUnits.erase(it);
					break;
				}
			}
		}
		OBJECTFACTORY->Destroy(toBeDeleteList[i]);
	}
	toBeDeleteList.resize(0);
}