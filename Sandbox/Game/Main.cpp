#include "Fuse2D/src/Core/Resource Manager/ResourceManager.h"
#include "Sandbox/Game/Scene/TestScene.h"
#include "Fuse2D/src/Utils/DeltaTime/DeltaTime.h"

int main()
{
	Fuse2D::WindowProps windowProps {};
	windowProps.Title = "Flappy Bird";
	windowProps.Width = 1024;
	windowProps.Height = 768;
	windowProps.IsFullScreen = false;
	windowProps.IsResizable = false;

	Fuse2D::Window window = Fuse2D::Window(windowProps);
	
	Sandbox::TestScene testScene(&window);
	testScene.OnSceneLoaded();

	while (!window.GetWindowShouldClose())
	{
		Fuse2DUtils::DeltaTime::CalculateDeltaTime();

		testScene.OnSceneInput(Fuse2DUtils::DeltaTime::GetDeltaTime());
		testScene.OnSceneUpdate(Fuse2DUtils::DeltaTime::GetDeltaTime());
		testScene.OnSceneRender();
	
		window.Present();
	}

	testScene.OnSceneUnloaded();
	window.DestroyWindow();
}