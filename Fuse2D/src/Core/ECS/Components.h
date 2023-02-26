#pragma once

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
						m_XPos = 0;
						m_YPos = 0;

						m_Width = 0;
						m_Height = 0;
					}

				public:
					void SetXPos(int x) { m_XPos = x; }
					void SetYPos(int y) { m_YPos = y; }
					void SetWidth(int width) { m_Width = width; }
					void SetHeight(int height) { m_Height = height; }

				private:
					int m_XPos;
					int m_YPos;
					int m_Width;
					int m_Height;
			};

			struct SpriteRenderer2D
			{

			};

			struct BoxCollider2D
			{

			};

			struct Rigidbody2D
			{

			};
	};
}