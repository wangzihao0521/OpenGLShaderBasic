#include <ShapeFactory.h>
#include <glm\glm.hpp>
#include <Vertex.h>

#define NUM_ELEMENT(x) sizeof(x)/sizeof(*x)

Shapedata ShapeFactory::MakeTriangle()
{
	Shapedata data;

	Vertex	Triangle[] =
	{
		glm::vec3(+0.0f,+1.0f,+0.0f),
		glm::vec3(+1.0f,+0.0f,+0.0f),

		glm::vec3(-1.0f,-1.0f,+0.0f),
		glm::vec3(+0.0f,+1.0f,+0.0f),

		glm::vec3(+1.0f,-1.0f,+0.0f),
		glm::vec3(+0.0f,+0.0f,+1.0f)
	};

	data.numVertices = NUM_ELEMENT(Triangle);
	data.vertices = new Vertex[data.numVertices];
	memcpy(data.vertices, Triangle, sizeof(Triangle));

	GLushort Indices[] =
	{
		0,1,2
	};

	data.numIndices = NUM_ELEMENT(Indices);
	data.Indices = new GLushort[data.numIndices];
	memcpy(data.Indices, Indices, sizeof(Indices));

	return data;

}