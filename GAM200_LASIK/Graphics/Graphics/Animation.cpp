/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.cpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#include "Animation.hpp"

void Animation::Initialize(SpriteSheet new_sheet, const Shader& new_shader)
{
	spriteSheet = new_sheet;
	shader = new_shader;
}

void Animation::Animate(float dt)
{
	Shader::UseShader(shader);
	shader.SendUniformVariable("frameX", spriteSheet.frameX);
	shader.SendUniformVariable("frameIndex", frameIndex);
	shader.SendUniformVariable("correction", 0.003f);
	
	frameIndex = int(baseTime) % spriteSheet.frameX;
	baseTime += spriteSheet.animateSpeed * dt;
}

void Animation::ChangeAnimation(int new_count)
{
	spriteSheet.frameX = new_count;
}
