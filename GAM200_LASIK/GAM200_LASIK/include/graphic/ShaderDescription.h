/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: ShaderDescription.h
*	
*	Shader description
*	
*	2019/10/04
*/

#pragma once
#include <vector>

class [[nodiscard]] ShaderDescription
{
public:
	enum Type
	{
		Point,
		Color,
		TextCoordinate
	};

	struct TypeDescription
	{
		unsigned int elementsNumber = 0;
		unsigned int elementsType = 0;
		unsigned int sizeInBytes = 0;
		bool shouldNormalize = false;
	};

	void AddType(Type type) noexcept;
	const std::vector<Type>& GetTypes() const noexcept;

	ShaderDescription(std::initializer_list<Type> fields) noexcept;

	unsigned GetVertexSize() const noexcept;

	void EnableAttributes() const noexcept;
	
private:
	unsigned vertexSize = 0;
	std::vector<TypeDescription> typeDescription{};
	std::vector<Type> types{};
	
};
