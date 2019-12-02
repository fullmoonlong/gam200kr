/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Hierarchy.cpp
 *	
 *	Graphic demo main file
 *	
 *	Dec.2 2019
 *******************************************************/

#pragma once
#include "Demo.hpp"

class HierarchyDemo : public Demo
{
public:
	explicit HierarchyDemo(Window& window) : Demo(window) { Initialize(); }

	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;
private:

};

