/**************************************************************************************
 *	File Name        : Logo.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "LevelSystem.h"
#include "OpenGLWindow.hpp"
#include "EventHandler.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "Draw.hpp"

class Logo : public LevelSystem {
public:
	Logo(OpenGLWindow* window);
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
private:
	OpenGLWindow* windowPointer;
	Camera camera;
	CameraView view;
	mat3<float> wolrdToNDC;
	float time;
private:
	Material  digipenLogo;
	Material  fmodLogo;
	Material  teamLogo;
	Transform transform;
	Transform digipenLogoTransform;
	Transform fmodLogoTransform;
	Transform teamLogoTransform;
};
