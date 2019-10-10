/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Texture.cpp
*	
*	Texture of the sprite
*	
*	2019/10/07
*/


#include "Image.hpp"
#include "Texture.hpp"
#include <GL/glew.h>


bool Texture::LoadTextureFrom(const Image& image) noexcept
{
	if (GetTexturehandle() != 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &textureHandle);
	}

	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelPointer());
	
	return true;
}
