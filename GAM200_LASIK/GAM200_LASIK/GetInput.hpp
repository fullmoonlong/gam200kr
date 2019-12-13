#pragma once

class GetInput
{
public:
	GetInput() {}

	void TakeAsInput(char input);
	int MatchStringWithInput();
	void Erasing();
	void SetString(std::wstring initial) { string = initial; }
	std::wstring GetString() { return string; }

private:
	std::wstring string;
	std::wstring knight = L"knight";
	std::wstring archer = L"archer";
	std::wstring magician = L"magician";
};