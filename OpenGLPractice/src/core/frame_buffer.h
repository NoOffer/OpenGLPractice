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

private:
	unsigned int m_RendererID;
};

