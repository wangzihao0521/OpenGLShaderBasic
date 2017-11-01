#pragma once
#include "ShapeData.h"
#include "ShaderInfo.h"
#include "Transform.h"

class Object {
protected:
	Shapedata geometry;
	Transform transform;
	ShaderInfo* shader;
	GLuint NumIndicesBufferOffset;
	
public:
	Object(Shapedata shapedata, Transform trans = Transform()) :
		geometry(shapedata), transform(trans),shader(nullptr),ObjectID(0), NumIndicesBufferOffset(0){}
	void Setposition(glm::vec3 pos) { transform.setPosition(pos); }
	void Setrotaion(glm::vec3 rot) { transform.setRotation(rot); }
	void Setscale(glm::vec3 scale) { transform.setScale(scale); }
	void translate(glm::vec3 Vec3) { transform.tranlate(Vec3); }
	void rotate(glm::vec3 Vec3) { transform.rotate(Vec3); }
	void scale(glm::vec3 Vec3) { transform.scale(Vec3); }
	void setShaderID(GLuint VshaderID, GLuint FshaderID);
	void setProgramID(GLuint programID);
	ShaderInfo* getShaderInfo() const { return shader; }
	GLuint getObjectID() const { return geometry.geometryID; }
	Shapedata getGeometry() const { return geometry; }
	GLuint getIndicesBufferOffset() const { return NumIndicesBufferOffset; }
};
