/**************************************************************************************
 *	File Name        : Cost.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Draw.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Text.hpp"
#include "BitmapFont.hpp"

class Cost {
public:
	void Initialize();
	void CostUpdate(Camera& camera_, CameraView& view_, float dt);
	
	float  GetCost() { return cost; }
	void AddCost(float cost_) { cost += cost_; }

private:
	float cost = 0;

	vec2<float> textPosition = { -150.f, 0.f};
	vec2<float> costTextPosition = { 30.f, 0.f};

	vec2<float> fontSize = { 1.5f };

	Camera		camera;
	CameraView    view;

	Shader		   shader;
	BitmapFont bitmapfont;
	Text	   text, costText;
	Transform	textTransform, costTextrasnform;
};