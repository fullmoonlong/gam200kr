
#include "CoolDown.hpp"
#include "PATH.hpp"

//void CoolDown::Initialize()
//{
//	textureShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
//
//	const Mesh mesh = MESH::create_rectangle({ 0.0f }, { 1.0f });
//	knightCoolMesh = mesh;
//	magicianCoolMesh = mesh;
//	archerCoolMesh = mesh;
//
//	knightCoolMaterial.shader = animationShader;
//	knightCoolMaterial.vertices.InitializeWithMeshAndLayout(knightCoolMesh, texturelayout);
//	knightCoolMaterial.texture.LoadFromPath(PATH::two);
//	knightCoolTransform.SetTranslation(coolKnightPosition);
//	knightCoolTransform.SetScale(size);
//
//
//	magicianCoolMaterial.shader = animationShader;
//	magicianCoolMaterial.vertices.InitializeWithMeshAndLayout(magicianCoolMesh, texturelayout);
//	magicianCoolMaterial.texture.LoadFromPath(PATH::four);
//	magicianCoolTransform.SetTranslation(coolMagicianPosition);
//	magicianCoolTransform.SetScale(size);
//
//
//	archerCoolMaterial.shader = animationShader;
//	archerCoolMaterial.vertices.InitializeWithMeshAndLayout(archerCoolMesh, texturelayout);
//	archerCoolMaterial.texture.LoadFromPath(PATH::three);
//	archerCoolTransform.SetTranslation(coolArcherPosition);
//	archerCoolTransform.SetScale(size);
//
//}

void CoolDown::Initialize(const Camera& camera_, const CameraView& view_) {
	animationShader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);

	const Mesh mesh = MESH::create_rectangle({ 0.0f }, { 1.0f });
	knightCoolMesh   = mesh;
	archerCoolMesh   = mesh;
	magicianCoolMesh = mesh;

	knightCoolMaterial.shader   = animationShader;
	archerCoolMaterial.shader   = animationShader;
	magicianCoolMaterial.shader = animationShader;

	knightCoolMaterial.vertices.InitializeWithMeshAndLayout(knightCoolMesh, texturelayout);
	archerCoolMaterial.vertices.InitializeWithMeshAndLayout(archerCoolMesh, texturelayout);
	magicianCoolMaterial.vertices.InitializeWithMeshAndLayout(magicianCoolMesh, texturelayout);

	knightCoolMaterial.texture.LoadFromPath(PATH::twocountdown);
	archerCoolMaterial.texture.LoadFromPath(PATH::threecountdown);
	magicianCoolMaterial.texture.LoadFromPath(PATH::fourcountdown);

	knightCoolTransform.SetTranslation(coolKnightPosition);
	knightCoolTransform.SetScale(size);
	magicianCoolTransform.SetTranslation(coolMagicianPosition);
	magicianCoolTransform.SetScale(size);
	archerCoolTransform.SetTranslation(coolArcherPosition);
	archerCoolTransform.SetScale(size);

	knightAnimation.Initialize({ 2, 1, 1.0f }, animationShader);
	archerAnimation.Initialize({ 3, 1, 1.0f }, animationShader);
	magicianAnimation.Initialize({ 4, 1, 1.0f }, animationShader);


	const mat3<float> worldToNDC = view_.GetCameraToNDCTransform() * camera_.WorldToCamera();
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
