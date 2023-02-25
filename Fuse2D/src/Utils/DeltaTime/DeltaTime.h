#pragma once
#include <Fuse2D/Vendor/GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <ctime>

namespace Fuse2DUtils
{
	class DeltaTime
	{
		public:
			DeltaTime()
			{
				m_DeltaTime = 0.0f;
				m_LastFrame = 0.0f;
			}
			~DeltaTime() {}

		public:
			static double GetDeltaTime()
			{
				return m_DeltaTime;
			}

			static void CalculateDeltaTime()
			{
				m_CurrentFrame = glfwGetTime();
				m_DeltaTime = m_CurrentFrame - m_LastFrame;
				m_LastFrame = m_CurrentFrame;
			}

			static std::string GetCurrentSystemTime()
			{
				std::time_t ct = std::time(0);
				char* cc = ctime(&ct);

				return static_cast<std::string>(cc);
			}

		private:
			inline static int m_FPS;
			inline static double m_CurrentFrame;
			inline static double m_DeltaTime;
			inline static double m_LastFrame;
	};
}