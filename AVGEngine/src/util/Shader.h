#pragma once

#include <memory>
#include <string>
#include "OpenGL.h"

class Shader;
using ShaderPtr = std::shared_ptr<Shader>;

class Shader
{
	//!着色器信息
	struct ShaderInfo
	{
		GLenum       type;
		std::string  fileName;
	};

	GLuint mProgram = 0;

	Shader() = default;

public:
	~Shader() = default;

	Shader(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&&) = delete;
	Shader& operator=(const Shader&) = delete;

	//!加载着色器
	static ShaderPtr loadShader(const char* fileName);

	//!获取Arrtibute位置
	GLuint getAttribLocation(const char* name) const
	{
		return glGetAttribLocation(mProgram, name);
	}

	//!获取Uniform位置
	GLuint getUniformLocation(const char* name) const
	{
		return glGetUniformLocation(mProgram, name);
	}

	//!绑定着色器
	void useShader() const
	{
		glUseProgram(mProgram);
	}
};
