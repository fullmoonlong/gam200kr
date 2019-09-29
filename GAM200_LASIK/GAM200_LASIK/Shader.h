#pragma once
#include <string>

class Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	bool LoadShader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	unsigned GetHandleToShader();
	unsigned int VBO = 0, VAO = 0;
private:
	unsigned handleToShader = 0;
};

