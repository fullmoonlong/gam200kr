#pragma once 
#include "Application.h" 
#include "vec2.h" 



struct AABB {

	MathLibrary::vec2 min;
	MathLibrary::vec2 max;
};

struct Circle {
	float radius;
	MathLibrary::vec2 position;
};

class Physics_object {
	Physics_object();
	Physics_object(const MathLibrary::vec2& xPosition, float mass, float width, float height);
	~Physics_object();

	void Initialize(const MathLibrary::vec2& xPosition, float mass);
	void Update(float dt);

	void Acceleration(const MathLibrary::vec2& F, float dt);
	bool Unmove() const { return (m_mass < 0.0001f); }

	float& GetMass() { return m_mass; }
	float& GetInverseMass() { return m_inverseMass; }

	float GetMass()        const { return m_mass; }
	float GetInverseMass() const { return m_inverseMass; }

	const MathLibrary::vec2& GetPosition() const { return m_xPosition; }
	const MathLibrary::vec2& GetDisplacement() const { return m_xDisplacement; }

protected:
	float m_inverseMass;
	float m_mass;

	MathLibrary::vec2 m_xPosition;
	MathLibrary::vec2 m_xDisplacement;
};

class GravityOb :public Physics_object {

};

class Static_physisOb : Physics_object {

};