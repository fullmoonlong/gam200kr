/**************************************************************************************
 *	File Name        : UI.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#pragma once


#include "Mesh.h"
#include "Draw.hpp"
#include "Transform.hpp"
#include "Vertices.h" 
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Text.hpp"
#include "GetInput.hpp"
#include "BitmapFont.hpp"
class HealthBar {
public:
	void Initialize(vec2<float> position_, int health);
	void Update(vec2<float> position_, int health);

	Material material;
	Transform transform;
	Mesh mesh;

private:

	float totalSizeX = 56.f;
	float fullHP = 0.f;
	float currentHP = 0.f;
	vec2<float> size = { totalSizeX, 8.f };

	const Color4f color{ 0.8f, 0.0f, 0.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
};

class SelectSpawn {

public:
	void SelectMenu();
	void SelectUpdate(Camera& camera_, CameraView& view_);
	void SetFont(const BitmapFont& font);
	//bool MouseCollide(vec2<float>& mouse_position, Transform transform_/*, int width, int height*/);

private:
	Text m_text, unitFont;
	BitmapFont bitmapfont;
	vec2<float> selectSize = { 2500.0f, 400.0f };
	vec2<float> archerSize = { 128.0f, 128.0f };
	vec2<float> fontSize = { 1.5f };
	vec2<float> unitFontSize = { 1.0f };

	vec2<float> archerPosition = { -220.0f, -250.0f };
	vec2<float> knightPosition = { 20.0f, -250.0f };
	vec2<float> magicianPosition = { 250.0f, -270.0f };
	vec2<float> fontPosition = { -540.0f, 280.0f };
	vec2<float> unitFontPosition = { -250.0f, -350.0f };


	const Color4f color{ 0.0f, 0.0f, 1.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	VerticesDescription texturelayout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	
	Shader		shader;
	Material	selectMaterial, archerMaterial, knightMaterial, magicianMaterial;
	Transform	selectTransform, archerTransform, knightTransform, magicianTransform, fontTransform, unitFontTransform;
	Mesh		selectMesh, archerMesh, knightMesh, magicianMesh, fontMesh;

};

class UI :public SelectSpawn, public HealthBar {
};