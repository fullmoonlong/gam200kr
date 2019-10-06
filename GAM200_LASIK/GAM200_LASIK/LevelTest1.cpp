#include "LevelTest1.h"
#include <iostream>

LevelTest1::LevelTest1()
{
	std::cout << "Add LevelTest1 Successful" << std::endl;
}

LevelTest1::~LevelTest1()
{
	std::cout << "Close LevelTest1 Successful" << std::endl;
}

void LevelTest1::Initialize()
{
	std::cout << "Load LevelTest1 Successful" << std::endl;
	test = objectFactory->CreateEmptyObject();
	test->SetPosition(0.f, 0.f);

	if (test != nullptr)
	{
		std::cout << "test object created" << std::endl;
		std::cout << test->GetXposition() << ", "<< test->GetYposition() << std::endl;
	}
}

void LevelTest1::Update()
{

}

void LevelTest1::Shutdown()
{

}
