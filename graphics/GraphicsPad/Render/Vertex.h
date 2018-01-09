#pragma once

#include <glm\glm.hpp>

struct Vertex 
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec4 tengent;

	bool operator == (Vertex vertex)
	{
		if (position == vertex.position &&
			color == vertex.color &&
			normal == vertex.normal &&
			uv == vertex.uv &&
			tengent == vertex.tengent)

			return true;
		else
			return false;
	}
};
