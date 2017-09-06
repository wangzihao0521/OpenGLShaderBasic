#include <Camera.h>
#include <glm\gtx\transform.hpp>

const float Camera::Movement_speed = 0.1f;

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(Position, Position + ViewDir, UpDir);
}

void Camera::move_forward()
{
	Position += ViewDir * Movement_speed;
}

void Camera::move_backward()
{
	Position += -ViewDir * Movement_speed;
}

void Camera::move_leftward()
{
	Position += -TengentDir * Movement_speed;
}

void Camera::move_rightward()
{
	Position += TengentDir * Movement_speed;
}

void Camera::move_upward()
{
	Position += UpDir * Movement_speed;
}

void Camera::move_downward()
{
	Position += -UpDir *Movement_speed;
}
