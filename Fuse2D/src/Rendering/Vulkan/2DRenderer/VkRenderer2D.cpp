#include "VkRenderer2D.h"

Fuse2DRendering::VkRenderer2D::VkRenderer2D() {}

void Fuse2DRendering::VkRenderer2D::InitialiseRenderer()
{

}

void Fuse2DRendering::VkRenderer2D::DrawEntity(Fuse2D::Entity entity)
{
	auto& transformComponent = entity.GetComponent<Fuse2D::Components::Transform>();
	auto& spriteComponent = entity.GetComponent<Fuse2D::Components::SpriteRenderer2D>();
	

}

void Fuse2DRendering::VkRenderer2D::DrawEntity(Fuse2D::Components::Transform transform, Fuse2D::Components::SpriteRenderer2D spriteRenderer)
{

}

void Fuse2DRendering::VkRenderer2D::DrawDebugLine(uint32_t startPoint, uint32_t endPoint)
{

}

void Fuse2DRendering::VkRenderer2D::DrawDebugSquare(uint32_t startX, uint32_t startY, uint32_t width, uint32_t height)
{

}

void Fuse2DRendering::VkRenderer2D::CleanupRenderer()
{

}