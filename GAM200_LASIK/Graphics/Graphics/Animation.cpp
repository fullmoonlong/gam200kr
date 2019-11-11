/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.hpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#include <GL/glew.h>
#include "Animation.hpp"
#include "Image.hpp"

void Animation::Initialize(Image& new_sprite, Mesh& new_shape, int new_count, Shader& new_shader)
{
	shader = new_shader;
	spriteSheet.LoadTextureFrom(new_sprite);
	shape = new_shape;
	frameCount = new_count;
	animateSpeed = 50.0f;
}

Animation::Animation(Image& new_sprite, Mesh& new_shape, int new_count, Shader& new_shader)
{
	Initialize(new_sprite, new_shape, new_count, new_shader);
}

void Animation::Animate(float dt)
{
	glBindTexture(GL_TEXTURE_2D, spriteSheet.GetTexturehandle());
	shader.SendUniformVariable("frameX", frameCount);
	shader.SendUniformVariable("frameIndex", frameIndex);
	shader.SendUniformVariable("correction", 0.003f);
	
	frameIndex = int(baseTime) % frameCount;
	baseTime += animateSpeed * dt;
}

void Animation::ChangeAnimation(const std::filesystem::path& /*new_sprite*/, int /*new_count*/)
{
	//spriteSheet.LoadTextureFrom(new_sprite);
	//textureCoord.clear();
	//frameCount = new_count;
	//float oneSide = 1.0f / (float)frameCount;
	//const float correction = 0.0005f * frameCount;	//this number hide the texture coordinate error
	//for (int i = 0; i <= frameCount; ++i)
	//{
	//	textureCoord.push_back((float)i * oneSide - correction);
	//}
}
