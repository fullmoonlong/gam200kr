/**************************************************************************************
 *	File Name        : ParticleGenerator.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Particle.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "VerticesDescriptionLayout.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

class ParticleGenerator {
public:
	void CreateParticles(int total_particle, vec2<float> position, vec2<float> velocity, float life_time) noexcept;
	void UpdateParticles(float dt);

	void DrawParticles();

	void SetNDC(mat3<float> camera_to_ndc) { ndc = camera_to_ndc * transform.GetModelToWorld(); }
private:
	unsigned int FirstUnusedParticle();
	void         RespawnParticle(Particle& particle, vec2<float> offset);
private:
	mat3<float> ndc;

	std::vector<Particle> particles;
	unsigned int totalParticles;
	unsigned int respawnParticles = 2;
	unsigned int lastUsedParticle = 0;

	VerticesDescription layout = Layout::point_texturecoordinate();
	Shader    shader;
	Vertices  vertices;
	Texture   texture;
	Transform transform;
};
