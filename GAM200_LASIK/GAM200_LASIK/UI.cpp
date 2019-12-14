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
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	const Mesh mesh = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);
	archerMesh = mesh;
	knightMesh = mesh;
	magicianMesh = mesh;

	archerMaterial.shader = shader;
	archerMaterial.vertices.InitializeWithMeshAndLayout(archerMesh, texturelayout);
	archerMaterial.texture.LoadTextureFrom(PATH::archer_menu);
	archerTransform.SetTranslation(archerPosition);
	archerTransform.SetScale(archerSize);

	knightMaterial.shader = shader;
	knightMaterial.vertices.InitializeWithMeshAndLayout(knightMesh, texturelayout);
	knightMaterial.texture.LoadTextureFrom(PATH::knight_menu);
	knightTransform.SetTranslation(knightPosition);
	knightTransform.SetScale(archerSize);

	magicianMaterial.shader = shader;
	magicianMaterial.vertices.InitializeWithMeshAndLayout(magicianMesh, texturelayout);
	magicianMaterial.texture.LoadTextureFrom(PATH::magician_menu);
	magicianTransform.SetTranslation(magicianPosition);
	magicianTransform.SetScale(archerSize);

	fontTransform.SetTranslation(fontPosition);
	fontTransform.SetScale(fontSize);

	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	m_text.SetFont(bitmapfont);
	m_text.SetString(L"you can spawn units if you type unit name");
}

void SelectSpawn::SelectUpdate(Camera& camera_, CameraView& view_) {

	archerMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * archerTransform.GetModelToWorld();
	Draw::draw(archerMaterial);

	knightMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * knightTransform.GetModelToWorld();
	Draw::draw(knightMaterial);

	magicianMaterial.ndc = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * magicianTransform.GetModelToWorld();
	Draw::draw(magicianMaterial);

	const mat3<float> ndc5 = view_.GetCameraToNDCTransform() * camera_.WorldToCamera() * fontTransform.GetModelToWorld();
	Draw::DrawText(shader, ndc5, m_text);

}

void SelectSpawn::SetFont(const BitmapFont& font)
{
	m_text.SetFont(font);
}