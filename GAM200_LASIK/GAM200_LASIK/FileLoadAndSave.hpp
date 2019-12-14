/**************************************************************************************
 *	File Name        : FileLoadAndSave.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#ifndef FILE_H
#define FILE_H
#include <fstream>
#include "Object.h"

class File
{
public:
	bool Open(const std::string& filename);
	bool GetInt(int* pInt);
	bool GetFloat(float* pFloat);
	bool GetString(std::string* pString);
	bool EndOfFile() const;

	std::ifstream ifstream;
	std::ofstream ofstram;
private:
	
};
#endif
