#pragma once
#include "Object.h"


class PointLight {
protected:
	Object* Light_obj;
	GLfloat AttenuationFactor;

public:
	PointLight() { 
		Light_obj = nullptr; 
		AttenuationFactor = 0.1;
	}
	void setObject (Object* obj) { Light_obj = obj; }
	Object* getObject() const { return Light_obj; }
	glm::vec3 getPosition() const { return Light_obj->getTransform().getPosition(); }
	GLfloat getAttenuation() const { return AttenuationFactor; }
	char* getName() const { return Light_obj->getName(); }
	//move functions
	void Move_forward() { Light_obj->translate(glm::vec3(0.0f, 0.0f, -0.2f)); }
	void Move_backward() { Light_obj->translate(glm::vec3(0.0f, 0.0f, 0.2f)); }
	void Move_leftward() { Light_obj->translate(glm::vec3(-0.2f, 0.0f, 0.0f)); }
	void Move_rightward() { Light_obj->translate(glm::vec3(0.2f, 0.0f, 0.0f)); }
	void Move_upward() { Light_obj->translate(glm::vec3(0.0f, 0.2f, 0.0f)); }
	void Move_downward() { Light_obj->translate(glm::vec3(0.0f, -0.2f, 0.0f)); }
};
