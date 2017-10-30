#pragma once
#include "ShapeData.h"
#include "Object.h"

class Pass {
protected:
	Object* object;
public:
	Pass():
		object(NULL){}

	void setObject(Shapedata shapedata,glm::vec3 Pos = glm::vec3());
	Object* getObject() const { return object; }
};
