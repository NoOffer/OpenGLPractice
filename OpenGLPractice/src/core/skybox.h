#pragma once

#include "cube_map.h"
#include "mesh.h"

class Skybox
{
public:
	void SetCubeMap(CubeMap cubeMap);

private:
	Skybox();
	~Skybox();

	Mesh m_Mesh;
};

