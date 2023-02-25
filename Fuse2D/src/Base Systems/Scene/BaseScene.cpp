#include "BaseScene.h"

Fuse2D::BaseScene::BaseScene()
{
	m_World = nullptr;
	m_IsActive = false;
}

void Fuse2D::BaseScene::Init(Fuse2D::Window* window)
{
	m_Window = *window;

	m_IsActive = true;
	m_SceneName = "Sandbox Test";

	m_World = new entt::registry();
	m_ResourceManager = Fuse2D::ResourceManager();
	
	m_2DRenderer = Fuse2D::VulkanRenderer2D(m_Window);
	m_2DRenderer.Init();
}

void Fuse2D::BaseScene::OnSceneLoaded() {}
void Fuse2D::BaseScene::OnSceneInput(float deltaTime) {}
void Fuse2D::BaseScene::OnSceneUpdate(float deltaTime) {}
void Fuse2D::BaseScene::OnSceneRender() {}
void Fuse2D::BaseScene::OnSceneUnloaded() {}