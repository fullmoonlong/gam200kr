/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: VerticesDescription.h
 *	
 *	Vertices description
 *	
 *	2019/10/31
 */

#pragma once
#include <vector>

class [[nodiscard]] VerticesDescription
{
public:
	enum class Type
	{
		Point,
		Color,
		TextureCoordinate
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

	VerticesDescription(std::initializer_list<Type> fields) noexcept;

	unsigned GetVertexSize() const noexcept;

	void EnableAttributes() const noexcept;
	
private:
	unsigned vertexSize = 0;
	std::vector<TypeDescription> typeDescription{};
	std::vector<Type> types{};
};
