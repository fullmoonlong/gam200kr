/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/

#include "Object.h"

Object::Object()
	: objectID(0), position(0) {}

void Object::Initialize(vec2<float> starting_position) noexcept
{
	transform.SetTranslation(starting_position);
}

void Object::Update(float dt) noexcept
{
	float decision_x = 120.f * speed.x * dt;
	float dicision_y = 120.f * speed.y * dt;
	float dx = transform.GetTranslation().x + decision_x;
	float dy = transform.GetTranslation().y + dicision_y;
	transform.SetTranslation({ dx, dy });
	min.x += decision_x;
	max.x += decision_x;
	min.y += dicision_y;
	max.y += dicision_y;
}

bool Object::isCollideWith(Object& object) noexcept
{
	return !(max.x < object.min.x || object.max.x < min.x || max.y < object.min.y || object.max.y < min.y);
}

bool Object::isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept
{
	return !(max.x + (width/2.0f) < mouse_position.x || mouse_position.x < min.x + (width / 2.0f) || max.y + (height / 2.0f) < mouse_position.y || mouse_position.y < min.y + (height / 2.0f));
}