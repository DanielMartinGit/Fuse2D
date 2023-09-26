#pragma once
#include "Fuse2D/src/Core/Scene.h"

namespace Sandbox
{
	class SandboxScene : public Fuse2D::Scene
	{
		public:
			SandboxScene();
			~SandboxScene();

		public:
			void OnSceneLoaded() override;
			void OnSceneUnloaded() override;
		
		public:
			void OnSceneInput(float dt) override;
			void OnSceneUpdate(float dt) override;
			void OnSceneRender() override;
	};
}