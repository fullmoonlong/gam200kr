/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Image.cpp
*	
*	Image class that load from image file
*	
*	2019/10/07
*/

#include <graphic/Image.hpp>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Image::ResizePixelSize(int image_width, int image_height) noexcept
{
	assert(image_width > 0 || image_height > 0);
	width = image_width;
	height = image_height; 

	pixels.resize((width + 1) * (height + 1));	// To avoid warning
}

bool Image::LoadFrom(const std::filesystem::path& source) noexcept
{
	int channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(source.generic_string().c_str(), &width, &height, &channel, 4);

	if (image != nullptr)
	{
		for (int i = 0; i < width * height; i++)
		{
			Color4uc color(image[i * 4], image[i * 4 + 1], image[i * 4 + 2], image[i * 4 + 3]);
			pixels.push_back(color);
		}
		return true;
	}
	stbi_image_free(image);
	return false;
}

int Image::GetWidth() const noexcept
{
	return width;
}

int Image::GetHeight() const noexcept
{
	return height;
}

Color4uc* Image::GetPixelPointer() noexcept
{
	return &pixels.front();
}

const Color4uc* Image::GetPixelPointer() const noexcept
{
	return &pixels.front();
}
