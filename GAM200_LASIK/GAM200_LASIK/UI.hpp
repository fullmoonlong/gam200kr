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

class HealthBar{
public:
	void Initialize(vec2<float> position_, int health);
	void Update(vec2<float> position_, int health);

	Material material;
	Transform transform;
	Mesh mesh;
	
private:
	/*int			hp = 50;
	Draw		allyDraw, enemyDraw;
	Object		allyUnit, enemy;
	Mesh		allyUnitMesh, enemyMesh;
	Shader		allyUnitShader, enemyShader;
	Vertices	allyUnitVertices, enemyVertices;
	Material	allyUnitMaterial, enemyMaterial;*/

	float totalSizeX = 56.f;
	float fullHP = 0;
	float currentHP = 0;
	vec2<float> size = { totalSizeX, 8.f};

	const Color4f color{ 0.8f, 0.0f, 0.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
};

class SelectRespawn {

public:
	void SelectMenu(/*vec2<float> selectPosition*/);
	void SelectUpdate();

	Material	selectMaterial, archerMaterial, knightMaterial, magicianMaterial;
	Transform	selectTransform, archerTransform, knightTransform, magicianTransform;
	Texture		archerTexture, knightTexture, magicianTexture;
	Shader		selectShader, archerShader, knightShader, magicianShader;
private:
	vec2<float> selectSize = { 2500.0f, 400.0f };
	vec2<float> archerSize = { 100.0f, 100.0f };
	
	vec2<float> archerPosition =   { -1000.0f, -500.0f };
	vec2<float> knightPosition =   { -600.0f, -500.0f };
	vec2<float> magicianPosition = { -200.0f, -500.0f };
	
	
	const Color4f color{ 0.0f, 0.0f, 1.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	VerticesDescription texturelayout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	
	//Application::view view;
	Camera			camera;
	CameraView		view;
	Mesh		selectMesh, archerMesh, knightMesh, magicianMesh;

};

class UI :public SelectRespawn, public HealthBar {
};