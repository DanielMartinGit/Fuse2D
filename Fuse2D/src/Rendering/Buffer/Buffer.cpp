#include "Buffer.h"

#include <Fuse2D/src/Rendering/Renderer/Renderer.h>
#include <Fuse2D-Renderer/src/OpenGL/Buffer/OpenGLBuffer.h>

#pragma region VertexBuffer
Fuse2DRendering::VertexBuffer* Fuse2DRendering::VertexBuffer::Create(Vertex* vertices, int size)
{
	return static_cast<VertexBuffer*>(new Fuse2DGraphics::OpenGLVertexBuffer(vertices, size));
}

Fuse2DRendering::VertexBuffer* Fuse2DRendering::VertexBuffer::Create(int size)
{
	return static_cast<VertexBuffer*>(new Fuse2DGraphics::OpenGLVertexBuffer(size));
}
#pragma endregion

#pragma region IndexBuffer
Fuse2DRendering::IndexBuffer* Fuse2DRendering::IndexBuffer::Create(uint32_t* indices, int size)
{
	return static_cast<IndexBuffer*>(new Fuse2DGraphics::OpenGLIndexBuffer(indices, size));
}
#pragma endregion