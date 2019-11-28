/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.h
 *	
 *	Graphic demo main file
 *	
 *	Nov.25 2019
 *******************************************************/

#pragma  once
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Transform.hpp"
#include "EventHandler.hpp"

class ShapeDrawingDemo : public SimpleEventHandler
{
public:
	void Initialize();
	void Update();
	void ShutDown();
private:
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	Shader shader;

	Camera camera;
	CameraView view;
	
	Mesh rectangle;
	Vertices vertices;
	Transform transform;
	
	Mesh line;
	Vertices lineVertices;
	Transform lineTransform;

	Mesh quad;
	Vertices quadVertices;
	Transform quadTransform;

	Mesh ellipse;
	Vertices ellipseVertices;
	Transform ellipseTransform;

	Mesh triangle;
	Vertices triangleVertices;
	Transform triangleTransform;
};
