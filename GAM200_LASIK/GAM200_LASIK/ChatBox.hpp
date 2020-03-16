/**************************************************************************************
 *	File Name        : ChatBox.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <string>
#include <array>
#include "Material.hpp"
#include "Transform.hpp"
#include "BitmapFont.hpp"
#include "Text.hpp"

class ChatBox {
public:
	void Initialize(mat3<float> world_to_ndc) noexcept;
	void AddHistory(std::wstring message) noexcept;
	void DrawMessageBox() noexcept;
private:
	std::array<std::wstring, 3> history;
	int index = 0;
	mat3<float> worldToNDC;
	
	Color4f chatBoxColor = { 0.0f, 0.36f, 0.56f, 0.6f };
	Material chatBox;
	Shader chatBoxShader;
	Shader textShader;
	Transform chatBoxTransform;
	Transform textTransform;

	BitmapFont bitmapFont;
	Text text;
};
