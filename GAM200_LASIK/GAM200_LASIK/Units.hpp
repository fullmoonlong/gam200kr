/**************************************************************************************
 *	File Name        : Units.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author : Doyeong Yi
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Object.h"
#include <vec2.hpp>
#include "UnitStateComponent.hpp"

class Knight : public Object {
public:	
	void UnitInitialize(const char* name);

	int GetKnightHealth() { return knightHealth; }
	int GetKnightDamage() { return knightDamage; }

private:
	int         knightHealth = 200;
	int         knightDamage =  15;
	vec2<float> knightSpeed;

};

class Archer : public Object {
public:
	void UnitInitialize(const char* name);

	int GetArcherHealth() { return  archerHealth; }
	int GetArcherDamage() { return archerDamage; }
	vec2<float>	 GetArcherAttackRange() { return archerAttackRange; }

	//void SetArcherHealth() { archerHealth = 150; }
	//void SetArcherDamage() { archerDamage = 10; }
	//bool ArcherCollideWith(Object& object);
private:
	int         archerHealth		= 150;
	int         archerDamage		=  10;
	vec2<float>	archerAttackRange = { 128, 0 };
	vec2<float> archerSpeed;
};

class Magician : public Object {
public:
	void UnitInitialize(const char* name);
	
	int GetMagicianHealth() { return  magicianHealth; }
	int GetMagicianDamage() { return magicianDamage; }
	vec2<float>	GetMagicianAttackRange() { return magicianAttackRange; }
private:
	int         magicianHealth		= 100;
	int         magicianDamage		=  50;
	vec2<float>	magicianAttackRange = { 196, 0};
	vec2<float> magicianSpeed;
};
