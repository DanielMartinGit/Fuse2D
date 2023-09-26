#include "ShaderProgram.h"

Fuse2DRendering::ShaderProgram::ShaderProgram()
{
	m_ShaderProgramID = 0;
}

Fuse2DRendering::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ShaderProgramID);
}

void Fuse2DRendering::ShaderProgram::CreateShader(Fuse2DGraphics::OpenGLShader& shader)
{
	shader.SetShaderType(glCreateShader(shader.GetShaderType()));

	glShaderSource(shader.GetShaderType(), 1, &shader.m_ShaderCode, NULL);
	glCompileShader(shader.GetShaderType());

	if (CheckShaderCompilation(shader.GetShaderType()))
	{
		shader.SetIsCompiled(true);
		m_Shaders.push_back(shader);
	}
}

void Fuse2DRendering::ShaderProgram::Link()
{
	m_ShaderProgramID = glCreateProgram();

	for (auto shader : m_Shaders)
	{
		if (shader.GetIsCompiled())
			glAttachShader(m_ShaderProgramID, shader.GetShaderType());
	}

	glLinkProgram(m_ShaderProgramID);

	if (CheckShaderLink(m_ShaderProgramID))
	{
		for (auto shader : m_Shaders)
		{
			glDeleteShader(shader.GetShaderType());
		}
	}
}

void Fuse2DRendering::ShaderProgram::Use()
{
	glUseProgram(m_ShaderProgramID);
}

bool Fuse2DRendering::ShaderProgram::CheckShaderCompilation(GLuint shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}
	
		return true;
}

bool Fuse2DRendering::ShaderProgram::CheckShaderLink(GLuint shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}
	else
		return true;
}

void Fuse2DRendering::ShaderProgram::ClearProgram()
{
	m_ShaderProgramID = 0;
	m_Shaders.clear();
}