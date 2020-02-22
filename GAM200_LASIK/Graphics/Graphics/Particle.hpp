/**************************************************************************************
 *	File Name        : Particle.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <vec2.hpp>
#include "Texture.hpp"
#include "Color4f.hpp"

struct Particle {
	vec2<float> position, velocity;
	Color4f color;
	float lifeTime;

	Particle() : position(0.0f), velocity(0.0f), color(1.0f), lifeTime(0.0f) {}
	Particle(vec2<float> position, vec2<float> velocity, float lifeTime)
		: position(position), velocity(velocity), lifeTime(lifeTime) {}
};