#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shader) const
{
	// Bind
	va.Bind();
	ib.Bind();
	shader.Bind();

	//// Set uniform
	//shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, ib.GetCount(), ib.GetIndexType(), nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}