#pragma once

#include "model.h"

#include <vector>

class Scene
{
public:
	void AddModel(Model m);
	void RemoveModel(const char* name);
	Model* GetModel(const char* name);

private:
	std::vector<Model> m_Models;
};

