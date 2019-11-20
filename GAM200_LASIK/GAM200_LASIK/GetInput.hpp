#pragma once

class GetInput
{
public:
	GetInput() {}

	void TakeAsInput();
	int MatchStringWithInput();

private:
	std::string input;
	std::string knight = "Knight";
	std::string archer = "Archer";
	std::string magician = "Magician";
};