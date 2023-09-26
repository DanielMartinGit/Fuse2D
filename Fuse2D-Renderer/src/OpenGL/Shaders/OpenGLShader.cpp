#include "Fuse2D-Renderer/src/OpenGL/Shaders/OpenGLShader.h"
#include <Fuse2D/Vendor/GLAD/glad.h>

Fuse2DGraphics::OpenGLShader::OpenGLShader(std::string filePath, GLuint shaderType)
{
	m_ShaderCode = "";
	m_ShaderPath = "";
	m_ShaderType = 0;
	m_ShaderID = 0;

	m_IsCompiled = false;

	std::stringstream shaderStream;

	std::ifstream shaderFile(filePath);
	shaderStream << shaderFile.rdbuf();

	m_ShaderString = shaderStream.str();
	m_ShaderCode = m_ShaderString.c_str();
	m_ShaderPath = filePath.c_str();

	m_ShaderType = shaderType;

	shaderFile.close();
}

Fuse2DGraphics::OpenGLShader::OpenGLShader(std::string filePath)
{
	m_ShaderCode = "";
	m_ShaderPath = "";
	m_ShaderType = 0;
	m_ShaderID = 0;

	m_IsCompiled = false;

	std::ifstream stream(filePath);
	std::string line;

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	// Parsing Shader File
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	std::string _strVertexSource = ss[0].str();
	std::string _strFragmentSource = ss[1].str();

	const char* vertex = _strVertexSource.c_str();
	const char* fragment = _strFragmentSource.c_str();


	// Creating Vertex Shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, nullptr);
	glCompileShader(vertexShader);

	// Debugging Vertex Shader
	int vertResult;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertResult);
	if (vertResult == GL_FALSE)
	{
		int length;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(vertexShader, length, &length, message);

		std::cout << "Failed To Compile Vertex: " << std::endl;
		std::cout << message << std::endl;
	}

	// Creating Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, nullptr);
	glCompileShader(fragmentShader);

	// Debugging Fragment Shader
	int fragResult;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragResult);
	if (fragResult == GL_FALSE)
	{
		int length;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(fragmentShader, length, &length, message);

		std::cout << "Failed To Compile Fragment: " << std::endl;
		std::cout << message << std::endl;
	}

	// Creating Shader Program
	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, fragmentShader);
	glLinkProgram(m_ShaderID);
}

void Fuse2DGraphics::OpenGLShader::Bind()
{
	glUseProgram(m_ShaderID);
}

void Fuse2DGraphics::OpenGLShader::Unbind()
{
	glUseProgram(0);
}

void* Fuse2DGraphics::OpenGLShader::GetNative()
{
	return (void*)m_ShaderID;
}

GLuint Fuse2DGraphics::OpenGLShader::GetShaderType()
{
	return m_ShaderType;
}

bool Fuse2DGraphics::OpenGLShader::GetIsCompiled()
{
	return m_IsCompiled;
}

const char* Fuse2DGraphics::OpenGLShader::GetShaderCode()
{
	return m_ShaderCode;
}

const char* Fuse2DGraphics::OpenGLShader::GetShaderPath()
{
	return m_ShaderPath;
}

void Fuse2DGraphics::OpenGLShader::SetShaderType(GLuint shaderType)
{
	m_ShaderType = shaderType;
}

void Fuse2DGraphics::OpenGLShader::SetIsCompiled(bool status)
{
	m_IsCompiled = status;
}

void Fuse2DGraphics::OpenGLShader::SetShaderCode(const char* shaderCode)
{
	m_ShaderCode = shaderCode;
}

void Fuse2DGraphics::OpenGLShader::SetInt(std::string uniformName, int uniformValue)
{
	unsigned int uniformLocation = glGetUniformLocation(m_ShaderID, uniformName.c_str());
	glUniform1i(uniformLocation, uniformValue);
}

void Fuse2DGraphics::OpenGLShader::SetFloat(std::string uniformName, float uniformValue)
{
	unsigned int uniformLocation = glGetUniformLocation(m_ShaderID, uniformName.c_str());
	glUniform1f(uniformLocation, uniformValue);
}

void Fuse2DGraphics::OpenGLShader::SetMat4(std::string uniformName, glm::mat4 uniformValue)
{
	unsigned int modelLoc = glGetUniformLocation(m_ShaderID, uniformName.c_str());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(uniformValue));
}

void Fuse2DGraphics::OpenGLShader::SetMat4fv(const char* uniformName, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLuint location = glGetUniformLocation(m_ShaderID, uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}