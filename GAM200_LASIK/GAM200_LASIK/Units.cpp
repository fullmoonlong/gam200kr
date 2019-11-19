/*
Name: Wonju Cho
Creation Date : 11/14/2019
*/
#include "Units.hpp"

void Units::Initialize()
{
	GetArcherDamage();
	GetArcherHealth();
	GetKnightDamage();
	GetKnightHealth();
	GetMagicianDamage();
	GetMagicianHealth();
}

//bool Archer::ArcherCollideWith(Object& object)
//{
//	return !(max.x + archerAttackRange < object.min.x || object.max.x < min.x + archerAttackRange || max.y + archerAttackRange < object.min.y || object.max.y < min.y + archerAttackRange);
//}
//
//bool Magician::MagicianCollideWith(Object& object)
//{
//	return !(max.x + magicianAttackRange < object.min.x || object.max.x < min.x + magicianAttackRange || max.y + magicianAttackRange < object.min.y || object.max.y < min.y + magicianAttackRange);
//}
