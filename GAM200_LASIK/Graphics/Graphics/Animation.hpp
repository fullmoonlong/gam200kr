/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.hpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#pragma once
#include "Shader.h"

class Animation
{
public:
	Animation() = default;
	
	struct SpriteSheet
	{
		int frameX;
		float animateSpeed;
	};

	void Initialize(SpriteSheet new_sheet, const Shader& new_shader);
	void Animate(float dt);
	void ChangeAnimation(int new_count);
private:
	Shader shader;
	SpriteSheet spriteSheet;
	int frameIndex = 0;
	float baseTime = 0.0f;
};
