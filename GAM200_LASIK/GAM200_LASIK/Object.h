#pragma once
#include <string>

typedef unsigned int ObjectID;

struct position
{
	float x, y;
	position(float x_, float y_) : x(x_), y(y_) {}
};

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

	float GetXposition() { return xpos; };
	float GetYposition() { return ypos; };
	position SetPosition(float x, float y) { xpos = x; ypos = y; return position(xpos, ypos); }

private:
	ObjectID objectID;
	std::string objectName = "";
	float xpos;
	float ypos;
};