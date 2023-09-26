#include "Fuse2D-Renderer/src/OpenGL/Texture/OpenGLTexture.h"
#include <Fuse2D/Vendor/GLAD/glad.h>

Fuse2DGraphics::OpenGLTexture::OpenGLTexture()
{
	m_Width = 0;
	m_Height = 0;

	m_TextureID = 0;
	m_TextureSlot = 0;
}
Fuse2DGraphics::OpenGLTexture::OpenGLTexture(int loadedTexture)
{
	m_Width = 0;
	m_Height = 0;
	m_TextureSlot = 0;

	m_TextureID = loadedTexture;
}

Fuse2DGraphics::OpenGLTexture::OpenGLTexture(std::string path, int slot)
{
	m_Width = 0;
	m_Height = 0;
	m_TextureID = 0;

	m_TextureSlot = slot;

	int width = 0;
	int height = 0;
	int nrChannels = 0;

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
	{
		std::cout << "Failed To Load Texture" << std::endl;
	}
	else
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		m_Height = height;
		m_Width = width;

		glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_TextureID);
		stbi_image_free(data);

		Bind();
	}
}

void Fuse2DGraphics::OpenGLTexture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
	glBindTextureUnit(m_TextureSlot, m_TextureID);
}

void Fuse2DGraphics::OpenGLTexture::SetWidth(int width)
{
	m_Width = width;
}

void Fuse2DGraphics::OpenGLTexture::SetHeight(int height)
{
	m_Height = height;
}

void Fuse2DGraphics::OpenGLTexture::SetTexture(uint32_t texture)
{
	m_TextureID = texture;
}

uint32_t Fuse2DGraphics::OpenGLTexture::GetTextureID()
{
	return m_TextureID;
}

int Fuse2DGraphics::OpenGLTexture::GetWidth()
{
	return m_Width;
}

int Fuse2DGraphics::OpenGLTexture::GetHeight()
{
	return m_Height;
}

void* Fuse2DGraphics::OpenGLTexture::GetNative()
{
	return (void*)m_TextureID;
}