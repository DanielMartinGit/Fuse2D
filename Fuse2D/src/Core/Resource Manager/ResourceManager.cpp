#define STB_IMAGE_IMPLEMENTATION
#include "ResourceManager.h"

Fuse2D::ResourceManager::ResourceManager() {}
Fuse2D::ResourceManager::~ResourceManager() {}

void Fuse2D::ResourceManager::LoadTexture(const char* texturePath)
{
	int width = 0;
	int height = 0;
	int nrChannels = 0;

	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	if (data)
	{
		switch (nrChannels)
		{

		}
	}

	stbi_image_free(data);
}

std::vector<char> Fuse2D::ResourceManager::LoadShader(const std::string&  shaderPath)
{
	std::ifstream file(shaderPath, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}