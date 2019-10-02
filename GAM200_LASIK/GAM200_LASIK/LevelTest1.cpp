#include "LevelTest1.h"
#include <iostream>

LevelTest1::LevelTest1()
{
	std::cout << "Add LevelTest1 Sucessful" << std::endl;
}

LevelTest1::~LevelTest1()
{
	std::cout << "Close LevelTest1 Sucessful" << std::endl;
}

void LevelTest1::Initialize()
{
	std::cout << "Load LevelTest1 Sucessful" << std::endl;
}

void LevelTest1::Update()
{
}

void LevelTest1::Shutdown()
{
}
