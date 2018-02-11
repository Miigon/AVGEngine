#include "Platform.h"
#include "Shader.h"
#include "OpenGL.h"
#include "Resource.h"
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
	//获取着色器信息
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

	//检测是否为空
	if (shaders.empty())
		return shaderPtr;

	shaders.push_back({ GL_NONE ,"" });

	//创建着色器程序
	const auto program = glCreateProgram();

	auto entry = shaders.begin();

	//循环编译着色器
	while (entry->type != GL_NONE)
	{
		//创建Shader
		const auto shader = glCreateShader(entry->type);

		//读取Shader代码
		std::ifstream shaderFileStream(RESOURCE_ROOT_PATH + entry->fileName);
		std::stringstream shaderStream;
		shaderStream << shaderFileStream.rdbuf();

		const auto source = shaderStream.str();
		
		//检测代码是否为空
		if (source.empty())
		{
			//删除Shader
			for (entry = shaders.begin(); entry->type != GL_NONE; ++entry)
				glDeleteShader(shader);

			break;
		}
		auto sourcePtr = source.c_str();

		//绑定源码
		glShaderSource(shader, 1, &sourcePtr, nullptr);

		//编译源码
		glCompileShader(shader);

		//获取编译状态
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		//如果编译出错
		if (!compiled)
		{
			//获取错误并输出
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			const auto log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader compilation failed: %s", log);
			delete[] log;
			throw std::runtime_error("Shader compilation failed");
		}

		//绑定Shader到着色器程序
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
