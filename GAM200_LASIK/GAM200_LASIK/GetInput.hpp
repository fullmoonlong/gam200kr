/**************************************************************************************
 *	File Name        : GetInput.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jookyung Lee
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once

class GetInput
{
public:
	GetInput() {}

	void TakeAsInput(char input);
	void TakeAsSymbol(char input);
	int MatchStringWithInput();
	void Erasing();
	void SetString(std::wstring initial) { string = initial; }
	std::wstring GetString() { return string; }

	std::wstring GetSymbolString() { return symbol; }

private:
	std::wstring string;
	std::wstring symbol;
	//units
	std::wstring knight = L"knight";
	std::wstring archer = L"archer";
	std::wstring magician = L"magician";
	//units
	//levels
	std::wstring tutorial = L"tutorial";
	std::wstring level1 = L"level1";
	std::wstring upgrade = L"upgrade";
	std::wstring levelSelect = L"levelselect";
	//levels
	//upgrade units
	std::wstring arthur = L"arthur";
	std::wstring artemis = L"artemis";
	std::wstring siegfried = L"siegfried";
	std::wstring valkyrie = L"valkyrie";

};