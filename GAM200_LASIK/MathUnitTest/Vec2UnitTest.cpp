/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: PATH.hpp
*	
*	namespace PATH that has all filesystem paths
*	
*	2019/11/01
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <vec2.hpp>
#include <ANGLE.hpp>

namespace
{
	constexpr auto e = std::numeric_limits<float>::epsilon();
}

TEST_CASE("Arithmetic operators", "[vec2]")
{

	const vec2<float> v1{ 1.3f, 3.2f };
	const vec2<float> v2{ 2.2f, 6.5f };
	vec2<float> result;
	SECTION("v1 + v2")
	{
		const vec2<float> answer{ 3.5f, 9.7f };
		result = v1 + v2;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("v1 - v2")
	{
		const vec2<float> answer{ -0.9f, 9.7f };
		result = v1 - v2;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("v2 - v1")
	{
		const vec2<float> answer{ 0.9f, 3.3f };
		result = v2 - v1;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("v1 * 5")
	{
		const vec2<float> answer{ 6.5f, 16.0f };
		result = v1 * 5.0f;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("v1 / 2")
	{
		const vec2<float> answer{ 0.65f, 1.6f };
		result = v1 / 2.0f;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
}

TEST_CASE("Logical operators")
{
	vec2<float> v{ 1.3f, 1.0f };
	vec2<float> result;
	SECTION("-v")
	{
		const vec2<float> answer{ -1.3f, -1.0f };
		result = -v;
		// REQUIRE((r.x == -1.3f && r.y == -1.0f));
		REQUIRE((abs(result.x - answer.x) <= e && abs(result.y - answer.y) <= e));
	}
	SECTION("v == { 1.3f, 1.0f }")
	{
		bool isSame = (v == vec2<float>{ 1.3f, 1.0f });
		REQUIRE(isSame == true);
	}
	SECTION("v != { 1.3f, 2.0f }")
	{
		bool isNotSame = (v != vec2<float>{ 1.3f, 2.0f });
		REQUIRE(isNotSame == true);
	}
}

TEST_CASE("Arithmetic with assign operators")
{
	vec2<float> v{ 0.8f, 1.3f };
	vec2<float> result{ 0.0f };
	SECTION("r += { 0.8f, 1.3f }")
	{
		const vec2<float> answer{ 0.8f, 1.3f };
		result += v;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("r -= { 0.8f, 1.3f }")
	{
		const vec2<float> answer{ 0.0f, 0.0f };
		result -= v;
		REQUIRE((abs(r.x - answer.x) <= e && abs(r.y - answer.y) <= e));
	}
	SECTION("v *= 2")
	{
		const vec2<float> answer{ 1.6f, 2.6f };
		v *= 2.0f;
		REQUIRE((abs(v.x - answer.x) <= e && abs(v.y - answer.y) <= e));
	}
	SECTION("v /= 2")
	{
		const vec2<float> answer{ 0.8f, 1.3f };
		v /= 2.0f;
		REQUIRE((abs(v.x - answer.x) <= e && abs(v.y - answer.y) <= e));
	}
}

TEST_CASE("Other functions", "[vec2]")
{
	const vec2<float> v1{ 1.2f, 1.5f };
	const vec2<float> v2{ 0.8f, 1.3f };
	SECTION("Dot Product")
	{
		const float result = dot_product(v1, v2);
		REQUIRE(abs(result - 2.91f) <= e * 2);
	}
	SECTION("Magnitude Squared")
	{
		const float result = magnitude_squared(v1);
		REQUIRE(abs(result - 3.69f) <= e);
	}
	SECTION("Manitude")
	{
		REQUIRE(abs(magnitude(v1) - 1.920937271229855f) <= e);
	}
	SECTION("Distance Between")
	{
		REQUIRE(abs(distance_between(v1, v2) - 0.4472135954999579f) <= e);
	}
	SECTION("Angle Between")
	{
		const float result = angle_between(vec2<float>{ 1.0f, 1.0f }, { 0.0f, 1.0f });
 		REQUIRE(abs(result - ANGLE::pi / 4) <= e);
	}
	SECTION("Rotate By")
	{
		vec2<float> rotate = rotate_by(ANGLE::pi, v1);
		vec2<float> result = { -1.2f, -1.5f };
		REQUIRE((abs(rotate.x - result.x) <= e && abs(rotate.y - result.y) <= e));
	}
	SECTION("Normalize")
	{
		vec2<float> norm = normalize(v1);
		vec2<float> result = { 0.6246950475544241f, 0.7808688094430302f };
		REQUIRE((abs(norm.x - result.x) <= e && abs(norm.y - result.y) <= e));
	}
}
