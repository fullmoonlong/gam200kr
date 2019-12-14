/**************************************************************************************
 *	File Name        : EnemyUnits.hpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include"Object.h"
#include<vec2.hpp>

class Skeleton :public Object {
public:
	int GetSkeletionHealth() { return SkeletionHealth; }
	int GetSkeletionDamage() { return SkeletionDamage; }
private:

	int         SkeletionHealth = 100;
	int         SkeletionDamage =  10;

};

class Lich :public Object {
public:
	int GetLichHealth() { return LichHealth; }
	int GetLichDamage() { return LichDamage; }
	vec2<float> GetLichAttackRange() { return LichAttackRange; }

private:

	int         LichHealth = 50;
	int         LichDamage = 50;
	vec2<float>	LichAttackRange = { 166, 0 };

};

class Golem :public Object {
public:
	int GetGolemHealth() { return GolemHealth; }
	int GetGolemDamage() { return GolemDamage; }

private:

	int         GolemHealth = 350;
	int         GolemDamage = 40;

};

class EnemyUnits : public Skeleton
{
public:
	void Initialize();
};