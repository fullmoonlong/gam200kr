/**************************************************************************************
 *	File Name        : UI.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include "UI.hpp"
#include "PATH.hpp"
#include "CurrencySystem.hpp"

void HealthBar::Initialize(vec2<float> position_, int health)
{
	mesh = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);
	material.vertices.InitializeWithMeshAndLayout(mesh, layout);
	material.texture.LoadTextureFrom(PATH::hpBar);

	vec2<float> hpBarPosition = { position_.x, position_.y + 40.f };
	transform.SetTranslation(hpBarPosition);
	transform.SetScale(size);

	fullHP = (float)health;
}

void HealthBar::Update(vec2<float> position_, int health)
{
	vec2<float> hpBarPosition = { position_.x, position_.y + 40.f };
	transform.SetTranslation(hpBarPosition);
	currentHP = (float)health / fullHP;
	size.x = totalSizeX * currentHP;
	transform.SetScale(size);
}

void SelectSpawn::SelectMenu()
{
	textShader.LoadTextShader();
	textureShader.LoadTextureShader();

	const Mesh mesh = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);
	archerMesh = mesh;
	knightMesh = mesh;
	magicianMesh = mesh;

	archerMaterial.shader = textureShader;
	archerMaterial.vertices.InitializeWithMeshAndLayout(archerMesh, texturelayout);
	archerMaterial.texture.LoadTextureFrom(PATH::archer_menu);
	archerTransform.SetTranslation(archerPosition);
	archerTransform.SetScale(archerSize);

	knightMaterial.shader = textureShader;
	knightMaterial.vertices.InitializeWithMeshAndLayout(knightMesh, texturelayout);
	knightMaterial.texture.LoadTextureFrom(PATH::knight_menu);
	knightTransform.SetTranslation(knightPosition);
	knightTransform.SetScale(archerSize);

	magicianMaterial.shader = textureShader;
	magicianMaterial.vertices.InitializeWithMeshAndLayout(magicianMesh, texturelayout);
	magicianMaterial.texture.LoadTextureFrom(PATH::magician_menu);
	magicianTransform.SetTranslation(magicianPosition);
	magicianTransform.SetScale(archerSize);

	fontTransform.SetTranslation(fontPosition);
	fontTransform.SetScale(fontSize);

	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	m_text.SetFont(bitmapfont);
	m_text.SetString(L"you can spawn units if you type unit name");

	unitFontTransform.SetTranslation(unitFontPosition);
	unitFontTransform.SetScale(unitFontSize);

	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	unitFont.SetFont(bitmapfont);
	unitFont.SetString(L"archer     knight    magician");

}

void SelectSpawn::SelectUpdate(Camera& camera_, CameraView& view_) {
	archerMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * archerTransform.GetModelToWorld();
	Draw::draw(archerMaterial);

	knightMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * knightTransform.GetModelToWorld();
	Draw::draw(knightMaterial);

	magicianMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * magicianTransform.GetModelToWorld();
	Draw::draw(magicianMaterial);

	const mat3<float> ndc5 = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * fontTransform.GetModelToWorld();
	Draw::DrawText(textShader, ndc5, m_text);

	const mat3<float> ndc6 = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * unitFontTransform.GetModelToWorld();
	Draw::DrawText(textShader, ndc6, unitFont);
}

void SelectSpawn::SetFont(const BitmapFont& font)
{
	m_text.SetFont(font);
}

void MoneyBar::Initialize()
{
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	m_text.SetFont(bitmapfont);
	m_text.SetString(L"Gold ");

	moneyTransform.SetTranslation(moneyPosition);
	moneyTransform.SetScale(fontSize);

	numberTransform.SetTranslation(numberPosition);
	numberTransform.SetScale(fontSize);

	number.SetFont(bitmapfont);
	moneyAmount = cs->GetMoney();
	numberString = std::to_wstring(moneyAmount);
	number.SetString(numberString);

}

void MoneyBar::Update(Camera& camera_, CameraView& view_)
{
	const mat3<float> moneyNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * moneyTransform.GetModelToWorld();
	Draw::DrawText(shader, moneyNDC, m_text);

	numberString = std::to_wstring(cs->GetMoney());
	number.SetString(numberString);
	const mat3<float> numberNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * numberTransform.GetModelToWorld();
	Draw::DrawText(shader, numberNDC, number);
}
