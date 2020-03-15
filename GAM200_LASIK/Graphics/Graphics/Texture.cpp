/**************************************************************************************
 *	File Name        : Texture.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "GL/glew.h"
#include "Image.hpp"
#include "Texture.hpp"
#include "PATH.hpp"

Texture::Texture(Image& image)
{
	LoadTextureFrom(image);
}


bool Texture::LoadTextureFrom(const std::filesystem::path& image_path) noexcept
{
	Image image;

	if (!image.LoadFrom(image_path))
	{
		return false;
	}
	return LoadTextureFrom(image);
}

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelPointer());
	
	return true;
}

void Texture::Bind() noexcept {
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}

void Texture::UnBind() noexcept {
	glBindTexture(GL_TEXTURE_2D, 0);
}