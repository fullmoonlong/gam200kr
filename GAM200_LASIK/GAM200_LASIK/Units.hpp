/*
Name: Wonju Cho
Creation Date : 11/14/2019
*/

#include"Object.h"
#include<vec2.hpp>

class Knight : public Object {
public:	
	
	int GetKnightHealth() { return knightHealth; }
	int GetKnightDamage() { return knightDamage; }
	//void SetKnightHealth(int damage) { knightHealth -= damage; }
	//void SetKnightDamage() { knightDamage = 15; }

private:
	int         knightHealth = 200;
	int         knightDamage =  15;
	vec2<float> knightSpeed;

};

class Archer : public Object {
public:
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
	
	int GetMagicianHealth() { return  magicianHealth; }
	int GetMagicianDamage() { return magicianDamage; }
	vec2<float>	GetMagicianAttackRange() { return magicianAttackRange; }

	//void SetMagicianHealth() { magicianHealth = 100; }
	//void SetMagicianDamage() { magicianDamage = 30; }
	//bool MagicianCollideWith(Object& object);
private:
	int         magicianHealth		= 100;
	int         magicianDamage		=  30;
	vec2<float>	magicianAttackRange = { 64, 0};
	vec2<float> magicianSpeed;
};

class Units : public Knight , public Archer , public Magician
{
public:
	void Initialize();
	
private:
	vec2<float> min;
	vec2<float> max;
};