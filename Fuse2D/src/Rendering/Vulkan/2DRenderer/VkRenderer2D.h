#pragma once
#include "Fuse2D/src/Core/ECS/Entity/Entity.h"

namespace Fuse2DRendering
{
	class VkRenderer2D
	{
		public:
			VkRenderer2D();

		public:
			void InitialiseRenderer();

		public:
			void DrawEntity(Fuse2D::Components::Transform transform, Fuse2D::Components::SpriteRenderer2D spriteRenderer);
			void DrawEntity(Fuse2D::Entity entity);

			void DrawDebugLine(uint32_t startPoint, uint32_t endPoint);
			void DrawDebugSquare(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height);

			void CleanupRenderer();
	};
}