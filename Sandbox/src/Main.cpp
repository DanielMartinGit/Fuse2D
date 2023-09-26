#include "Fuse2D/src/Backend/Window.h"
#include "Scenes/SandboxScene.h"

Fuse2D::Window window;
Sandbox::SandboxScene testScene;

int main()
{
	// Create the Window
	Fuse2D::WindowProps windowProps {};
	windowProps.Width = 1024;
	windowProps.Height = 768;
	windowProps.Title = "Sandbox";
	windowProps.IconPath = "resources/icons/icon.png";
	windowProps.IsFullScreen = false;
	windowProps.IsResizable = false;
	windowProps.InputMode = Fuse2D::InputModes::Keyboard;
	window = Fuse2D::Window(windowProps);

	// Initialise the main Game scene
	testScene.OnSceneLoaded();

	// Run game while window is open
	while (!window.GetWindowShouldClose())
	{
		// CLear the window before drawing
		window.Clear(0.5f, 0.5f, 1.0f, 1.0f);
		
		// Update the current running scene
		testScene.OnSceneInput(0.0f);
		testScene.OnSceneUpdate(0.0f);
		testScene.OnSceneRender();

		// Draw to the Window
		window.Draw(); 
	}

	// On Shutdown of Game
	testScene.OnSceneUnloaded();
	window.Destroy();
}