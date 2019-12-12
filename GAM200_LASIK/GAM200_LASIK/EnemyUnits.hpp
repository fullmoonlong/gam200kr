/*
Name: Wonju Cho
Creation Date : 11/14/2019
*/

#include"Object.h"
#include<vec2.hpp>

class Skeleton :public Object {
public:
	int GetSkeletionHealth() { return SkeletionHealth; }
	int GetSkeletionDamage() { return SkeletionDamage; }

	//void SetSkeletionHealth(int damage) { SkeletionHealth -= damage; }
	//void SetKnightDamage() { knightDamage = 15; }
private:

	int         SkeletionHealth = 100;
	int         SkeletionDamage =  10;

};

class Lich :public Object {
public:
	int GetLichHealth() { return LichHealth; }
	int GetLichDamage() { return LichDamage; }
	vec2<float> GetLichAttackRange() { return LichAttackRange; }

	//void SetSkeletionHealth(int damage) { SkeletionHealth -= damage; }
	//void SetKnightDamage() { knightDamage = 15; }
private:

	int         LichHealth = 50;
	int         LichDamage = 50;
	vec2<float>	LichAttackRange = { 166, 0 };

};

class Golem :public Object {
public:
	int GetGolemHealth() { return GolemHealth; }
	int GetGolemDamage() { return GolemDamage; }

	//void SetSkeletionHealth(int damage) { SkeletionHealth -= damage; }
	//void SetKnightDamage() { knightDamage = 15; }
private:

	int         GolemHealth = 350;
	int         GolemDamage = 40;

};

class EnemyUnits : public Skeleton
{
public:
	void Initialize();
};