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

	void SetSkeletionHealth(int damage) { SkeletionHealth -= damage; }
	//void SetKnightDamage() { knightDamage = 15; }
private:

	int         SkeletionHealth = 100;
	int         SkeletionDamage =  10;
	vec2<float> SkeletionSpeed;

};

class EnemyUnits : public Skeleton
{
public:
	void Initialize();
};