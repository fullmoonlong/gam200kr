/**************************************************************************************
 *	File Name        : DataReader.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vec2.hpp>
#include "Object.hpp"
#include "UnitStateComponent.hpp"

class DataReader {
public:
	static bool OpenAndReadData(const std::string& file_name, Object* object) {
		const std::string file = "../data/" + file_name;
		std::ifstream ifstream;
		ifstream.open(file.c_str(), std::ios::in);
		if (!ifstream.is_open()) {
			return false;
		}
	
		std::string line, read;
		while (!ifstream.eof()) {
			std::stringstream lineStream;
			std::getline(ifstream, line);
			lineStream << line;
			lineStream >> read;
			if (read == "Name:") {
				lineStream >> read;
				object->SetName(read);
			}
			else if (read == "Position:") {
				vec2<float> position;
				//lineStream >> read;
				//position.x = stoi(read);
				//lineStream >> read;
				//position.y = stoi(read);
				lineStream >> position.x;
				lineStream >> position.y;
				object->SetPosition(position);
			}
			else if (read == "Size:") {
				vec2<float> size;
				//lineStream >> read;
				//size.x = stoi(read);
				//lineStream >> read;
				//size.y = stoi(read);
				lineStream >> size.x;
				lineStream >> size.y;
				object->SetSize(size);
			}
			else if (read == "Speed:") {
				vec2<float> speed;
				//lineStream >> read;
				//speed.x = stoi(read);
				//lineStream >> read;
				//speed.y = stoi(read);
				lineStream >> speed.x;
				lineStream >> speed.y;
				object->SetSpeed(speed);
			}
			else if (read == "Health:") {
				lineStream >> read;
				object->GetComponent<BaseUnitState>()->healthBar.Initialize(object->transform.GetTranslation(), stoi(read));
			}
			else if (read == "Camp:") {
				lineStream >> read;
				if (read == "PlayerUnit") {
					object->GetComponent<BaseUnitState>()->SetType(Player);
				}
				else if (read == "EnemyUnit") {
					object->GetComponent<BaseUnitState>()->SetType(Player);
				}
				else if (read == "PlayerProjectile") {
					object->GetComponent<BaseUnitState>()->SetType(Player);
				}
				else if (read == "EnemyProjectile") {
					object->GetComponent<BaseUnitState>()->SetType(Player);
				}
			}
		}
	return true;
};