#pragma once
#include "Object.h"
#include "Camera.h"

class Pass {
protected:
	Object* object;
	Camera* camera;

public:
	Pass(Camera* cam):
		object(NULL),camera(cam){}

	void setObject(Object* obj);
	Object* getObject() const { return object; }
	Camera* getCamera() const { return camera; }
};
