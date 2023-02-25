#pragma once
#include "Fuse2D/src/Base Systems/Scene/BaseScene.h"

#include <iostream>

namespace Sandbox
{
	class TestScene : public Fuse2D::BaseScene
	{
		public:
			TestScene();
			TestScene(Fuse2D::Window* window);

		public:
			void OnSceneLoaded() override;
			void OnSceneInput(float deltaTime) override;
			void OnSceneUpdate(float deltaTime) override;
			void OnSceneRender() override;
			void OnSceneUnloaded() override;

		private:
			Fuse2D::Entity m_Entity;
	};
}