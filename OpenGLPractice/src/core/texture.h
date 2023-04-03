#pragma once

#include <GLAD/glad.h>
#include <string>

#include "stb_image/stb_image.h"

class Texture
{
public:
	Texture(const std::string& path, const std::string& name = "");
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	std::string m_Filepath, m_Name;
	int m_Width, m_Height, m_NumChannel;  // stb_image uses int instead of unsigned int
};