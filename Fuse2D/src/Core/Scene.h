#pragma once

#include "Fuse2D/src/Core/Managers/AssetManager.h"
#include "Fuse2D/src/Rendering/Renderer2D/Renderer2D.h"
#include <string>

namespace Fuse2D
{
	class Scene
	{
		public:
			Scene();
			~Scene();

		public:
			virtual void OnSceneLoaded() = 0;
			virtual void OnSceneUnloaded() = 0;
		
		public:
			virtual void OnSceneInput(float dt) = 0;
			virtual void OnSceneUpdate(float dt) = 0;
			virtual void OnSceneRender() = 0;

		public:
			void SetSceneName(std::string name) { m_SceneName = name; }
			std::string GetSceneName() { return m_SceneName; }

		private:
			std::string m_SceneName;
	};
}