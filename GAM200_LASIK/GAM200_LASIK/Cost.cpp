/**************************************************************************************
 *	File Name        : Cost.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Cost.hpp"
#include "PATH.hpp"

void Cost::Initialize()
{
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	
	text.SetFont(bitmapfont);
	costText.SetFont(bitmapfont);

	text.SetString(L"Mana ");
	costText.SetString(std::to_wstring(cost));

	textTransform.SetScale(fontSize);
	costTextrasnform.SetScale(fontSize);

	textTransform.SetTranslation(textPosition);
	costTextrasnform.SetTranslation(costTextPosition);
}

void Cost::CostUpdate(Camera& camera_, CameraView& view_, float dt)
{
	cost += dt;

	const mat3<float> textNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * textTransform.GetModelToWorld();
	Draw::DrawText(shader, textNDC, text);

	costText.SetString(std::to_wstring(static_cast<int>(cost)));
	const mat3<float> costTextNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * costTextrasnform.GetModelToWorld();
	Draw::DrawText(shader, costTextNDC, costText);

}