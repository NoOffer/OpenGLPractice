#pragma once

#include "basic.h"

#include "stb_image/stb_image.h"

class CubeTexture
{
public:
	CubeTexture(
		const std::string& pos_x_path,
		const std::string& neg_x_path,
		const std::string& pos_y_path,
		const std::string& neg_y_path,
		const std::string& pos_z_path,
		const std::string& neg_z_path,
		const std::string& name = ""
	);
	~CubeTexture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	//inline int GetWidth() const { return m_Width; }
	//inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	std::string m_Name;
	int m_Width, m_Height, m_NumChannel;  // stb_image uses int instead of unsigned int
};
