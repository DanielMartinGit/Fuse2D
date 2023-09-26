#include "OpenGLBuffer.h"

#include <Fuse2D/Vendor/GLAD/glad.h>

#pragma region OpenGL Vertex Buffer
Fuse2DGraphics::OpenGLVertexBuffer::OpenGLVertexBuffer(Fuse2DRendering::Vertex* vertices, int size)
{
	m_IVBO = 0;

	glGenBuffers(1, &m_IVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_IVBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Fuse2DGraphics::OpenGLVertexBuffer), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Fuse2DGraphics::OpenGLVertexBuffer::OpenGLVertexBuffer(int size)
{
	m_IVBO = 0;

	glGenBuffers(1, &m_IVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_IVBO);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Fuse2DGraphics::OpenGLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_IVBO);
}

void Fuse2DGraphics::OpenGLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* Fuse2DGraphics::OpenGLVertexBuffer::GetNative()
{
	return (void*)m_IVBO;
}

void Fuse2DGraphics::OpenGLVertexBuffer::SetData(void* data, int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_IVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
#pragma endregion

#pragma region OpenGL Index Buffer
Fuse2DGraphics::OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, int count)
{
	m_IEBO = 0;
	m_ICount = count;

	glGenBuffers(1, &m_IEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Fuse2DGraphics::OpenGLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IEBO);
}

void Fuse2DGraphics::OpenGLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int Fuse2DGraphics::OpenGLIndexBuffer::GetCount()
{
	return m_ICount;
}

void Fuse2DGraphics::OpenGLIndexBuffer::SetCount(int count)
{
	m_ICount = count;
}

void* Fuse2DGraphics::OpenGLIndexBuffer::GetNative()
{
	return (void*)m_IEBO;
}
#pragma endregion