/**************************************************************************************
 *	File Name        : Animation.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Shader.h"

class Animation
{
public:
	Animation() = default;
	
	struct SpriteSheet
	{
		int frameX;
		int frameY;
		float animateSpeed;
	};

	void Initialize(SpriteSheet sprite_sheet, const Shader& shader);
	void Initialize(int column, int row, float animation_speed, const Shader& shader);
	void Animate(float dt);
	void ChangeAnimation(SpriteSheet new_sprite_sheet);
	void ChangeAnimation(int new_column, int new_row);
	void ChangeAnimation(int new_column, int new_row, float new_animation_speed);
private:
	Shader shader;
	SpriteSheet spriteSheet;
	int frameIndex = 0;
	float baseTime = 0.0f;
};
