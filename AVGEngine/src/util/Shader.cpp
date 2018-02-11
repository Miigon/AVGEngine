#include "Platform.h"
#include "Shader.h"
#include "OpenGL.h"
#include <fstream>
#include <sstream>
#include <vector>
#ifdef AVG_DESKTOP
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

ShaderPtr Shader::loadShader(const char* fileName)
{
	//��ȡ��ɫ����Ϣ
	std::vector<ShaderInfo> shaders;
	std::ifstream shaderFile(fileName);
	while(!shaderFile.eof())
	{
		std::string shaderFileName;
		std::string shaderType;

		shaderFile >> shaderFileName;
		shaderFile >> shaderType;

		if (shaderType == "GL_VERTEX_SHADER")
			shaders.push_back({ GL_VERTEX_SHADER, shaderFileName });
		else if (shaderType == "GL_FRAGMENT_SHADER")
			shaders.push_back({ GL_FRAGMENT_SHADER, shaderFileName });
		else
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unknown shader type : %s", shaderType.c_str());
	}

	ShaderPtr shaderPtr(new Shader());

	//����Ƿ�Ϊ��
	if (shaders.empty())
		return shaderPtr;

	shaders.push_back({ GL_NONE ,"" });

	//������ɫ������
	const auto program = glCreateProgram();

	auto entry = shaders.begin();

	//ѭ��������ɫ��
	while (entry->type != GL_NONE)
	{
		//����Shader
		const auto shader = glCreateShader(entry->type);

		//��ȡShader����
		std::ifstream shaderFileStream(entry->fileName);
		std::stringstream shaderStream;
		shaderStream << shaderFileStream.rdbuf();

		const auto source = shaderStream.str();
		
		//�������Ƿ�Ϊ��
		if (source.empty())
		{
			//ɾ��Shader
			for (entry = shaders.begin(); entry->type != GL_NONE; ++entry)
				glDeleteShader(shader);

			break;
		}
		auto sourcePtr = source.c_str();

		//��Դ��
		glShaderSource(shader, 1, &sourcePtr, nullptr);

		//����Դ��
		glCompileShader(shader);

		//��ȡ����״̬
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		//����������
		if (!compiled)
		{
			//��ȡ�������
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			const auto log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader compilation failed: %s", log);
			delete[] log;
			throw std::runtime_error("Shader compilation failed");
		}

		//��Shader����ɫ������
		glAttachShader(program, shader);

		++entry;
	}
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		const auto log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader linking failed: ");
		delete[] log;
		throw std::runtime_error("Shader linking failed");
	}
	glUseProgram(program);
	shaderPtr->mProgram = program;

	return shaderPtr;
}
