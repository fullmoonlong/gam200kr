/**************************************************************************************
 *	File Name        : Units.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Texture.hpp"
#include "Draw.hpp"
#include "Animation.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Transform.hpp"

class CoolDown
{
public:
	void Initialize(const Camera& camera_, const CameraView& view_);
	void CoolDownUpdate(float dt);

	void SetKnightCoolDown();
	void SetArcherCoolDown();
	void SetMagicianCoolDown();
private:
	const float knightCoolTime   = 2.f;
	const float archerCoolTime   = 3.f;
	const float magicianCoolTime = 4.f;

	float knightCoolDown   = knightCoolTime;
	float archerCoolDown   = archerCoolTime;
	float magicianCoolDown = magicianCoolTime;

	bool isKnightCoolDown = false;
	bool isArcherCoolDown = false;
	bool isMagicianCoolDown = false;

	Animation archerAnimation, knightAnimation, magicianAnimation;
	VerticesDescription texturelayout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Shader animationShader, textureShader;
	Mesh knightCoolMesh, magicianCoolMesh, archerCoolMesh;
	Transform knightCoolTransform, magicianCoolTransform, archerCoolTransform;
	Material knightCoolMaterial, magicianCoolMaterial, archerCoolMaterial;

	vec2<float> size = { 50.0f, 50.0f };
	vec2<float> coolKnightPosition		= {    70.f, -225.f };
	vec2<float> coolArcherPosition		= { -150.f, -225.f };
	vec2<float> coolMagicianPosition	= {  300.f, -225.f };
	vec2<float> coolTimeBarPosition		= { -400.f ,-200.f };
};

