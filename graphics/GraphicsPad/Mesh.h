#pragma once
#include "GL\glew.h"
#include "ShapeData.h"

struct Mesh{
	Shapedata geometry;
	GLint GeometryID;
	GLint VertexBufferID;
	GLint indicesBufferID;

public:
	Mesh(Shapedata geo) :
		geometry(geo), GeometryID(0), VertexBufferID(0), indicesBufferID(0){};
};