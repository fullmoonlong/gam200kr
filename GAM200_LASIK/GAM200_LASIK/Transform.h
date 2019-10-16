#include"Component.h"
#include "../external/math_lib/include/vec2.hpp"

class Transform : public Component {
public:
	Transform() : Component(ComponentType::CP_TRANSFORM)
	{
		T_position.x = 0.f; T_position.y = 0.f;
		scale.x = 1.f; scale.y = 1.f;
	}

	Math::vec2<float> GetPosition() { return T_position; }
	void SetPosition(float x, float y) { T_position.x = x; T_position.y = y; }
	void SetPosition(const Math::vec2<float> pos) { T_position = pos; }

	Math::vec2<float> GetScale() { return scale; }
	void SetScale(const Math::vec2<float> sca) { scale = sca; }
	void SetScale(float x, float y) { scale.x = x; scale.y = y; }

	Math::vec2<float> T_position;
	Math::vec2<float> scale;
};