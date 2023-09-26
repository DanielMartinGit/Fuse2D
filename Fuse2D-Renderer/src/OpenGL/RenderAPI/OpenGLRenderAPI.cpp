#include "OpenGLRenderAPI.h"

#include <Fuse2D/Vendor/GLAD/glad.h>

Fuse2DGraphics::OpenGLRenderAPI::OpenGLRenderAPI()
{
	m_WireframeMode = false;
	m_Context = nullptr;
}

void Fuse2DGraphics::OpenGLRenderAPI::Init()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Fuse2DGraphics::OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Fuse2DGraphics::OpenGLRenderAPI::SetClearColour(float x, float y, float z)
{
	glClearColor(x, y, z, 1.0f);
}

void Fuse2DGraphics::OpenGLRenderAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Fuse2DGraphics::OpenGLRenderAPI::DrawIndexedPrimitive(Fuse2DRendering::VertexArray* vertexArray, unsigned int count)
{
	m_WireframeMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	unsigned int indexCount = vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Fuse2DGraphics::OpenGLRenderAPI::DrawPrimitive(Fuse2DRendering::VertexArray* _pVertexArray, unsigned int count)
{
	m_WireframeMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Fuse2DGraphics::OpenGLRenderAPI::EnableWireframeMode(bool state)
{
	m_WireframeMode = state;
}

void Fuse2DGraphics::OpenGLRenderAPI::SetContext(Fuse2DRendering::GraphicsContext* _context)
{
	m_Context = _context;
}

void Fuse2DGraphics::OpenGLRenderAPI::BindTexture(Fuse2DRendering::Texture* texture)
{

}

void* Fuse2DGraphics::OpenGLRenderAPI::GetDevice()
{
	return nullptr;
}