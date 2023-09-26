#pragma once
#include <Fuse2D/Vendor/GLM/glm.hpp>
#include <Fuse2D/Vendor/GLM/gtc/matrix_transform.hpp>
#include <Fuse2D/Vendor/GLM/gtc/type_ptr.hpp>
#include <Fuse2D/Vendor/GLAD/glad.h>

#include <string>

namespace Fuse2DRendering
{
	class Shader
	{
		public:
			virtual ~Shader() = default;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void* GetNative() = 0;
			virtual const char* GetShaderCode() = 0;
			virtual const char* GetShaderPath() = 0;
			virtual bool GetIsCompiled() = 0;
			virtual GLuint GetShaderType() = 0;

			virtual void SetIsCompiled(bool status) = 0;
			virtual void SetShaderType(GLuint shaderType) = 0;
			virtual void SetShaderCode(const char* shaderCode) = 0;

			virtual void SetInt(std::string uniformName, int uniformValue) = 0;
			virtual void SetFloat(std::string uniformName, float uniformValue) = 0;
			virtual void SetMat4(std::string uniformName, glm::mat4 uniformValue) = 0;
			virtual void SetMat4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value) = 0;

		public:
			static Shader* Create(std::string filePath, GLuint shaderType);
			static Shader* Create(std::string filePath);
	};
}