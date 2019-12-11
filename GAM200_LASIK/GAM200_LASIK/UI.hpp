#pragma once
/*
Name: Wonju Cho
Creation Date : 11/14/2019
*/

//#include"Object.h"
//#include"Units.hpp"
//#include"ObjectFactory.h"

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
	float fullHP = 0;
	float currentHP = 0;
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
	Text m_text;
	BitmapFont bitmapfont;
	vec2<float> selectSize = { 2500.0f, 400.0f };
	vec2<float> archerSize = { 200.0f, 200.0f };
	vec2<float> fontSize = { 2.0f };

	vec2<float> archerPosition = { -400.0f, -400.0f };
	vec2<float> knightPosition = { 0.0f, -400.0f };
	vec2<float> magicianPosition = { 400.0f, -400.0f };
	vec2<float> fontPosition = { -600.0f, -600.0f };


	const Color4f color{ 0.0f, 0.0f, 1.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	VerticesDescription texturelayout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	
	Shader		shader;
	Material	selectMaterial, archerMaterial, knightMaterial, magicianMaterial, fontMaterial;
	Transform	selectTransform, archerTransform, knightTransform, magicianTransform, fontTransform;
	Mesh		selectMesh, archerMesh, knightMesh, magicianMesh, fontMesh;

};

class UI :public SelectSpawn, public HealthBar {
};