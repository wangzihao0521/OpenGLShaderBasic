#pragma once
#include <glm\glm.hpp>

class Transform {
protected:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
public:
	Transform(glm::vec3 pos = glm::vec3(), glm::vec3 rot = glm::vec3(), glm::vec3 scale = glm::vec3(1.0,1.0,1.0) ):
		Position(pos),Rotation(rot),Scale(scale){}
	void setPosition(glm::vec3 pos) { Position = pos; }
	void setRotation(glm::vec3 rot) { Rotation = rot; }
	void setScale(glm::vec3 scale) { Scale = scale; }
	void tranlate(glm::vec3 Vec3) { Position += Vec3; }
	void rotate(glm::vec3 Vec3) { Rotation += Vec3; }
	void scale(glm::vec3 Vec3) { Scale *= Vec3; }
	glm::vec3 getPosition() const { return Position;}
	glm::vec3 getRotation() const { return Rotation; }
	glm::vec3 getScale() const { return Scale; }
};