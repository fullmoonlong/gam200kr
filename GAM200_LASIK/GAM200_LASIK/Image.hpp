/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Image.hpp
*	
*	Image class that load from image file
*	
*	2019/10/07
*/


#pragma once
#include "Color4uc.hpp"
#include "Color4f.hpp"
#include <vector>
#include <filesystem>

class [[nodiscard]]Image
{
public:	
	Image() = default;

	void ResizePixelSize(int image_width, int image_height) noexcept;
	bool LoadFrom(const std::filesystem::path& source) noexcept;

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

	Color4uc* GetPixelPointer() noexcept;
	const Color4uc* GetPixelPointer() const noexcept;
	
private:

	int width, height;
	std::vector<Color4uc> pixels{};
};