#pragma once

#include "cube_map.h"
#include "mesh.h"

class Skybox
{
public:
	void static Init();
	void static inline SetCubeMap(const CubeMap& cubeMap) { s_CubeMap = cubeMap; }
	void static Render();

private:
	Skybox();
	~Skybox();

	// render data
	static IndexBuffer s_IB;
	static VertexArray s_VA;
	static CubeMap s_CubeMap;
};

