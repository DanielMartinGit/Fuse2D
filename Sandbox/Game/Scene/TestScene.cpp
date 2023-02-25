#include "TestScene.h"

Sandbox::TestScene::TestScene() {}
Sandbox::TestScene::TestScene(Fuse2D::Window* window)
{
	Init(window);
}

void Sandbox::TestScene::OnSceneLoaded()
{
	std::cout << "Scene loaded" << std::endl;
}

void Sandbox::TestScene::OnSceneInput(float deltaTime)
{
	if (Fuse2D::Input::IsKeyPressed('W'))
	{
		std::cout << "W is Down!" << std::endl;
	}
}

void Sandbox::TestScene::OnSceneUpdate(float deltaTime)
{

}

void Sandbox::TestScene::OnSceneRender()
{
	// This will be the function call for drawing a sprite to the screen, m_Player being the Entity
	//m_2DRenderer.RenderSprite(m_Player);

	m_2DRenderer.Render();
}

void Sandbox::TestScene::OnSceneUnloaded()
{
	std::cout << "Scene unloaded" << std::endl;
}