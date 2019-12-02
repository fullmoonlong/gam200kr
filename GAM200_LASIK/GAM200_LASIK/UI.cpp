#include "UI.hpp"
#include "PATH.hpp"
/*
Name: Wonju Cho
Creation Date : 11/14/2019
*/

void HealthBar::Initialize(vec2<float> position_, int health)
{
	mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	material.vertices.InitializeWithMeshAndLayout(mesh, layout);
	//material.texture.LoadFromPath(PATH::hpbar);

	vec2<float> hpBarPosition = { position_.x, position_.y + 40.f };
	transform.SetTranslation(hpBarPosition);
	transform.SetScale(size);

	fullHP = health;
}

void HealthBar::Update(vec2<float> position_, int health)
{
	vec2<float> hpBarPosition = { position_.x, position_.y + 40.f };
	transform.SetTranslation(hpBarPosition);

	currentHP = health / fullHP * 100;
	size.x = totalSizeX * currentHP / 100.f;
	transform.SetScale(size);
}

//void SelectRespawn::SelectMenu(/*vec2<float> selectPosition*/)
//{
//	//selectMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
//	archerMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
//	knightMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
//	magicianMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
//	
//	//selectShader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
//	archerShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
//	knightShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
//	magicianShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
//	
//	//selectMaterial.vertices.InitializeWithMeshAndLayout(selectMesh, layout);
//	
//	archerMaterial.vertices.InitializeWithMeshAndLayout(archerMesh, texturelayout);
//	archerMaterial.texture.LoadFromPath(PATH::archer_menu);
//
//	knightMaterial.vertices.InitializeWithMeshAndLayout(knightMesh, texturelayout);
//	knightMaterial.texture.LoadFromPath(PATH::knight_menu);
//
//	magicianMaterial.vertices.InitializeWithMeshAndLayout(magicianMesh, texturelayout);
//	magicianMaterial.texture.LoadFromPath(PATH::magician_menu);
//	
//	//selectTransform.SetTranslation(selectPosition);
//	//selectTransform.SetScale(selectSize);
//	archerTransform.SetTranslation(archerPosition);
//	archerTransform.SetScale(archerSize);
//	knightTransform.SetTranslation(knightPosition);
//	knightTransform.SetScale(archerSize);
//	magicianTransform.SetTranslation(magicianPosition);
//	magicianTransform.SetScale(archerSize);
//}
//
//void SelectRespawn::SelectUpdate() {
//	
//
//	Draw::DrawWithNoTexture(selectShader, selectMaterial.vertices);
//	const mat3<float> ndc1 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * archerTransform.GetModelToWorld();
//	selectShader.SendUniformVariable("ndc", ndc1);
//
//	Draw::draw(archerShader, archerMaterial);
//	const mat3<float> ndc2 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * archerTransform.GetModelToWorld();
//	archerShader.SendUniformVariable("ndc", ndc2);
//
//	Draw::draw(knightShader, knightMaterial);
//	const mat3<float> ndc3 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * knightTransform.GetModelToWorld();
//	knightShader.SendUniformVariable("ndc", ndc3);
//
//	Draw::draw(magicianShader, magicianMaterial);
//	const mat3<float> ndc4 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * magicianTransform.GetModelToWorld();
//	magicianShader.SendUniformVariable("ndc", ndc4);
//
//}