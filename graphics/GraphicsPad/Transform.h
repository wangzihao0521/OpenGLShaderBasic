#pragma once
#include <glm\glm.hpp>

using namespace glm;

class Transform {
protected:
	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
public:
	Transform(vec3 pos = vec3(),vec3 rot = vec3(),vec3 scale = vec3(1.0,1.0,1.0) ):
		Position(pos),Rotation(rot),Scale(scale){}
	void setPosition(vec3 pos) { Position = pos; }
	void setRotation(vec3 rot) { Rotation = rot; }
	void setScale(vec3 scale) { Scale = scale; }
	void tranlate(vec3 Vec3) { Position += Vec3; }
	void rotate(vec3 Vec3) { Rotation += Vec3; }
	void scale(vec3 Vec3) { Scale *= Vec3; }

};