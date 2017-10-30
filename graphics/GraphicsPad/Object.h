#pragma once
#include "ShaderInfo.h"

class Object {
protected:
	Shapedata geometry;
	glm::vec3 position;
	ShaderInfo* shader;
	GLuint ObjectID;
	GLuint NumIndicesBufferOffset;
	
public:
	Object(Shapedata shapedata, glm::vec3 Pos = glm::vec3()) :
		geometry(shapedata), position(Pos),shader(nullptr),ObjectID(0), NumIndicesBufferOffset(0){}

	ShaderInfo* getShaderInfo() const { return shader; }
	GLuint getObjectID() const { return ObjectID; }
	Shapedata getGeometry() const { return geometry; }
	GLuint getIndicesBufferOffset() const { return NumIndicesBufferOffset; }
};
