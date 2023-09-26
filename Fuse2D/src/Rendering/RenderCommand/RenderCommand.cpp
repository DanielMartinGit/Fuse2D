#include "RenderCommand.h"

std::unique_ptr<Fuse2DRenderAPI::Renderer2DAPI> Fuse2DRendering::RenderCommand::s_RenderAPI = std::unique_ptr<Fuse2DRenderAPI::Renderer2DAPI>(Fuse2DRenderAPI::Renderer2DAPI::Create());

void Fuse2DRendering::RenderCommand::Init(Fuse2DRendering::GraphicsContext* context)
{
	s_RenderAPI->SetContext(context);
	s_RenderAPI->Init();
}

void Fuse2DRendering::RenderCommand::ClearColour(float r, float g, float b)
{
	s_RenderAPI->SetClearColour(r, g, b);
}

void Fuse2DRendering::RenderCommand::Clear()
{
	s_RenderAPI->Clear();
}

void Fuse2DRendering::RenderCommand::EnableWireframeMode(bool state)
{
	s_RenderAPI->EnableWireframeMode(state);
}

void Fuse2DRendering::RenderCommand::DrawIndexedPrimative(Fuse2DRendering::VertexArray* vertexArray, unsigned int count)
{
	s_RenderAPI->DrawIndexedPrimitive(vertexArray, count);
}

void Fuse2DRendering::RenderCommand::DrawPrimative(Fuse2DRendering::VertexArray* vertexArray, unsigned int count)
{
	s_RenderAPI->DrawPrimitive(vertexArray, count);
}

void* Fuse2DRendering::RenderCommand::GetDevice()
{
	return s_RenderAPI->GetDevice();
}

void Fuse2DRendering::RenderCommand::BindTexture(Fuse2DRendering::Texture* texture)
{
	s_RenderAPI->BindTexture(texture);
}