#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <stdexcept>
#include <vector>

#include "Shader.h"

Shader::Shader(std::string vertexSource, std::string fragmentSource) :
	m_vertexID(0), 
	m_fragmentID(0),
	m_programID(0),
	m_vertexSource(vertexSource),
	m_fragmentSource(fragmentSource)
{
	if(!m_vertexSource.empty() && !m_fragmentSource.empty())
		if(!load())
			throw std::logic_error("Shader could not be loaded correctly");
}

Shader::Shader(const Shader& shad) :
	Shader(shad.m_vertexSource, shad.m_fragmentSource)
{}

Shader::~Shader()
{
	glDeleteProgram(m_programID);
	m_programID = 0;
}

const Shader& Shader::operator=(const Shader& shad)
{
	if(m_programID != 0)
		glDeleteProgram(m_programID);

	m_vertexID = 0;
	m_fragmentID = 0;
	m_programID = 0;
	m_vertexSource = shad.m_vertexSource;
	m_fragmentSource = shad.m_fragmentSource;
	
	if(!m_vertexSource.empty() && !m_fragmentSource.empty())
		if(!load())
			throw std::logic_error("Shader could not be loaded correctly");
	
	return *this;
}

void Shader::setSources(std::string const vertexSource, std::string const fragmentSource)
{
	if(m_programID != 0)
		glDeleteProgram(m_programID);

	m_vertexID = 0;
	m_fragmentID = 0;
	m_programID = 0;
	m_vertexSource = vertexSource;
	m_fragmentSource = fragmentSource;
	
	if(!m_vertexSource.empty() && !m_fragmentSource.empty())
		if(!load())
			throw std::logic_error("Shader could not be loaded correctly");
}

GLuint Shader::getProgramID() const
{
    return m_programID;
}

bool Shader::load()
{
	if(!compileShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
		return false;

	if(!compileShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
		return false;

	m_programID = glCreateProgram();

	glAttachShader(m_programID, m_vertexID);
	glAttachShader(m_programID, m_fragmentID);

	glLinkProgram(m_programID);

	GLint errorLink(0);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &errorLink);

	if(errorLink != GL_TRUE)
	{
		GLint errorSize(0);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);

		char *error = new char[(GLsizeiptr)errorSize + 1];

		glGetShaderInfoLog(m_programID, errorSize, &errorSize, error);
		error[errorSize] = '\0';

		std::cout << error << std::endl;

		delete[] error;
		glDeleteProgram(m_programID);

		return false;
	}

	glDetachShader(m_programID, m_vertexID);
	glDetachShader(m_programID, m_fragmentID);
	
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);

	return true;
}

bool Shader::compileShader(GLuint &shader, const GLenum type, const std::string& sourceFile)
{
	shader = glCreateShader(type);

	if(shader == 0)
	{
		std::cout << "Error, shader (" << type << ") does not exists" << std::endl;
		return false;
	}

	std::ifstream file(sourceFile.c_str());

	if(!file)
	{
		std::cout << "Error, file " << sourceFile << " not found" << std::endl;
		glDeleteShader(shader);

		return false;
	}

	std::string line;
	std::string source;

	while(getline(file, line))
		source += line + '\n';

	file.close();

	const GLchar* sourceString = source.c_str();

	glShaderSource(shader, 1, &sourceString, 0);

	glCompileShader(shader);

	GLint compilationError(0);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationError);

	if(compilationError != GL_TRUE)
	{
		GLint errorSize(0);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);

		char *error = new char[(GLsizeiptr)errorSize + 1];

		glGetShaderInfoLog(shader, errorSize, &errorSize, error);
		error[errorSize] = '\0';

		std::cout << error << std::endl;

		delete[] error;
		glDeleteShader(shader);

		return false;
	}

	return true;
}
