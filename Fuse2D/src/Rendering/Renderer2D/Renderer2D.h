#pragma once
#include "Fuse2D/src/Rendering/RenderCommand/RenderCommand.h"
#include "Fuse2D/src/Rendering/Texture/Texture.h"

#include <Fuse2D/Vendor/GLM/glm.hpp>
#include <Fuse2D/Vendor/GLM/gtx/transform.hpp>

namespace Fuse2DRendering
{
	class Renderer2D
	{
		private:
			struct Render2DData
			{
				Fuse2DRendering::IndexBuffer* m_QuadIB = nullptr;
				Fuse2DRendering::Shader* m_Shader = nullptr;
				Fuse2DRendering::Texture* m_BasicTexture = nullptr;

				int m_MaxQuads = 200;
				int m_MaxVertices = m_MaxQuads * 4;
				int m_QuadCount = 0;
				int m_QuadIndicesCount = 0;
								int m_TextureCount = 0;

				Fuse2DRendering::VertexArray* m_QuadVA = nullptr;
				Fuse2DRendering::Vertex* m_QuadVertices = nullptr;
				Fuse2DRendering::VertexBuffer* m_QuadBuffer = nullptr;

				glm::vec4 m_QuadBase[4] = {};
				uint32_t* m_Indices = 0;
			};

		public:
			static void Init();

			static void BeginScene();
			static void EndScene();
			static void Flush();

			static void DrawQuad(glm::vec3 position, glm::vec3 size, glm::vec3 colour, float rotationAngle = 0);
			static void DrawQuad(glm::vec3 position, glm::vec3 size, glm::vec3 colour, Fuse2DRendering::Texture* texture, float rotationAngle = 0);

			static void FlushandReset();
			static int& GetQuadCount();
			static int GetTextureSlotsUsed();
			static void IncreaseTextureSlotsUsed();

		public:
			inline static Render2DData s_Data;
	};
}