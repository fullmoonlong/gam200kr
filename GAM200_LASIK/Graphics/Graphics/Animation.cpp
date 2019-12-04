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
	shader.SendUniformVariable("frameY", spriteSheet.frameY);
	shader.SendUniformVariable("frameIndex", frameIndex);
	
	frameIndex = int(baseTime) % 15;
	baseTime += spriteSheet.animateSpeed * dt;
}

void Animation::ChangeAnimation(int new_count)
{
	spriteSheet.frameX = new_count;
}
