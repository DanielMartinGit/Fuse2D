#pragma once
#include "Fuse2D-Renderer/src/OpenGL/Shaders/OpenGLShader.h"

#include "Fuse2D/Vendor/GLAD/glad.h"
#include "Fuse2D/Vendor/GLM/gtc/type_ptr.hpp"

#include <vector>
#include <iostream>

namespace Fuse2DRendering
{
	class ShaderProgram
	{
		public:
			ShaderProgram();
			~ShaderProgram();

		public:
			static void CreateShader(Fuse2DGraphics::OpenGLShader& shader);

			static void Link();
			static void Use();

			static void ClearProgram();

		public:
			static bool CheckShaderCompilation(GLuint shader);
			static bool CheckShaderLink(GLuint shaderProgram);

		public:
			static void SetBool(const std::string& name, bool value)
			{
				glUniform1i(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
			}

			static void SetInt(const std::string& name, int value)
			{
				glUniform1i(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
			}

			static void SetFloat(const std::string& name, float value)
			{
				glUniform1f(glGetUniformLocation(m_ShaderProgramID, name.c_str()), value);
			}

			static void SetUniformMatrix4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value)
			{
				GLuint location = glGetUniformLocation(GetActiveShaderProgram(), uniformName);
				glUniformMatrix4fv(location, 1, GL_FALSE, value);
			}

			static void SetUniformMatrix4(const char* uniformName, const glm::mat4& matrix)
			{
				GLuint location = glGetUniformLocation(GetActiveShaderProgram(), uniformName);
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
			}

		public:
			static GLuint GetActiveShaderProgram() { return m_ShaderProgramID; }
			static size_t GetShadersLoaded() { return m_Shaders.size(); }

			static Fuse2DGraphics::OpenGLShader* GetShader(GLuint shaderType)
			{
				for (Fuse2DGraphics::OpenGLShader& shader : m_Shaders)
				{
					if (shader.GetShaderType() == shaderType)
						return &shader;
				}
			}

		private:
			inline static std::vector<Fuse2DGraphics::OpenGLShader> m_Shaders;
			inline static uint32_t m_ShaderProgramID;
	};
}