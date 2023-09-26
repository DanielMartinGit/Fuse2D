#pragma once

#include "Input.h"
#include "Fuse2D/src/Rendering/Renderer/Renderer.h"

#include <Fuse2D/Vendor/GLAD/glad.h>
#include <Fuse2D/Vendor/GLFW/glfw3.h>
#include <Fuse2D/Vendor/GLM/ext/vector_float2.hpp>
#include <Fuse2D/Vendor/STB/stb_image.h>

#include <iostream>

namespace Fuse2D
{
	struct WindowProps
	{
		WindowProps()
		{
			Title = "";
			IconPath = "";
			Width = 0;
			Height = 0;
			IsFullScreen = false;
			InputMode = Fuse2D::InputModes::Keyboard;
		}

		public:
			std::string IconPath;
			std::string Title;
			uint16_t Width;
			uint16_t Height;

			bool IsFullScreen;
			bool IsResizable;
			Fuse2D::InputModes InputMode;
	};

	class Window
	{
		public:
			Window();
			Window(WindowProps props);
			~Window();

		public:
			void Initialise(const char* title, const char* iconPath, uint16_t width, uint16_t height, bool fullscreen, GLFWwindow* window, Fuse2D::InputModes inputMode);
			void ResizeWindow(uint16_t width, uint16_t height);

			void Clear(float r, float g, float b, float a);
			void Draw();
			void Destroy();

		public:
			int GetWindowShouldClose() { return glfwWindowShouldClose(m_WindowInstance); }

		public:
			void SetWindowResizable(bool resize);

			void SetWindowTitle(const char* title);
			void SetWindowIcon(const char* iconPath);
			void SetWindowShouldClose(bool shouldClose);
			void ShowWindow(bool show);

		public:
			static void FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height);

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