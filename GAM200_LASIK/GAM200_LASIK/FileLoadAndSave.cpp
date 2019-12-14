/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/11/20
*/
#include "FileLoadAndSave.hpp"

bool File::Open(const std::string& filename)
{
	std::string path = "../data/" + filename;
	ifstream.open(path.c_str(), std::ios::in);
	return ifstream.good();

}

bool File::GetInt(int* pInt)
{
	std::string s;
	if (!GetString(&s))
	{
		return false;
	}
	*pInt = atoi(s.c_str());
	return true;
}

bool File::GetFloat(float* pFloat)
{
	ifstream >> (*pFloat);
	return true;
}

bool File::GetString(std::string* pString)
{
	char buf[128];
	while (true)
	{
		if (EndOfFile())
		{
			return false;
		}

		ifstream.getline(buf, 10000);
		*pString = buf;

		if (pString->size() > 0 && (*pString)[0] == '#')
		{
			continue;
		}
		if (!pString->empty())
		{
			return true;
		}
	}
}

bool File::EndOfFile() const
{
	return ifstream.eof() || !ifstream.good();
}