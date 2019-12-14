/**************************************************************************************
 *	File Name        : Text.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <string>
#include <unordered_map>
#include "Mesh.h"
#include "Vertices.h"
#include "BitmapFont.hpp"

class BitmapFont;

class [[nodiscard]] Text
{
public:
	Text() = default;
	Text(std::wstring text_string, const BitmapFont & text_font) noexcept;

	std::vector<std::pair<const Vertices*, const Texture*>> GetPairOfVerticesAndTextures() const noexcept;

	void SetString(const std::wstring & text_string) noexcept;
	void SetFont(const BitmapFont & text_font) noexcept;

	std::wstring GetString() const noexcept { return string; };
	const BitmapFont* GetFont() const noexcept { return font; };
private:
	void InitializeWithEmptyVertices() const noexcept;
	void BuildNewMeshesIfNeeded() const noexcept;
private:
	mutable bool needNewMeshes = true;
	std::wstring string;
	const BitmapFont* font = nullptr;
	mutable std::unordered_map<int, Vertices> vertices;
};
