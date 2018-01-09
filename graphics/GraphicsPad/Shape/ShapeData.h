#pragma once

#include <GL\glew.h>
#include "Render\Vertex.h"

class Shapedata
{
public:
	Shapedata() :
		vertices(0), numVertices(0),
		Indices(0), numIndices(0)
	{}

	GLsizeiptr VertexBufferSize() const
	{
		return (numVertices * sizeof(Vertex));
	}

	GLsizeiptr IndicesBufferSize() const
	{
		return (numIndices * sizeof(GLuint));
	}

	void cleanup()
	{
		delete[] vertices;
		delete[] Indices;
		numVertices = numIndices = 0;

	}

	Vertex* vertices;
	GLuint  numVertices;
	GLushort*  Indices;
	GLuint numIndices;

	bool operator == (Shapedata geometry)
	{
		if (numVertices == geometry.numVertices && numIndices == geometry.numIndices)
		{
			for (unsigned int i = 0; i < numVertices; ++i)
			{
				if (vertices[i] == geometry.vertices[i])
				{
				}
				else
					return false;
			}
			for (unsigned int i = 0; i < numIndices; ++i)
			{
				if (Indices[i] == geometry.Indices[i])
				{
				}
				else
					return false;
			}
		}
		else
			return false;

		return true;
	}

};