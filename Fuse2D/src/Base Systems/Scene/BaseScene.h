#pragma once
#include "Fuse2D/src/Rendering/Vulkan/VulkanRenderer2D.h"
#include "Fuse2D/src/Core/Resource Manager/ResourceManager.h"
#include "Fuse2D/src/Core/ECS/Entity/Entity.h"

#include <string>

namespace Fuse2D
{
	class BaseScene
	{
		public:
			BaseScene();
			void Init(Fuse2D::Window* window);

		public:
			virtual void OnSceneLoaded();
			virtual void OnSceneInput(float deltaTime);
			virtual void OnSceneUpdate(float deltaTime);
			virtual void OnSceneRender();
			virtual void OnSceneUnloaded();

		private:
			bool m_IsActive;
			std::string m_SceneName;

		protected:
			Fuse2D::VulkanRenderer2D m_2DRenderer;
			Fuse2D::ResourceManager m_ResourceManager;
			Fuse2D::Window m_Window;
			entt::registry* m_World;
	};
}