/**************************************************************************************
 *	File Name        : Shader.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <filesystem>
#include "mat3.hpp"
#include "vec2.hpp"

class Color4f;

class [[nodiscard]] Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
	unsigned GetHandleToShader() const noexcept;

	void Use() noexcept;
	void UnUse() noexcept;

	void SendUniformVariable(const char* variable_name, const int& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const float& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const mat3<float>& matrix) const noexcept;
	void SendUniformVariable(const char* variable_name, const vec2<float>& vector) const noexcept;
	void SendUniformVariable(const char* variable_name, const Color4f& color) const noexcept;

	bool LoadShapeShader() noexcept;
	bool LoadTextureShader() noexcept;
	bool LoadAnimationShader() noexcept;
	bool LoadShaderFrom(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
private:
	unsigned int handleToShader = 0;
};
