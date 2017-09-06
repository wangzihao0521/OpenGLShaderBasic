#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	Camera():
		Position(0.0f,0.0f,0.0f),
		ViewDir(0.0f,0.0f,-1.0f),
		UpDir(0.0f,1.0f,0.0f),
		TengentDir(1.0f,0.0f,0.0f)
	{}

	glm::mat4 getWorldToViewMatrix() const;

	void move_forward();
	void move_backward();
	void move_leftward();
	void move_rightward();
	void move_upward();
	void move_downward();

protected:
	glm::vec3 Position;
	glm::vec3 ViewDir;
	const glm::vec3 UpDir;
	static const float Movement_speed;
	glm::vec3 TengentDir;
};
