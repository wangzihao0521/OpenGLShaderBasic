#pragma once
#include <ShapeData.h>

class ShapeFactory
{
public:
	static Shapedata MakeTriangle();
	static Shapedata MakeCube();
};