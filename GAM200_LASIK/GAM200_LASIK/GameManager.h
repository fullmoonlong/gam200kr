/**************************************************************************************
 *	File Name        : GameManager.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019~2020 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <vector>
#include "System.h"
#include "Object.h"
#include "ParticleGenerator.hpp"

class GameManager : public System
{
public:
	GameManager();
	~GameManager();
	void Initialize() override;
	void Update(float dt) override;

	void CheckCollision();
	void CheckAttackState();
	void SpawnUnit(Object* object);
	void UnitUpdate(Object* object, float dt);

	int PlayerAmount = 0;
	int EnemyAmount = 0;

	std::vector<Object*> PlayerUnits;
	std::vector<Object*> EnemyUnits;

	bool isGameEnd = false;
//private:
	ParticleGenerator pg;
};
extern GameManager* GAMEMANAGER;