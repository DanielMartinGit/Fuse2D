#pragma once
#include <Fuse2D/Vendor/GLFW/glfw3.h>
#include <Fuse2D/Vendor/GLFW/glfw3native.h>
#include <Fuse2D/src/Core/Input/Input.h>

#include <iostream>

namespace Fuse2D
{
	struct WindowProps
	{
		WindowProps()
		{
			Title = "";
			Width = 0;
			Height = 0;
			IsFullScreen = false;
		}

		public:
			std::string Title;
			uint16_t Width;
			uint16_t Height;

			bool IsFullScreen;
			bool IsResizable;
	};

	class Window
	{
		public:
			Window();
			Window(WindowProps props);
			~Window();

		public:
			void Initialise(const char* title, uint16_t width, uint16_t height, bool fullscreen, GLFWwindow* window);
			void ResizeWindow(uint16_t width, uint16_t height);

			void Present();
			void DestroyWindow();

		public:
			int GetWindowShouldClose() { return glfwWindowShouldClose(m_WindowInstance); }
		
		public:
			void SetWindowResizable(bool resize);

			void SetWindowTitle(const char* title);
			void SetWindowIcon(std::string path);
			void SetWindowShouldClose(bool shouldClose);

		private:
			uint16_t m_WindowWidth;
			uint16_t m_WindowHeight;
			std::string m_WindowTitle;

			bool m_isFullScreen;
		public:
			GLFWwindow* GetWindowInstance() { return m_WindowInstance; }

		private:
			GLFWwindow* m_WindowInstance;
	};
}