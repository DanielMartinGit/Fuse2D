#pragma once
#include "Fuse2D/src/Rendering/ShaderProgram/ShaderProgram.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace Fuse2D
{
	class AssetManager
	{
		public:
			AssetManager() {}
			~AssetManager() {}

		public:
			static Fuse2DGraphics::OpenGLShader* CreateShader(std::string shaderCodePath, GLuint shaderType)
			{
				Fuse2DGraphics::OpenGLShader* shader = new Fuse2DGraphics::OpenGLShader(shaderCodePath, shaderType);
				return shader;
			}

			static std::string LoadTextFile(std::string textPath)
			{
				if (std::filesystem::exists(textPath))
				{
					std::string text;
					std::stringstream textStream;

					std::ifstream textFile(textPath);
					textStream << textFile.rdbuf();

					return text = textStream.str();

					textFile.close();
				}
				else
					std::cout << "Couldn't locate shader file at: " << textPath << std::endl;
			}

			// Will return a Fuse2D::Texture Object (Yet to be created)			
			static void LoadTexture(const char* texturePath)
			{

			}

			public:
				static inline std::string shaderText;
	};
}