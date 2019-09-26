#pragma once
#include "Application.h"
#include "Object.h"
#include <string>

typedef unsigned int ObjectID;
class Object {
public:
	friend class ObjectFactory;
	Object();
	~Object();

	void Initialize();
	void Update();
	//void Render();

	ObjectID GetObjectID(){	return objectID;}
	void SetObjectID(ObjectID objID){ objectID = objID;}

	std::string GetName() const{return objectName;}
	void SetName(const std::string& name){objectName = name;}

	int GetXpos() { return xpos; };
	int GetYpos() { return ypos; };
	int SetXpos(int x) { return xpos = x; };
	int SetYpos(int y) { return ypos = y; };

	ObjectID objectID;
private:
	std::string objectName = "";
	int xpos;
	int ypos;
};