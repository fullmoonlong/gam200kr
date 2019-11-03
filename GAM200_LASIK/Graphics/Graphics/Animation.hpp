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
#include <vector>
#include "Mesh.h"
#include "Texture.hpp"

class Animation
{
public:
	void Initialize(Image& new_sprite, Mesh& new_shape, int new_count);

	Animation() = default;
	Animation(Image& new_sprite, Mesh& new_shape, int new_count);

	void Animate(float dt);
private:
	Texture spriteSheet;
	Mesh shape;
	std::vector<float> textureCoord;
	int sceneCount;
	float baseTime = 0.0f;
};
