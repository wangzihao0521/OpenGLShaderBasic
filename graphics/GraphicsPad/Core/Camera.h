#pragma once

#include <glm\glm.hpp>

class Camera
{
public:
	Camera(char* CamName = "MainCamera",glm::vec3 pos = glm::vec3()):
		name(CamName),
		Position(pos),
		ViewDir(0.0f,0.0f,-1.0f),
		UpDir(0.0f,1.0f,0.0f),
		TengentDir(1.0f,0.0f,0.0f)
	{}

	glm::mat4 getWorldToViewMatrix() const;
	glm::vec3 getPosition() const
	{
		return Position;
	}

	char* getName() const
	{
		return name;
	}

	void setPosition(glm::vec3 NewPosition) {
		Position = NewPosition;
	}

	void move_forward();
	void move_backward();
	void move_leftward();
	void move_rightward();
	void move_upward();
	void move_downward();
	void rotate_left();
	void rotate_right();
	void rotate_up();
	void rotate_down();

	void operator = (const Camera cam)
	{
//		Camera camera;
		name = cam.name;
		Position = cam.Position;
		ViewDir = cam.ViewDir;
		TengentDir = cam.TengentDir;
//		return camera;
	}

protected:
	char* name;
	glm::vec3 Position;
	glm::vec3 ViewDir;
	glm::vec3 UpDir;
	static const float Movement_speed;
	static const float Rotation_speed;
	glm::vec3 TengentDir;
};
