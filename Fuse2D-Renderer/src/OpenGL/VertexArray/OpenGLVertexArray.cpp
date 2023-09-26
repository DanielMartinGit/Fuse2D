#include "Fuse2D-Renderer/src/OpenGL/VertexArray/OpenGLVertexArray.h"
#include <Fuse2D/Vendor/GLAD/glad.h>

Fuse2DGraphics::OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &m_VAO);
}

void Fuse2DGraphics::OpenGLVertexArray::Bind()
{
	glBindVertexArray(m_VAO);
}

void Fuse2DGraphics::OpenGLVertexArray::Unbind()
{
	glBindVertexArray(0);
}

void Fuse2DGraphics::OpenGLVertexArray::AddVertexBuffer(Fuse2DRendering::VertexBuffer* vertexBuffer)
{
	glBindVertexArray(m_VAO);
	vertexBuffer->Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Fuse2DRendering::Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Fuse2DRendering::Vertex), (void*)(offsetof(Fuse2DRendering::Vertex, m_Colour)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Fuse2DRendering::Vertex), (void*)(offsetof(Fuse2DRendering::Vertex, m_Texture)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	vertexBuffer->Unbind();

	m_VertexBuffer = vertexBuffer;
}

void Fuse2DGraphics::OpenGLVertexArray::SetIndexBuffer(Fuse2DRendering::IndexBuffer* indexBuffer)
{
	glBindVertexArray(m_VAO);
	indexBuffer->Bind();

	glBindVertexArray(0);
	indexBuffer->Unbind();

	m_IndexBuffer = indexBuffer;
}

Fuse2DRendering::IndexBuffer* Fuse2DGraphics::OpenGLVertexArray::GetIndexBuffer()
{
	return m_IndexBuffer;
}

void Fuse2DGraphics::OpenGLVertexArray::AddShader(Fuse2DRendering::Shader* vert)
{
	m_Vertex = vert;
}

void* Fuse2DGraphics::OpenGLVertexArray::GetNative()
{
	return (void*)m_VAO;
}