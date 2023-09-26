#include "Renderer2D.h"

#include "Fuse2D/src/Rendering/Renderer2D/Renderer2D.h"
#include "Fuse2D/src/Rendering/RenderCommand/RenderCommand.h"
#include "Fuse2D/src/Rendering/Texture/Texture.h"
#include "Fuse2D/src/Rendering/ShaderProgram/ShaderProgram.h"

void Fuse2DRendering::Renderer2D::Init()
{
	FlushandReset();

	if (Fuse2DRendering::ShaderProgram::GetShadersLoaded() == 0)
	{
		s_Data.m_Shader = Fuse2DRendering::Shader::Create("Resources/Shaders/BasicShader.shader");
		s_Data.m_BasicTexture = Fuse2DRendering::Texture::Create("Resources/Textures/texture.png", 0);
	}
	else
	{
		s_Data.m_Shader = Fuse2DRendering::ShaderProgram::GetShader(GL_FRAGMENT_SHADER);
	}

	s_Data.m_QuadBase[0] = { 0.5f, 0.5f, 0.0f, 1.0f };
	s_Data.m_QuadBase[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.m_QuadBase[2] = { -0.5f, -0.5f, 0.0f, 1.0f };
	s_Data.m_QuadBase[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

	s_Data.m_Indices = new uint32_t[s_Data.m_MaxQuads * 6];

	int offset = 0;

	for (int i = 0; i < s_Data.m_MaxQuads * 6; i += 6)
	{
		s_Data.m_Indices[i] = (offset * 4) + 0;
		s_Data.m_Indices[i + 1] = (offset * 4) + 1;
		s_Data.m_Indices[i + 2] = (offset * 4) + 3;
		s_Data.m_Indices[i + 3] = (offset * 4) + 1;
		s_Data.m_Indices[i + 4] = (offset * 4) + 2;
		s_Data.m_Indices[i + 5] = (offset * 4) + 3;
		offset++;
	}

	s_Data.m_QuadVertices = new Fuse2DRendering::Vertex[s_Data.m_MaxVertices];
	s_Data.m_QuadVA = Fuse2DRendering::VertexArray::Create();
	s_Data.m_QuadIB = Fuse2DRendering::IndexBuffer::Create(s_Data.m_Indices, s_Data.m_MaxQuads * 6);
	s_Data.m_QuadBuffer = Fuse2DRendering::VertexBuffer::Create(s_Data.m_MaxVertices * sizeof(Fuse2DRendering::Vertex));

	s_Data.m_QuadCount = 0;
}

void Fuse2DRendering::Renderer2D::BeginScene()
{
	s_Data.m_Shader->Bind();

	s_Data.m_QuadVA->AddVertexBuffer(s_Data.m_QuadBuffer);
	s_Data.m_QuadVA->SetIndexBuffer(s_Data.m_QuadIB);
	s_Data.m_QuadVA->AddShader(s_Data.m_Shader);
}

void Fuse2DRendering::Renderer2D::EndScene()
{
	s_Data.m_QuadIB->SetCount(s_Data.m_QuadCount * 6);
	s_Data.m_QuadBuffer->SetData(s_Data.m_QuadVertices, s_Data.m_QuadCount * 4 * sizeof(Fuse2DRendering::Vertex));
	Flush();
}

void Fuse2DRendering::Renderer2D::Flush()
{
	s_Data.m_QuadVA->Bind();
	Fuse2DRendering::RenderCommand::EnableWireframeMode(false);
	Fuse2DRendering::RenderCommand::DrawIndexedPrimative(s_Data.m_QuadVA, s_Data.m_MaxQuads * 6);
	s_Data.m_QuadCount = 0;
}

void Fuse2DRendering::Renderer2D::DrawQuad(glm::vec3 position, glm::vec3 size, glm::vec3 color, float rotationAngle)
{
	int quadSize = 4;

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), size);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), { 0.0f, 0.0f, 1.0f });

	glm::vec2 textureCoords[4] =
	{
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};

	for (int i = 0; i < quadSize; i++)
	{
		Vertex v;
		v.m_Position = translationMatrix * rotationMatrix * scaleMatrix * s_Data.m_QuadBase[i];
		v.m_Colour = color;
		v.m_Texture = textureCoords[i];
		s_Data.m_QuadVertices[(s_Data.m_QuadCount * 4) + i] = v;
	}

	++s_Data.m_QuadCount;
}

void Fuse2DRendering::Renderer2D::DrawQuad(glm::vec3 position, glm::vec3 size, glm::vec3 color, Fuse2DRendering::Texture* texture, float rotationAngle)
{
	int quadSize = 4;

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), size);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), { 0.0f, 0.0f, 1.0f });

	glm::vec2 textureCoords[4] =
	{
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};

	for (int i = 0; i < quadSize; i++)
	{
		Vertex v;
		v.m_Position = translationMatrix * rotationMatrix * scaleMatrix * s_Data.m_QuadBase[i];
		v.m_Colour = color;
		v.m_Texture = textureCoords[i];
		s_Data.m_QuadVertices[(s_Data.m_QuadCount * 4) + i] = v;
	}

	s_Data.m_QuadCount++;
}

void Fuse2DRendering::Renderer2D::FlushandReset()
{
	delete s_Data.m_QuadVertices;
	s_Data.m_QuadVertices = new Fuse2DRendering::Vertex[s_Data.m_MaxVertices];
	s_Data.m_QuadCount = 0;
}

int Fuse2DRendering::Renderer2D::GetTextureSlotsUsed()
{
	return s_Data.m_TextureCount;
}

void Fuse2DRendering::Renderer2D::IncreaseTextureSlotsUsed()
{
	s_Data.m_TextureCount++;
}

int& Fuse2DRendering::Renderer2D::GetQuadCount()
{
	return s_Data.m_QuadCount;
}