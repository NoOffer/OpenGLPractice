#include "post_process.h"

static float vertices[12] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,
};

static unsigned int indices[6] =
{
	0, 1, 2,
	1, 3, 2
};

PostProcess::PostProcess() :
	m_IB(IndexBuffer(indices, 36))
{

}
