/**************************************************************************************
 *	File Name        : ParticleGenerator.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "GL/glew.h"
#include "ParticleGenerator.hpp"
#include "Mesh.h"

void ParticleGenerator::CreateParticles(int total_particle, vec2<float> position, vec2<float> velocity, float life_time) noexcept
{
	totalParticles = total_particle;
	shader.LoadShaderFrom("../assets/shader/particle.vert", "../assets/shader/particle.frag");

	Mesh particleMesh = MESH::create_rectangle({ 0.f }, {1.0f}, { 1.0f, 0.f, 0.f, 1.0f });
	vertices.InitializeWithMeshAndLayout(particleMesh, layout);

	Particle p(position, velocity, life_time);

	for (unsigned int i = 0; i < totalParticles; ++i) {
		particles.push_back(p);
	}

	texture.LoadTextureFrom("../assets/sprite/awesomeface.png");
	transform.SetScale({ 2.0f });
}

void ParticleGenerator::UpdateParticles(float dt)
{
	for (unsigned int i = 0; i < respawnParticles; ++i) {
		int unusedParticle = FirstUnusedParticle();
		RespawnParticle(particles[unusedParticle], 0.0f);	// offset is something like radius, but in my case, there's no object, so offset is 0.0
	}
	for (unsigned int i = 0; i < totalParticles; ++i) {
		Particle& p = particles[i];
		p.lifeTime -= dt;
		if (p.lifeTime > 0.0f) {
			p.position -= p.velocity * dt;
			p.color.a -= dt * 0.01f;
		}
	}
}

void ParticleGenerator::DrawParticles()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.Use();
	for (Particle particle : particles) {
		if (particle.lifeTime > 0.0f) {
			shader.SendUniformVariable("ndc", ndc);
			shader.SendUniformVariable("offset", particle.position);
			shader.SendUniformVariable("color", particle.color);
			Vertices::SelectVAO(vertices);
			glBindTexture(GL_TEXTURE_2D, texture.GetTexturehandle());
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glBindVertexArray(0);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

unsigned int ParticleGenerator::FirstUnusedParticle()
{
	for (unsigned int i = lastUsedParticle; i < totalParticles; ++i) {
		if (particles[i].lifeTime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (particles[i].lifeTime <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::RespawnParticle(Particle& particle, vec2<float> offset)
{
	float randomX = ((rand() % 100) - 50) / 50.0f;
	float randomY = ((rand() % 100) - 50) / 50.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	//particle.position.x = offset.x + randomX;
	//particle.position.y = offset.y + randomY;

	particle.position = offset;
	particle.velocity = { randomX, randomY };
	particle.color = Color4f{ rColor, rColor, rColor, 1.0f };
	particle.lifeTime = 1.0f;

	//particle.velocity = 1.0f * 0.1f;
}
