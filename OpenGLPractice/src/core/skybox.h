#pragma once

#include "cube_map.h"
#include "mesh.h"

class Skybox
{
public:
	Skybox(CubeMap cubeMap);

private:
	Mesh m_Mesh;
};

