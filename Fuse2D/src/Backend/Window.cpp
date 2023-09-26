#define STB_IMAGE_IMPLEMENTATION
#include "Window.h"
#include <filesystem>

Fuse2D::Window::Window()
{
	m_WindowWidth = 0;
	m_WindowHeight = 0;

	m_WindowTitle = "";
	m_isFullScreen = false;
}

Fuse2D::Window::Window(WindowProps props)
{
	if (!glfwInit() || !m_WindowInstance)
	{
		std::cout << "Error: Problem with GLFW" << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	SetWindowResizable(props.IsResizable);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), props.IsFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);	
	glfwMakeContextCurrent(window);

	Initialise(props.Title.c_str(), props.IconPath.c_str(), props.Width, props.Height, props.IsFullScreen, window, props.InputMode);
}
Fuse2D::Window::~Window() {}

void Fuse2D::Window::Initialise(const char* title, const char* iconPath, uint16_t width, uint16_t height, bool fullscreen, GLFWwindow* window, Fuse2D::InputModes inputMode)
{
	m_WindowWidth = width;
	m_WindowHeight = height;
	m_WindowTitle = title;
	m_isFullScreen = fullscreen;
	m_WindowInstance = window;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Failed to initialize GLAD" << std::endl;
	}

	glfwSetFramebufferSizeCallback(m_WindowInstance, FrameBuffer_Size_Callback);

	Fuse2D::InputProps inputProps{};
	inputProps.inputMode = inputMode;
	inputProps.activeWindow = m_WindowInstance;

	Fuse2D::Input::Input(inputProps);

	if (iconPath != "")
		SetWindowIcon(iconPath);

	ShowWindow(true);
}

void Fuse2D::Window::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Fuse2D::Window::Draw()
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

void Fuse2D::Window::SetWindowIcon(const char* iconPath)
{
	if (std::filesystem::exists(iconPath))
	{
		GLFWimage images[1];
		images[0].pixels = stbi_load(iconPath, &images[0].width, &images[0].height, 0, 4);
		glfwSetWindowIcon(m_WindowInstance, 1, images);
		stbi_image_free(images[0].pixels);
	}
	else
		std::cout << "Cannot locate Executable Icon at : " << iconPath << std::endl;
}

void Fuse2D::Window::SetWindowShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(m_WindowInstance, shouldClose);
}

void Fuse2D::Window::ResizeWindow(uint16_t width, uint16_t height)
{
	glfwSetWindowSize(m_WindowInstance, width, height);
}

void Fuse2D::Window::ShowWindow(bool show)
{
	if (show)
		glfwShowWindow(m_WindowInstance);
}

void Fuse2D::Window::FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Fuse2D::Window::Destroy()
{
	glfwDestroyWindow(m_WindowInstance);
	glfwTerminate();
}