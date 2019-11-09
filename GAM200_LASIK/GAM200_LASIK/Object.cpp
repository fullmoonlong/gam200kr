/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/

#include "Object.h"
#include <iostream>

Object::Object()
	: objectID(0), position(0) {}

void Object::Initialize(vec2<float> starting_position, float width, float height) noexcept
{
	transform.SetTranslation(starting_position);
	position = starting_position;
	float half_width = width / 2;
	float half_height = height / 2;
	min = { starting_position.x - half_width, starting_position.y - half_height };
	max = { starting_position.x + half_width, starting_position.y + half_height };
}

void Object::Update(float dt) noexcept
{
	float decision_x = speed.x * dt;
	float decision_y = speed.y * dt;
	float dx = transform.GetTranslation().x + decision_x;
	float dy = transform.GetTranslation().y + decision_y;
	transform.SetTranslation({ dx, dy });
	position.x += decision_x;
	position.y += decision_y;
	min.x += decision_x;
	max.x += decision_x;
	min.y += decision_y;
	max.y += decision_y;
}
Object* Object::Clone()
{
	return new Object(*this);
}


bool Object::isCollideWith(Object& object) noexcept
{
	return !(max.x < object.min.x || object.max.x < min.x || max.y < object.min.y || object.max.y < min.y);
}

bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width / 2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}