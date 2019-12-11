
#include "Test.hpp"

int main()
{
	Test test;

	test.Initialize();

	while (test.IsRunning())
	{
		test.Update();
	}

	return 0;
}