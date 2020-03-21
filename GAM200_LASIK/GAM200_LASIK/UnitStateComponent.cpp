#include "UnitStateComponent.hpp"

void UnitState::UpdateState(float dt)
{
	DamageOverTime(dt);
	SlowDown(dt);
}

void UnitState::DamageOverTime(float dt)
{
	if (isDotOn == true)
	{
		dotDeltaTime += dt;
		if (dotDeltaTime > timePerDamage)
		{
			dotDeltaTime = 0.f;
			dotAmount++;
			unit->GetComponent<UnitState>()->SetHealth(unit->GetComponent<UnitState>()->GetHealth() - damagePerTime);
		}
		if (dotFullAmount == dotAmount)
		{
			damagePerTime = 0;
			timePerDamage = 0.f;

			dotAmount = 0;
			dotFullAmount = 0;
			isDotOn = false;
		}
	}
}

void UnitState::SlowDown(float dt)
{
	if (isSlowDownOn == true)
	{
		slowDeltaTime += dt;
		if (slowDeltaTime > slowDownFullTime)
		{
			slowDownFullTime = 0.f;
			unit->speed = originalSpeed;
			originalSpeed = { 0.f, 0.f };
			slowDeltaTime = 0.f;
			isSlowDownOn = false;
		}
	}
}

void UnitState::SetDamageOverTime(int damage_per_time, float time_per_damage, int full_dot_amount)
{
	if (isDotOn == false)
	{
		damagePerTime = damage_per_time;
		timePerDamage = time_per_damage;
		dotFullAmount = full_dot_amount;
		isDotOn = true;
	}
}

void UnitState::SetSlowDown(vec2<float> reduction, float full_time) //player-> +, enemt-> -
{
	if (isSlowDownOn == false)
	{
		slowDownFullTime = full_time;
		originalSpeed = unit->speed;
		unit->speed -= reduction;
		isSlowDownOn = true;
	}
}
