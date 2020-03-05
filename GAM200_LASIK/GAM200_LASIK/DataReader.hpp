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
#include "Object.h"
#include "UnitStateComponent.hpp"

class DataReader {
public:
	static bool ReadData(const std::string& file_name, Object* object) {
		const std::string file = "../data/" + file_name;
		std::ifstream ifstream;
		ifstream.open(file.c_str(), std::ios::in);
		if (!ifstream.is_open()) {
			return false;
		}

		object->SetName(file_name.substr(0, file_name.size() - 4));		// 4 means .txt
		
		vec2<float> position, size, speed;
		std::string line, read;
		while (!ifstream.eof()) {
			std::stringstream lineStream;
			std::getline(ifstream, line);
			lineStream << line;
			lineStream >> read;
			if (read == "Position:") {
				lineStream >> position.x;
				lineStream >> position.y;
				object->SetPosition(position);
			}
			else if (read == "Size:") {
				lineStream >> size.x;
				lineStream >> size.y;
				object->SetSize(size);
			}
			else if (read == "Speed:") {
				lineStream >> speed.x;
				lineStream >> speed.y;
				object->speed = speed;
				//object->SetSpeed(speed);
			}
			else if (read == "Health:") {
				lineStream >> read;
				object->GetComponent<BaseUnitState>()->healthBar.Initialize(object->transform.GetTranslation(), stoi(read));
			}
			//else if (read == "Damage:") {
			//	lineStream >> read;
			//	object->GetComponent<BaseUnitState>()->SetDamage(stoi(read));
			//}
			else if (read == "Camp:") {
				lineStream >> read;
				if (read == "PlayerUnit") {
					object->GetComponent<BaseUnitState>()->SetType(Player);
				}
				else if (read == "EnemyUnit") {
					object->GetComponent<BaseUnitState>()->SetType(Enemy);
				}
				else if (read == "PlayerProjectile") {
					object->GetComponent<BaseUnitState>()->SetType(ProjectilesPlayer);
				}
				else if (read == "EnemyProjectile") {
					object->GetComponent<BaseUnitState>()->SetType(ProjectilesEnemy);
				}
			}
		}

		object->transform.SetTranslation(position);
		const vec2<float> halfSize = size / 2.f;
		object->min = position - halfSize;
		object->max = position + halfSize;
		object->transform.SetScale(size);

		return true;
	}
};