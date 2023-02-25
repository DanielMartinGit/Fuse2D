#include "Window.h"

Fuse2D::Window::Window() {}

Fuse2D::Window::Window(WindowProps props)
{
	if (!glfwInit() || !m_WindowInstance)
	{
		std::cout << "Error: Problem with GLFW" << std::endl;
		glfwTerminate();
	}

	SetWindowResizable(props.IsResizable);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), props.IsFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	
	Initialise(props.Title.c_str(), props.Width, props.Height, props.IsFullScreen, window);
}

Fuse2D::Window::~Window() {}

void Fuse2D::Window::Initialise(const char* title, uint16_t width, uint16_t height, bool fullscreen, GLFWwindow* window)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
	m_WindowTitle = title;
	m_isFullScreen = fullscreen;

	m_WindowInstance = window;
	glfwMakeContextCurrent(m_WindowInstance);

	Fuse2D::InputProps inputProps{};
	inputProps.inputMode = Fuse2D::InputModes::Keyboard;
	inputProps.activeWindow = m_WindowInstance;

	Fuse2D::Input::Input(inputProps);
}

void Fuse2D::Window::Present()
{
	glfwSwapBuffers(m_WindowInstance);
	glfwPollEvents();
}

void Fuse2D::Window::SetWindowTitle(const char* title)
{
	glfwSetWindowTitle(m_WindowInstance, title);
}

void Fuse2D::Window::SetWindowResizable(bool resize)
{
	resize ? glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE) : glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void Fuse2D::Window::SetWindowIcon(std::string path)
{
	GLFWimage* image;
	// Finish this function, need to load image through Resource Manager
	glfwSetWindowIcon(m_WindowInstance, 1, image);
}

void Fuse2D::Window::SetWindowShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(m_WindowInstance, shouldClose);
}

void Fuse2D::Window::ResizeWindow(uint16_t width, uint16_t height)
{
	glfwSetWindowSize(m_WindowInstance, width, height);
}

void Fuse2D::Window::DestroyWindow()
{
	glfwDestroyWindow(m_WindowInstance);
	glfwTerminate();
}