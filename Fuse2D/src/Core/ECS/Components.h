#pragma once
#include <Fuse2D/Vendor/GLM/vec2.hpp>

namespace Fuse2D
{
	class Components
	{
		public:
			struct Transform
			{
				public:
					Transform()
					{
						m_Position = glm::vec2(0.0f, 0.0f);
					}

				public:
					void SetPosition(glm::vec2 pos) { m_Position = pos; }
					void SetRotation(glm::vec2 rot) { m_Rotation = rot; }
					void SetScale(glm::vec2 scale) { m_Scale = scale; }

				private:
					glm::vec2 m_Position;
					glm::vec2 m_Rotation;
					glm::vec2 m_Scale;
			};

			struct SpriteRenderer2D
			{
				SpriteRenderer2D()
				{
					m_SpriteSize = glm::vec2(0.0f, 0.0f);
					m_Layer = 0;
					m_SpriteColour = glm::vec3(255, 255, 255);
				}

				public:
					void SetSpriteSize(glm::vec2 size) { m_SpriteSize = size; }
					void SetSpriteLayer(uint32_t layer) { m_Layer = layer; }
					void SetSpriteColour(glm::vec3 colour) { m_SpriteColour = colour; }
			
				public:
					glm::vec2 GetSpriteSize() { return m_SpriteSize; }
					glm::vec3 GetSpriteColour() { return m_SpriteColour; }
					uint32_t GetSpriteLayer() { return m_Layer; }

				private:
					//FuseTexture2D m_Sprite;
					glm::vec2 m_SpriteSize;
					glm::vec3 m_SpriteColour;
					uint32_t m_Layer;
			};

			struct BoxCollider2D
			{
				BoxCollider2D()
				{
					m_ColliderBounds = glm::vec2(0, 0);
					m_IsTrigger = false;
				}

				public:
					void SetCollisionBounds(glm::vec2 collisionBounds) { m_ColliderBounds = collisionBounds; }
					void SetIsTrigger(bool trigger) { m_IsTrigger = trigger; }

				public:
					glm::vec2 GetColliderBounds() { return m_ColliderBounds; }
					bool GetIsTrigger() { return m_IsTrigger; }

				private:
					bool m_IsTrigger;
					glm::vec2 m_ColliderBounds;
			};

			struct Rigidbody2D
			{
				Rigidbody2D()
				{
					m_GravityScale = 1.0f;
					m_Mass = 1.0f;
					m_IsKinematic = false;
				}

				public:
					void SetGravityScale(float scale) { m_GravityScale = scale; }
					void SetMass(float mass) { m_Mass = mass; }
					void SetIsKinematic(bool kinematic) { m_IsKinematic = kinematic; }

				public:
					float GetGravityScale() { return m_GravityScale; }
					float GetMass() { return m_Mass; }
					bool GetIsKinematic() { return m_IsKinematic; }

				private:
					float m_GravityScale;
					float m_Mass;
					bool m_IsKinematic;
			};
	};
}