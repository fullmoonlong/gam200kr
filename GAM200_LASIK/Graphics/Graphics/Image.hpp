/**************************************************************************************
 *	File Name        : Image.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <vector>
#include <filesystem>
#include "Color4f.hpp"
#include "ColorInChar.hpp"

class [[nodiscard]] Image
{
public:
	Image() = default;
	Image(const std::filesystem::path & source) noexcept;

	void ResizePixelSize(int image_width, int image_height) noexcept;
	bool LoadFrom(const std::filesystem::path & source) noexcept;
	void SaveToPNG(const std::filesystem::path & file_path) const noexcept;

	int GetWidth() const noexcept;
	int GetHeight() const noexcept;

	ColorBit* GetPixelPointer() noexcept;
	const ColorBit* GetPixelPointer() const noexcept;
	int GetPixelsBufferBytesSize() const noexcept;

	void FlipVertically() noexcept;
private:
	int width, height;
	std::vector<ColorBit> pixels{};
};