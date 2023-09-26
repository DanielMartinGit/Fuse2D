#include "SandboxScene.h"

Sandbox::SandboxScene::SandboxScene() {}
Sandbox::SandboxScene::~SandboxScene() {}

void Sandbox::SandboxScene::OnSceneLoaded()
{
	// Initialise the Renderer2D
	Fuse2DRendering::Renderer2D::Init();
	
	// Create the needed shaders
	Fuse2DRendering::ShaderProgram::CreateShader(*Fuse2D::AssetManager::CreateShader("resources/shaders/vertex.vert", GL_VERTEX_SHADER));
	Fuse2DRendering::ShaderProgram::CreateShader(*Fuse2D::AssetManager::CreateShader("resources/shaders/fragment.frag", GL_FRAGMENT_SHADER));
	Fuse2DRendering::ShaderProgram::Link();
}

void Sandbox::SandboxScene::OnSceneInput(float dt) {}
void Sandbox::SandboxScene::OnSceneUpdate(float dt) {}

void Sandbox::SandboxScene::OnSceneRender()
{
	// Apply the needed shaders before rendering
	Fuse2DRendering::ShaderProgram::Use();

	// Begin the Renderer2Ds scene
	Fuse2DRendering::Renderer2D::BeginScene();
	
	// Draw a quad using the renderer2D
	Fuse2DRendering::Renderer2D::DrawQuad({ -0.5f, 0, 0 }, { 0.5f, 0.5f, 0.5f }, { 1.0, 0.0, 0.0 }, 0.0f);
	Fuse2DRendering::Renderer2D::DrawQuad({ 0.5f, 0, 0 }, { 0.5f, 1.0f, 0.0f }, { 0.0, 0.0, 1.0 }, 0.0f);

	// Begin the Renderer2Ds scene
	Fuse2DRendering::Renderer2D::EndScene();
}

void Sandbox::SandboxScene::OnSceneUnloaded() {}