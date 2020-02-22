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

class Arthur : public Object {
public:

	int GetArthurHealth() { return arthurHealth; }
	int GetArthurDamage() { return arthurDamage; }
	int GetarthurCost() { return arthurCost;}
private:
	int         arthurHealth = 200;
	int         arthurDamage = 15;
	int			arthurCost = 5;
	vec2<float> arthurSpeed;

};

class Archer : public Object {
public:
	void UnitInitialize(const char* name);

	int GetArcherHealth() { return  archerHealth; }
	int GetArcherDamage() { return archerDamage; }
	vec2<float>	 GetArcherAttackRange() { return archerAttackRange; }
private:
	int         archerHealth		= 150;
	int         archerDamage		=  10;
	vec2<float>	archerAttackRange = { 128, 0 };
	vec2<float> archerSpeed;
};

class Artemis : public Object {
public:
	int GetArtemisHealth() { return  artemisHealth; }
	int GetArtemisDamage() { return artemisDamage; }
	vec2<float>	 GetArtemisAttackRange() { return artemisAttackRange; }
	int GetArtemisCost() { return artemisCost;}
private:
	int         artemisHealth = 150;
	int         artemisDamage = 10;
	int			artemisCost = 7;
	vec2<float> artemisAttackRange = { 128, 0 };
	vec2<float> artemisSpeed;
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

class Siegfried : public Object {
public:	
	int GetSiegfriedHealth() { return  siegfriedHealth; }
	int GetSiegfriedDamage() { return siegfriedDamage; }
	int GetSiegfriedCost(){return siegfriedCost;}
	vec2<float>	GetSiegfriedAttackRange() { return siegfriedAttackRange; }
private:
	int         siegfriedHealth		= 100;
	int         siegfriedDamage		=  50;
	int			siegfriedCost = 9;
	vec2<float>	siegfriedAttackRange = { 196, 0};
	vec2<float> siegfriedSpeed;
};

class Cavalry :public Object {
public:
	int GetCavalryHealth() { return cavalryHealth; }
	int GetCavalryDamage() { return cavalryDamage; }
private:
	int cavalryHealth = 50;
	int cavalryDamage = 70;
	vec2<float> cavalrySpeed;
};

class Valkyrie :public Object {
public:
	int GetValkyrieHealth() { return valkyrieHealth; }
	int GetValkyrieDamage() { return valkyrieDamage; }
	int GetValkyrieCost() { return valkyrieCost;}
private:
	int valkyrieHealth = 50;
	int valkyrieDamage = 70;
	int valkyrieCost = 6;
	vec2<float> valkyrieSpeed;
};