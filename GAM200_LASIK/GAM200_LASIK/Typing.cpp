/**************************************************************************************
 *	File Name        : Typing.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <string>			// include this before typing.hpp
#include "Units.hpp"
#include "Text.hpp"
#include "Typing.hpp"
#include "Eventhandler.hpp"
#include "GameManager.h"
#include "UnitStateComponent.hpp"

Typing::Typing()
	: isTyping(false), isDebugMode(false) {
}

void Typing::Type(KeyboardButton button) {
	if (isTyping) {
		switch (button) {
		case KeyboardButton::A:
			string.push_back('a');
			break;
		case KeyboardButton::B:
			string.push_back('b');
			break;
		case KeyboardButton::C:
			string.push_back('c');
			break;
		case KeyboardButton::D:
			string.push_back('d');
			break;
		case KeyboardButton::E:
			string.push_back('e');
			break;
		case KeyboardButton::F:
			string.push_back('f');
			break;
		case KeyboardButton::G:
			string.push_back('g');
			break;
		case KeyboardButton::H:
			string.push_back('h');
			break;
		case KeyboardButton::I:
			string.push_back('i');
			break;
		case KeyboardButton::J:
			string.push_back('j');
			break;
		case KeyboardButton::K:
			string.push_back('k');
			break;
		case KeyboardButton::L:
			string.push_back('l');
			break;
		case KeyboardButton::M:
			string.push_back('m');
			break;
		case KeyboardButton::N:
			string.push_back('n');
			break;
		case KeyboardButton::O:
			string.push_back('o');
			break;
		case KeyboardButton::P:
			string.push_back('p');
			break;
		case KeyboardButton::Q:
			string.push_back('q');
			break;
		case KeyboardButton::R:
			string.push_back('r');
			break;
		case KeyboardButton::S:
			string.push_back('s');
			break;
		case KeyboardButton::T:
			string.push_back('t');
			break;
		case KeyboardButton::U:
			string.push_back('u');
			break;
		case KeyboardButton::V:
			string.push_back('v');
			break;
		case KeyboardButton::W:
			string.push_back('w');
			break;
		case KeyboardButton::X:
			string.push_back('x');
			break;
		case KeyboardButton::Y:
			string.push_back('y');
			break;
		case KeyboardButton::Z:
			string.push_back('z');
			break;
		case KeyboardButton::Backspace:
			EraseOneCharacter();
			break;
		default:;
		}
	}
	else if (isDebugMode) {
		Debug(button);
	}
}

void Typing::Enter(Cost& cost) {
	const std::wstring type = GetString();

	if (!isTyping) {
		isTyping = true;
		symbol.SetString(L">");
		return;
	}

	// change wstring -> string
	// use map check the object name
	// spawn the match
	if (type == L"knight" && cost.GetCost() >= 4) {
		GAMEMANAGER->SpawnUnit(knightPtr);
		cost.AddCost(-4);
	}
	else if (type == L"archer" && cost.GetCost() >= 6) {
		GAMEMANAGER->SpawnUnit(archerPtr);
		cost.AddCost(-6);
	}
	else if (type == L"magician" && cost.GetCost() >= 8) {
		GAMEMANAGER->SpawnUnit(magicianPtr);
		cost.AddCost(-8);
	}
	else if (type == L"debug") {
		ToggleDebug();
	}
	isTyping = false;
	cb.AddHistory(GetString());
	ClearString();
	symbol.SetString(L"");
}

void Typing::EraseOneCharacter() {
	if (string.size() > 0) {
		string.pop_back();
	}
}

void Typing::SetUnitPtr(Knight* knight_ptr, Archer* archer_ptr, Magician* magician_ptr, Skeleton* skeleton_ptr,
	Lich* lich_ptr) {
	knightPtr = knight_ptr;
	archerPtr = archer_ptr;
	magicianPtr = magician_ptr;
	skeletonPtr = skeleton_ptr;
	lichPtr = lich_ptr;
}

void Typing::Debug(KeyboardButton button) noexcept {
	const int randomNumber = rand();
	const int randomAlly = randomNumber % 3;
	const int randomEnemy = randomNumber % 2;
	switch (button) {
	case KeyboardButton::Num1:
		if (randomAlly == 0) {
			GAMEMANAGER->SpawnUnit(knightPtr);
		}
		else if (randomAlly == 1) {
			GAMEMANAGER->SpawnUnit(archerPtr);
		}
		else if (randomAlly == 2) {
			GAMEMANAGER->SpawnUnit(magicianPtr);
		}
		break;
	case KeyboardButton::Num2:
		if (randomEnemy == 0) {
			GAMEMANAGER->SpawnUnit(skeletonPtr);
		}
		else if (randomEnemy == 1) {
			GAMEMANAGER->SpawnUnit(lichPtr);
		}
		break;
	case KeyboardButton::Num3:
		for (auto obj : GAMEMANAGER->PlayerUnits) {
			if (obj->GetName() != "tower") {
				obj->GetComponent<UnitState>()->SetHealth(0);
			}
		}
		break;
	case KeyboardButton::Num4:
		for (auto obj : GAMEMANAGER->EnemyUnits) {
			if (obj->GetName() != "lair") {
				obj->GetComponent<UnitState>()->SetHealth(0);
			}
		}
		break;
	case KeyboardButton::Num5:
		for (auto obj : GAMEMANAGER->PlayerUnits) {
			obj->GetComponent<UnitState>()->SetInvincibilityState(true);
			//obj->GetComponent<UnitState>()->SetDamageOverTime(20, 0.5f, 3);
		}
		break;
	case KeyboardButton::Num6:
		for (auto obj : GAMEMANAGER->PlayerUnits) {
			obj->GetComponent<UnitState>()->SetInvincibilityState(false);
			//obj->GetComponent<UnitState>()->SetSlowDown({ 99.f, 0.f}, 1.f);
		}
	}
}
