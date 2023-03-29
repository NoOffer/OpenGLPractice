#pragma once

#include <iostream>

#include "glm/glm.hpp"

#define Log(x) std::cout << x << std::endl

inline std::ostream& operator<<(std::ostream& ostr, glm::vec3 const& v)
{

	ostr << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return ostr;
}
