#include "OpenGLFramebuffer.h"

Fuse2DGraphics::OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height)
{
	m_FBO = 0;
	m_Framebuffer = 0;

	m_CurrentWidth = width;
	m_CurrentHeight = height;

	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

	glGenTextures(1, &m_Framebuffer);
	glBindTexture(GL_TEXTURE_2D, m_Framebuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_CurrentWidth, m_CurrentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Framebuffer, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER::FRAMEBUFFER_NOT_COMPLETE" << std::endl;
}
Fuse2DGraphics::OpenGLFramebuffer::~OpenGLFramebuffer() {}

void Fuse2DGraphics::OpenGLFramebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Fuse2DGraphics::OpenGLFramebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Fuse2DGraphics::OpenGLFramebuffer::DeleteFramebuffer()
{
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteTextures(1, &m_Framebuffer);
}

void Fuse2DGraphics::OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
{
	if (width != 0 && height != 0)
	{
		if (m_CurrentWidth != width || m_CurrentHeight != height)
		{
			m_CurrentWidth = width;
			m_CurrentHeight = height;

			DeleteFramebuffer();
			Fuse2DGraphics::OpenGLFramebuffer::OpenGLFramebuffer(width, height);
		}
	}
}

uint32_t Fuse2DGraphics::OpenGLFramebuffer::GetNative()
{
	return m_Framebuffer;
}