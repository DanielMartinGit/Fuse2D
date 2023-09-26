#include "Fuse2D-Renderer/src/OpenGL/GraphicsContext/OpenGLGraphicsContext.h"

#include <Fuse2D/Vendor/GLAD/glad.h>
#include <Fuse2D/Vendor/GLFW/glfw3.h>

Fuse2DGraphics::OpenGLGraphicsContext::OpenGLGraphicsContext()
{
	m_Window = nullptr;
}

Fuse2DGraphics::OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window)
{
	m_Window = window;
}

void Fuse2DGraphics::OpenGLGraphicsContext::Init()
{
	glfwMakeContextCurrent(m_Window);
}

void* Fuse2DGraphics::OpenGLGraphicsContext::GetNative()
{
	return nullptr;
}