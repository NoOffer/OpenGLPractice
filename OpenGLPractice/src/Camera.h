#pragma once

#include "PlaceableObj.h"

class Camera : public PlaceableObj
{
public:
	Camera();
	~Camera();

	glm::mat4 GetViewMatrix();

private:

};
