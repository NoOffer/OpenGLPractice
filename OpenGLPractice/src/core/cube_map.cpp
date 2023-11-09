#include "cube_map.h"

CubeMap::CubeMap(const std::string& name) : m_Name(name)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	unsigned char* localBuffer = stbi_load("res/textures/Default.png", &m_Width, &m_Height, &m_NumChannel, 0);
	//GL_TEXTURE_CUBE_MAP_POSITIVE_X
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	//GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	//GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);

		GLenum e = glGetError();
		if (e)
		{
			while (e)
			{
				std::cout << "[OpenGL Error] (" << e << ")" << std::endl;
				e = glGetError();
			}
			__debugbreak();
		}
	}

	// Unbind texture for now
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Free buffer
	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}

CubeMap::CubeMap(
	const std::string& pos_x_path,
	const std::string& neg_x_path,
	const std::string& pos_y_path,
	const std::string& neg_y_path,
	const std::string& pos_z_path,
	const std::string& neg_z_path,
	const std::string& name
) : m_Name(name)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	std::string paths[6] = {
		pos_x_path,
		neg_x_path,
		pos_y_path,
		neg_y_path,
		pos_z_path,
		neg_z_path
	};
	unsigned char* localBuffer;
	//GL_TEXTURE_CUBE_MAP_POSITIVE_X
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	//GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	//GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	//GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	for (unsigned int i = 0; i < 6; i++)
	{
		std::ifstream f(paths[i].c_str());
		if (!f.is_open()) LogError("Texture source file not found.");
		localBuffer = stbi_load(paths[i].c_str(), &m_Width, &m_Height, &m_NumChannel, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
	}

	// Unbind texture for now
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Free buffer
	if (localBuffer)
	{
		stbi_image_free(localBuffer);
	}
}

//CubeMap::CubeMap(CubeMap&& other) noexcept
//{
//	m_RendererID = other.m_RendererID;
//	m_Name = other.m_Name;
//	m_Width = other.m_Width;
//	m_Height = other.m_Height;
//	m_NumChannel = other.m_NumChannel;
//
//	other.m_RendererID = 0;
//}

CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_RendererID);
}

CubeMap& CubeMap::operator= (CubeMap&& other) noexcept
{
	LogWarning(other.m_Name.c_str());
	m_RendererID = other.m_RendererID;
	m_Name = other.m_Name;
	m_Width = other.m_Width;
	m_Height = other.m_Height;
	m_NumChannel = other.m_NumChannel;

	other.m_RendererID = 0;

	return *this;
}

void CubeMap::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
}

void CubeMap::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}