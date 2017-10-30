#include "Pass.h"

void Pass::setObject(Shapedata shapedata, glm::vec3 Pos)
{
	object = new Object(shapedata, Pos);
}
