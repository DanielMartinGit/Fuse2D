#include "Renderer.h"
#include "Fuse2D/src/Rendering/Renderer2D/Renderer2D.h"

void Fuse2DRendering::Renderer::Init(Fuse2DRendering::GraphicsContext* context)
{
	Fuse2DRendering::RenderCommand::Init(context);
	Fuse2DRendering::Renderer2D::Init();
}

void Fuse2DRendering::Renderer::Clear()
{
	Fuse2DRendering::RenderCommand::Clear();
}

void Fuse2DRendering::Renderer::ClearColour(float r, float g, float b)
{
	Fuse2DRendering::RenderCommand::ClearColour(r, g, b);
}

Fuse2DRenderAPI::Renderer2DAPI::API Fuse2DRendering::Renderer::GetAPI()
{
	return Fuse2DRenderAPI::Renderer2DAPI::GetAPI();
}

void Fuse2DRendering::Renderer::Submit(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader)
{

}

void Fuse2DRendering::Renderer::DrawIndexedPrimative(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader, unsigned int count)
{
	vertexArray->Bind();
	shader->Bind();

	Fuse2DRendering::RenderCommand::DrawIndexedPrimative(vertexArray, count);
}

void Fuse2DRendering::Renderer::DrawPrimative(Fuse2DRendering::VertexArray* vertexArray, Fuse2DRendering::Shader* shader, unsigned int count)
{
	vertexArray->Bind();
	shader->Bind();

	Fuse2DRendering::RenderCommand::DrawPrimative(vertexArray, count);
}

void* Fuse2DRendering::Renderer::GetDevice()
{
	return Fuse2DRendering::RenderCommand::GetDevice();
}