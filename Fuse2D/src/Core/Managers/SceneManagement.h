#pragma once

#include "Fuse2D/src/Core/Scene.h"

#include <vector>
#include <memory>
#include <iostream>

namespace Fuse2D
{
	class SceneManagement
	{
		public:
			SceneManagement() { m_ActiveScene = {}; }
			~SceneManagement() {}

		public:
			void AddScene(Fuse2D::Scene scene)
			{
				m_Scenes.push_back(scene);
				SetStartingScene(0);
			}

			void SetStartingScene(int index)
			{
				std::cout << "Setting active scene to Scene " << &m_ActiveScene->GetSceneName() << std::endl;
				m_ActiveScene =	&m_Scenes[index];
			}

			void RunLoadedScene(float dt)
			{
				m_ActiveScene->OnSceneInput(dt);
				m_ActiveScene->OnSceneUpdate(dt);
				m_ActiveScene->OnSceneRender();
			}

			Fuse2D::Scene& GetActiveScene()
			{
				return *m_ActiveScene;
			}

		private:
			std::vector<Fuse2D::Scene> m_Scenes;
			Fuse2D::Scene* m_ActiveScene;
	};
}