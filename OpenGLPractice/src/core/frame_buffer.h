#pragma once

#include "basic.h"

class FrameBuffer
{
public:
	FrameBuffer(int frameW, int frameH, bool rbDepthStencil = true);
	~FrameBuffer();

	void BindR() const;
	void UnbindR() const;
	void BindW() const;
	void UnbindW() const;
	void BindRW() const;
	void UnbindRW() const;

	inline unsigned int GetTexID() { return m_TexID; }
	inline unsigned int GetWidth() { return m_Width; }
	inline unsigned int GetHeight() { return m_Height; }

private:
	unsigned int m_RendererID;
	unsigned int m_TexID;
	unsigned int m_Width;
	unsigned int m_Height;
};

