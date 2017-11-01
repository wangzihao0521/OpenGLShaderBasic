#pragma once
#include "ShapeData.h"
#include "Object.h"

class Pass {
protected:
	Object* object;
public:
	Pass():
		object(NULL){}

	void setObject(Object* obj);
	Object* getObject() const { return object; }
};
