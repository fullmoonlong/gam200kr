#include "../external/math_lib/include/vec2.hpp"
#include "Transform.h"

struct MassData {
	float mass;
	float inv_mass;

	// For rotations (not covered in this article)
	float inertia;
	float inverse_inertia;
};

class Body : public Component {
public:
	Body();
	~Body();
	
	friend class Physics;

	unsigned int BodyID = 0;
	void Update(float dt);

	Transform* tx;

	Math::vec2<float> m_force;
	Math::vec2<float> m_gravity;
	Math::vec2<float> m_velocity;
	Math::vec2<float> m_force;
	
	MassData mass_data;
	float gravityScale;
};