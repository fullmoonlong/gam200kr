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

class Unit : public Object {
public:
	void Initialize(const char* name) noexcept override;
	//virtual ~Unit() { std::cout << "Unit destory\n"; }
};

//===Ally==============================================

class Knight : public Unit {
public:
	//~Knight() { std::cout << "Knight destory\n"; }
};

class Archer : public Unit {
public:
	//~Archer() { std::cout << "Archer destory\n"; }
};

class Magician : public Unit {
public:
	//~Magician() { std::cout << "Magician destory\n"; }
};

//===Enemy=============================================

class Skeleton : public Unit {
public:
	int GetMoney() { return money; }
private:
	int money = 2;
};

class Lich : public Unit {
	
};

class Golem : public Unit {
	
};
