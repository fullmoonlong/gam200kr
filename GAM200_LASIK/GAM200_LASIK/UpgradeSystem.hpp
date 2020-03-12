/**************************************************************************************
 *	File Name        : UpgradeSystem.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#pragma once
#include"System.h"

class UpgradeSystem;
inline UpgradeSystem* up = nullptr;

class UpgradeSystem :public System {
public:
	UpgradeSystem() { up = this; }
	~UpgradeSystem() {} 

	void Initialize() override {}
	void Update(float /*dt*/)override{}
	
	void SetKnightUpgrade(bool upgrade) { knightUpgrade = upgrade; }
	void SetArcherUpgrade(bool upgrade) { archerUpgrade = upgrade; }
	void SetMagicianUpgrade(bool upgrade) { magicianUpgrade = upgrade; }
	void SetCavalryUpgrade(bool upgrade) { cavalryUpgrade = upgrade; }

	bool GetKnightUpgrade  () { return knightUpgrade; }
	bool GetArcherUpgrade  () { return archerUpgrade; }
	bool GetMagicianUpgrade() { return magicianUpgrade; }
	bool GetCavalryUpgrade () { return cavalryUpgrade; }

private:
	bool knightUpgrade = false;
	bool archerUpgrade = false;
	bool magicianUpgrade = false;
	bool cavalryUpgrade = false;
};

extern UpgradeSystem* up;