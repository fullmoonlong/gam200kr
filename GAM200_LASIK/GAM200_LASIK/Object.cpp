/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/

#include <GL/glew.h>
#include "Object.h"

const std::filesystem::path sprite_image = "../assets/sprite.png";

Object::Object()
	: position(0), objectID(0) {}

Object::~Object()
{
}

void Object::Initialize(vec2<float> starting_position, int spriteCount) noexcept
{
	transform.SetTranslation(starting_position);
	animation.spriteCount = spriteCount;
	float oneSide = 1.f / (float)animation.spriteCount;
	for (int i = 0; i <= animation.spriteCount; i++)
	{
		animation.texCoord.push_back((float)i * oneSide);
	}
	Image image;
	image.LoadFrom(sprite_image);
	animation.sprite.LoadTextureFrom(image);
	animation.baseTime = 0;
}

void Object::Update(float dt) noexcept
{
	static int spriteIndex = 0;
	animation.baseTime += dt;

	float texCoord[] = {
		animation.texCoord.at(spriteIndex), 0.f,
		animation.texCoord.at(spriteIndex + 1), 0.f,
		animation.texCoord.at(spriteIndex + 1), 1.f,
		animation.texCoord.at(spriteIndex), 1.f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);

	if (animation.baseTime >= 0.125f)
	{
		spriteIndex++;
		if (spriteIndex == 8)
		{
			spriteIndex = 0;
		}
		animation.baseTime -= 0.125f;
	}

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