/**************************************************************************************
 *	File Name        : CoolDown.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "CoolDown.hpp"
#include "PATH.hpp"

void CoolDown::Initialize(const Camera& camera_, const CameraView& view_) {
	animationShader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);

	const Mesh mesh = MESH::create_rectangle({ 0.0f }, { 1.0f });
	knightCoolMesh   = mesh;
	archerCoolMesh   = mesh;
	magicianCoolMesh = mesh;

	const mat3<float> worldToNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera();
	//knightAnimation.Initialize({2, 1, 1.0f}, animationShader);
	//knightCoolMaterial.CreateAnimation(animationShader, PATH::twocountdown, knightAnimation, worldToNDC * knightCoolTransform.GetModelToWorld());
	
	knightCoolMaterial.shader   = animationShader;
	archerCoolMaterial.shader   = animationShader;
	magicianCoolMaterial.shader = animationShader;

	knightCoolMaterial.vertices.InitializeWithMeshAndLayout(knightCoolMesh, texturelayout);
	archerCoolMaterial.vertices.InitializeWithMeshAndLayout(archerCoolMesh, texturelayout);
	magicianCoolMaterial.vertices.InitializeWithMeshAndLayout(magicianCoolMesh, texturelayout);

	knightCoolMaterial.texture.LoadTextureFrom(PATH::twocountdown);
	archerCoolMaterial.texture.LoadTextureFrom(PATH::threecountdown);
	magicianCoolMaterial.texture.LoadTextureFrom(PATH::fourcountdown);

	knightCoolTransform.SetTranslation(coolKnightPosition);
	knightCoolTransform.SetScale(size);
	magicianCoolTransform.SetTranslation(coolMagicianPosition);
	magicianCoolTransform.SetScale(size);
	archerCoolTransform.SetTranslation(coolArcherPosition);
	archerCoolTransform.SetScale(size);

	knightAnimation.Initialize({ 2, 1, 1.0f }, animationShader);
	archerAnimation.Initialize({ 3, 1, 1.0f }, animationShader);
	magicianAnimation.Initialize({ 4, 1, 1.0f }, animationShader);

	knightCoolMaterial.ndc   = worldToNDC * knightCoolTransform.GetModelToWorld();
	archerCoolMaterial.ndc   = worldToNDC * archerCoolTransform.GetModelToWorld();
	magicianCoolMaterial.ndc = worldToNDC * magicianCoolTransform.GetModelToWorld();
}

void CoolDown::CoolDownUpdate(float dt) {
	if (isKnightCoolDown) {
		knightAnimation.Animate(dt);
		Draw::draw(knightCoolMaterial);
		knightCoolDown -= dt;
		if (knightCoolDown <= 0.0f) {
			knightCoolDown = knightCoolTime;
			isKnightCoolDown = false;
		}
	}
	if (isArcherCoolDown) {
		archerAnimation.Animate(dt);
		Draw::draw(archerCoolMaterial);
		archerCoolDown -= dt;
		if (archerCoolDown <= 0.0f) {
			archerCoolDown = archerCoolTime;
			isArcherCoolDown = false;
		}
	}
	if (isMagicianCoolDown) {
		magicianAnimation.Animate(dt);
		Draw::draw(magicianCoolMaterial);
		magicianCoolDown -= dt;
		if (magicianCoolDown <= 0.0f) {
			magicianCoolDown = magicianCoolTime;
			isMagicianCoolDown = false;
		}
	}
}

bool CoolDown::GetKnightCoolDown()
{
	return isKnightCoolDown;
}

bool CoolDown::GetArcherCoolDown()
{
	return isArcherCoolDown;
}

bool CoolDown::GetMagicianCoolDown()
{
	return isMagicianCoolDown;
}

void CoolDown::SetKnightCoolDown()
{
	isKnightCoolDown = true;
}

void CoolDown::SetArcherCoolDown()
{
	isArcherCoolDown = true;
}

void CoolDown::SetMagicianCoolDown()
{
	isMagicianCoolDown = true;
}
