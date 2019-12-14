/**************************************************************************************
 *	File Name        : VerticesDescription.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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
