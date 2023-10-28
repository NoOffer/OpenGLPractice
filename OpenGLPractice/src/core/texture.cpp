#include "texture.h"

Texture::Texture(int width, int height, bool alpha, bool linearFilter, const std::string& name)
	: m_Filepath(""), m_Name(name), m_Width(width), m_Height(height), m_NumChannel(alpha ? 4 : 3)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// Filtering when scaling down & up
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
	// X & Y direction wrap function
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		alpha ? GL_RGBA8 : GL_RGB8,
		m_Width, m_Height,
		0,
		alpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		nullptr
	);

	// Unbind texture for now
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string& path, int mipmapLv, bool alpha, bool linearFilter, const std::string& name)
	: m_Filepath(path), m_Name(name)
{
	/*
	For .png file, pixels are loaded from top to bottom
	However OpenGL expect the pixel at the bottom to be loaded first
	*/
	stbi_set_flip_vertically_on_load(1);

	unsigned char* m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NumChannel, 4);  // Local buffer of pixels

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// Filtering when scaling down & up
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
	// X & Y direction wrap function
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(
		GL_TEXTURE_2D,
		mipmapLv,
		alpha ? GL_RGBA8 : GL_RGB8,
		m_Width, m_Height,
		0,
		alpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		m_LocalBuffer
	);
	if (mipmapLv > 0) glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind texture for now
	glBindTexture(GL_TEXTURE_2D, 0);

	// Free m_LocalBuffer
	if (m_LocalBuffer)
	{
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