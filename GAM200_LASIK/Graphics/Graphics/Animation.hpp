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
#include <filesystem>
#include "Mesh.h"
#include "Texture.hpp"
#include "Shader.h"

class Animation
{
public:
	Animation() = default;

	void Initialize(Image& new_sprite, Mesh& new_shape, int new_count, Shader& new_shader);
	void Animate(float dt);
	void ChangeAnimation(const std::filesystem::path& new_sprite, int new_count);
	Texture spriteSheet;
private:
	Mesh shape;
	Shader shader;
	int frameCount;
	int frameIndex = 0;
	float animateSpeed;
	float baseTime = 0.0f;
};
