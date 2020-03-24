/**************************************************************************************
 *	File Name        : CurrencySystem.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "System.h"

class CurrencySystem;
inline CurrencySystem* cs = nullptr;

class CurrencySystem : public System
{
public:
	CurrencySystem() { cs = this; }
	~CurrencySystem() {}
	
	void Initialize() override {}	// maybe file load
	void Update(float /*dt*/) override {}
	
	void Decrease(unsigned int amount) {
		if (money > amount) {
			money -= amount;
		}
		else {							// money will not be minus.
			money = 0;
		}
	}

	void Increase(unsigned int amount) {
		if (money + amount > MAX_MONEY) {
			money = MAX_MONEY;
		}
		else {
			money += amount;
		}
	}

	void diamondIncrease(unsigned int amount) {
		diamond += amount;
	}

	unsigned int GetDiamond() const { return diamond; }
	unsigned int GetMoney() const { return money; }
private:
	unsigned int MAX_MONEY = 9999;		// Maybe data-driven and read the data when the program starts and initializes.
	unsigned int money = 0;
	unsigned int diamond = 0;
};

extern CurrencySystem* cs;
