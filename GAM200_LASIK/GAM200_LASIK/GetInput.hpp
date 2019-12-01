#pragma once

class GetInput
{
public:
	GetInput() {}

	void TakeAsInput(char input);
	int MatchStringWithInput();
	void SetString(std::string initial) { string = initial; }
	std::string GetString() { return string; }

private:
	std::string string;
	std::string knight = "knight";
	std::string archer = "archer";
	std::string magician = "magician";
};