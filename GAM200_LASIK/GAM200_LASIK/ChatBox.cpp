/**************************************************************************************
 *	File Name        : ChatBox.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <GL/glew.h>
#include "ChatBox.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Draw.hpp"
#include "PATH.hpp"

void ChatBox::Initialize(mat3<float> world_to_ndc) noexcept {
	worldToNDC = world_to_ndc;
	chatBoxShader.LoadShapeShader();
	textShader.LoadTextShader();
	chatBoxTransform.SetTranslation({ -430.0f, -250.0f });
	chatBoxTransform.SetScale({ 330.0f, 170.0f });
	textTransform.SetTranslation({ -430.0f, -250.0f });
	chatBox.CreateShape(chatBoxShader, MESH::create_rectangle({ 0.0f }, { 1.0f }, chatBoxColor), worldToNDC * chatBoxTransform.GetModelToWorld());
	bitmapFont.LoadFromFile(PATH::bitmapfont_fnt);
	text.SetFont(bitmapFont);
}

void ChatBox::AddHistory(std::wstring message) noexcept {
	if (index == 3) {
		history.at(2) = history.at(1);
		history.at(1) = history.at(0);
		history.at(0) = message;
	}
	else {
		history.at(index) = message;
		++index;
	}
}

void ChatBox::DrawMessageBox() noexcept {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Draw::DrawShape(chatBox);
	glDisable(GL_BLEND);
	if (index != 0) {
		std::wstring something;
		for (int i = 0; i < index; ++i) {
			something += history.at(i) + L'\n';
		}
		something.pop_back();
		text.SetString(something);
		Draw::DrawText(textShader, worldToNDC * textTransform.GetModelToWorld(), text);
	}
}
