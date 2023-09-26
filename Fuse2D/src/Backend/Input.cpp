#include "Input.h"

Fuse2D::Input::Input()
{
	m_ActiveWindow = nullptr;
	m_InputMode = InputModes::Keyboard;
}

Fuse2D::Input::Input(InputProps props)
{
	m_ActiveWindow = props.activeWindow;
	m_InputMode = props.inputMode;

	SetCallbacks();
}

Fuse2D::Input::~Input() {}

bool Fuse2D::Input::IsKeyUp(int key)
{
	int state = glfwGetKey(m_ActiveWindow, key);

	if (state == GLFW_RELEASE)
		return true;

	return false;
}

bool Fuse2D::Input::IsKeyDown(int key)
{
	int state = glfwGetKey(m_ActiveWindow, key);

	if (state == GLFW_REPEAT)
		return true;

	return false;
}

bool Fuse2D::Input::IsKeyPressed(int key)
{
	int state = glfwGetKey(m_ActiveWindow, key);

	if (state == GLFW_PRESS)
		return true;

	return false;
}

bool Fuse2D::Input::IsMouseButtonUp(int key)
{
	int state = glfwGetMouseButton(m_ActiveWindow, key);

	if (state == GLFW_RELEASE)
		return true;

	return false;
}

bool Fuse2D::Input::IsMouseButtonDown(int key)
{
	int state = glfwGetMouseButton(m_ActiveWindow, key);

	if (state == GLFW_REPEAT)
		return true;

	return false;
}

bool Fuse2D::Input::IsMouseButtonPressed(int key)
{
	int state = glfwGetMouseButton(m_ActiveWindow, key);

	if (state == GLFW_PRESS)
		return true;

	return false;
}

void Fuse2D::Input::SetCursorEnabled(bool enabled)
{
	if (enabled)
		glfwSetInputMode(m_ActiveWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(m_ActiveWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Fuse2D::Input::ChangeInputMode(InputModes mode)
{
	m_InputMode = mode;
}

void Fuse2D::Input::SetCallbacks()
{
	glfwSetKeyCallback(m_ActiveWindow, Input::KeyCallback);
	glfwSetMouseButtonCallback(m_ActiveWindow, Input::MouseButtonCallback);
	glfwSetCursorPosCallback(m_ActiveWindow, Input::MousePositionCallback);
	glfwSetScrollCallback(m_ActiveWindow, Input::MouseScrollCallback);
}

void Fuse2D::Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	IsKeyUp(key);
	IsKeyDown(key);
	IsKeyPressed(key);
}

void Fuse2D::Input::MouseButtonCallback(GLFWwindow* window, int key, int action, int mods)
{
	IsMouseButtonUp(key);
	IsMouseButtonDown(key);
	IsMouseButtonPressed(key);
}

void Fuse2D::Input::MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	SetMouseScreenPos(glm::vec2(xPos, yPos));
}

void Fuse2D::Input::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	SetMouseScrollWheelY(yOffset);
}