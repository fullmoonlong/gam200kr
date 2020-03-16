/**************************************************************************************
 *	File Name        : UnitStateComponent.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Component.h"
#include "ComponentType.h"
#include "Object.h"
#include"UI.hpp"

enum UnitType {
	Player,
	Enemy,
	ProjectilesPlayer,
	ProjectilesEnemy
};

enum State {
	WALK,
	ATTACK,
	IDLE
};

class BaseUnitState : public Component
{
public:
	BaseUnitState() : Component(ComponentType::BASEUNITSTATE) {};
	~BaseUnitState() override {};
	virtual void Initialize() override {};

	UnitType GetType() { return unitType; }
	void SetType(UnitType unittype) { unitType = unittype; };

	State GetState() { return state; }
	void SetState(State state_) { state = state_; };

	vec2<float> GetAttackRange() const { return attackRange; }
	void SetAttackRange(vec2<float> attackrange) { attackRange = attackrange; }

	bool GetAttackState() { return attackState; }
	void SetAttackState(bool attackstate) { attackState = attackstate; };

	bool GetSpriteChangeState() { return spriteChange; }
	void SetSpriteChangeState(bool spritestate) { spriteChange = spritestate; };

	int GetHealth() { return health; }
	void SetHealth(int health_) { health = health_; };

	int GetDamage() { return damage; }
	void SetDamage(int damage_) { damage = damage_; };

	bool GetInvincibilityState() { return invincibilityState; }
	void SetInvincibilityState(bool invincibilitystate) { invincibilityState = invincibilitystate; };

	UI::HealthBar healthBar;
	vec2<float> attackRange = { 0, 0 };

private:
	Object* unit;

	UnitType unitType;
	State state;

	bool attackState = false;
	bool spriteChange = false;
	bool invincibilityState = false;

	int health = 0;
	int damage = 0;


	float baseTime = 0.f;
};


class UnitState : public Component
{
public:
	UnitState() : Component(ComponentType::UNITSTATE) {};
	~UnitState() override {};
	virtual void Initialize() override {};

	void SetUnit(Object* object_) { unit = object_; }

	UnitType GetType() { return unitType; }
	void SetType(UnitType unittype) { unitType = unittype; };

	State GetState() { return state; }
	void SetState(State state_) { state = state_; };

	vec2<float> GetAttackRange() const { return attackRange; }
	void SetAttackRange(vec2<float> attackrange) { attackRange = attackrange; }

	bool GetAttackState() { return attackState; }
	void SetAttackState(bool attackstate) { attackState = attackstate; };

	bool GetSpriteChangeState() { return spriteChange; }
	void SetSpriteChangeState(bool spritestate) { spriteChange = spritestate; };

	int GetHealth() { return health; }
	void SetHealth(int health_) { health = health_; };

	int GetDamage() { return damage; }
	void SetDamage(int damage_) { damage = damage_; };

	bool GetInvincibilityState() { return invincibilityState; }
	void SetInvincibilityState(bool invincibilitystate) { invincibilityState = invincibilitystate; };

	//CC
	void UpdateState(float dt);

	void DamageOverTime(float dt);
	void SlowDown(float dt);

	void SetDamageOverTime(int damage_per_time, float time_per_damage, int full_dot_amount);
	void SetSlowDown(vec2<float> reduction, float full_time);
	//CC

	UI::HealthBar healthBar;
	vec2<float> attackRange = { 0, 0 };

private:
	Object* unit;

	UnitType unitType;
	State state;

	bool attackState = false;
	bool spriteChange = false;
	bool invincibilityState = false;

	int health = 0;
	int damage = 0;

	float baseTime = 0.f;

	//CC
	int dotAmount = 0;
	int dotFullAmount = 0;
	int damagePerTime = 0;
	float timePerDamage = 0.f;
	float dotDeltaTime = 0.f;
	bool isDotOn = false;

	float slowDownFullTime = 0.f;
	float slowDeltaTime = 0.f;
	bool isSlowDownOn = false;

	vec2<float> originalSpeed;
	//CC
};