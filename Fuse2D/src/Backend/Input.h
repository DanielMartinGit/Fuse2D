#pragma once
#include <Fuse2D/Vendor/GLFW/glfw3.h>
#include <Fuse2D/Vendor/GLM/ext/vector_float2.hpp>

namespace Fuse2D
{
	enum class InputModes { Keyboard, Controller, Mouse };

	struct InputProps
	{
		InputModes inputMode;
		GLFWwindow* activeWindow;
	};

	class Input
	{
		public:
			Input();
			Input(InputProps props);
			~Input();

		public:
			static void SetCallbacks();

		public:
			static bool IsKeyUp(int key);
			static bool IsKeyDown(int key);
			static bool IsKeyPressed(int key);

		public:
			static bool IsMouseButtonUp(int key);
			static bool IsMouseButtonDown(int key);
			static bool IsMouseButtonPressed(int key);

		public:
			static void SetCursorEnabled(bool enabled);
			static void SetMouseScreenPos(glm::vec2 mousePos) { m_ScreenPos = mousePos; }
			static void SetMouseScrollWheelY(double pos) { m_ScrollYPos = pos; }

			static void ChangeInputMode(InputModes mode);

		public:
			glm::vec2 GetMouseScreenPos() const { return m_ScreenPos; }
			double GetScrollWheelY() const { return m_ScrollYPos; }

		public:
			static void SetWindowInstance(GLFWwindow* window) { m_ActiveWindow = window; SetCallbacks(); }

		private:
			static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void MouseButtonCallback(GLFWwindow* window, int key, int action, int mods);
			static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
			static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		private:
			inline static glm::vec2 m_ScreenPos;
			inline static double m_ScrollYPos;

		private:
			inline static InputModes m_InputMode;
			inline static GLFWwindow* m_ActiveWindow;
	};
}