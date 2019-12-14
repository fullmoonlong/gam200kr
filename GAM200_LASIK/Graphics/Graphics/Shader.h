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

class [[nodiscard]] Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
	unsigned GetHandleToShader() const noexcept;

	static void UseShader(const Shader& shader);
	static void UseNothing();

	void SendUniformVariable(const char* variable_name, const int& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const float& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const mat3<float>& matrix) const noexcept;

	bool LoadShapeShader() noexcept;
	bool LoadTextureShader() noexcept;
	bool LoadAnimationShader() noexcept;
	bool LoadShaderFrom(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
private:
	unsigned int handleToShader = 0;
};
