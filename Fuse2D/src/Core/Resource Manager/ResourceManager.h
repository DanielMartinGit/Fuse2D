#pragma once
#include "Fuse2D/Vendor/STB/stb_image.h"

#include <fstream>
#include <vector>

namespace Fuse2D
{
	class ResourceManager
	{
		public:
			ResourceManager();
			~ResourceManager();

		public:
			void LoadTexture(const char* texturePath);
			static std::vector<char> LoadShader(const std::string& shaderPath);
	};	
}