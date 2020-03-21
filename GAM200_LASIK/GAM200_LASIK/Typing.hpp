/**************************************************************************************
 *	File Name        : Typing.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "ChatBox.hpp"
#include "Cost.hpp"

class GameManager;
class Text;
enum class KeyboardButton;

class Typing {
public:
	Typing();
	
	void Type(KeyboardButton button);
	void Enter(Cost& cost);
	void EraseOneCharacter();
	void ClearString() { string = L""; }

	std::wstring GetString() const { return string; }
	void SetString(std::wstring new_string) { string = new_string; }
	void SetUnitPtr(Knight* knight_ptr, Archer* archer_ptr, Magician* magician_ptr,
		Skeleton* skeleton_ptr, Lich* lich_ptr);
public:
	bool isTyping;
	ChatBox  cb;
	Text symbol;
	//Cost cost;

	bool isDebugMode;
	void Debug(KeyboardButton button) noexcept;
	void ToggleDebug() { isDebugMode = !isDebugMode; }
private:
	std::wstring string;
	
	Knight* knightPtr = nullptr;
	Archer* archerPtr = nullptr;
	Magician* magicianPtr = nullptr;

	Skeleton* skeletonPtr = nullptr;
	Lich* lichPtr = nullptr;
};
