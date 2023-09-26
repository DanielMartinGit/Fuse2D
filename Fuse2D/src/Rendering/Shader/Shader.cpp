#include "Shader.h"

#include <Fuse2D/src/Rendering/Renderer/Renderer.h>
#include <Fuse2D-Renderer/src/OpenGL/Shaders/OpenGLShader.h>

Fuse2DRendering::Shader* Fuse2DRendering::Shader::Create(std::string filePath, GLuint shaderType)
{
	switch (Fuse2DRendering::Renderer::GetAPI())
	{
		case Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL:
		{
			return new Fuse2DGraphics::OpenGLShader(filePath, shaderType);
		}
			break;
	}

	return nullptr;
}

Fuse2DRendering::Shader* Fuse2DRendering::Shader::Create(std::string filePath)
{
	switch (Fuse2DRendering::Renderer::GetAPI())
	{
		case Fuse2DRenderAPI::Renderer2DAPI::API::OpenGL:
		{
			return new Fuse2DGraphics::OpenGLShader(filePath);
		}
			break;
	}

	return nullptr;
}