#pragma once
#include "Fuse2D/src/Rendering/Shader/Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace Fuse2DGraphics
{
	class OpenGLShader : public Fuse2DRendering::Shader
	{
		public:
			OpenGLShader(std::string filepath, GLuint shaderType);
			OpenGLShader(std::string filePath);

		public:
			// Bind/Unbind functions
			void Bind() override;
			void Unbind() override;

		public:
			// Uniforms
			void SetInt(std::string uniformName, int uniformValue) override;
			void SetFloat(std::string uniformName, float uniformValue) override;
			void SetMat4(std::string uniformName, glm::mat4 uniformValue) override;
			void SetMat4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value) override;

		public:
			// Setters
			void SetShaderType(GLuint shaderType) override;
			void SetShaderCode(const char* shaderCode) override;
			void SetIsCompiled(bool status) override;

		public:
			// Getters
			GLuint GetShaderType() override;
			const char* GetShaderCode() override;
			const char* GetShaderPath() override;
			bool GetIsCompiled() override;
			void* GetNative() override;

		public:
			const char* m_ShaderCode;

		private:
			bool m_IsCompiled;
			const char* m_ShaderPath;

			std::string m_ShaderString;
			uint32_t m_ShaderID;
			GLuint m_ShaderType;
	};
}