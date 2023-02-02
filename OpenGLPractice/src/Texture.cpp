#include "Texture.h"

#include <GLAD/glad.h>

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	:m_Filepath(path)
{
	/*
	For .png file, pixels are loaded from top to bottom
	However OpenGL expect the pixel at the bottom to be loaded first
	*/
	stbi_set_flip_vertically_on_load(1);

	unsigned char* m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);  // Local buffer of pixels

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // X direction
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  // Y direction

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	// Unbind texture for now
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free m_LocalBuffer
	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}