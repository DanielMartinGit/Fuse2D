#pragma once
#include "Fuse2D/src/Core/ECS/Components.h"
#include "Fuse2D/Vendor/Entt/entt.hpp"

#include <iostream>

namespace Fuse2D
{
	class Entity
	{
		public:
			Entity()
			{
				m_World = nullptr;
			}
			
			Entity(entt::registry* world)
			{
				m_World = world;
				m_EntityInstance = m_World->create();
			}

		public:
			template<typename T>
			void AddComponent()
			{
				if (m_World->valid(m_EntityInstance))
				{
					bool hasComponent = m_World->any_of<T>(m_EntityInstance);

					if (!hasComponent)
					{
						m_World->emplace<T>(m_EntityInstance);
						std::cout << "Component Added!" << std::endl;
					}
				}
			}

			template<typename T>
			T GetComponent()
			{
				if (m_World->valid(m_EntityInstance))
				{
					bool hasComponent = m_World->any_of<T>(m_EntityInstance);

					if (hasComponent)
					{
						std::cout << "Component retrieved!" << std::endl;
						return m_World->get<T>(m_EntityInstance);
					}
				}
			}

		private:
			entt::registry* m_World;
			entt::entity m_EntityInstance;
	};
}