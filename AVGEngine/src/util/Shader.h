#pragma once

#include <memory>
#include <string>
#include "OpenGL.h"

class Shader;
using ShaderPtr = std::shared_ptr<Shader>;

class Shader
{
	//!��ɫ����Ϣ
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

	//!������ɫ��
	static ShaderPtr loadShader(const char* fileName);

	//!��ȡArrtibuteλ��
	GLuint getAttribLocation(const char* name) const
	{
		return glGetAttribLocation(mProgram, name);
	}

	//!��ȡUniformλ��
	GLuint getUniformLocation(const char* name) const
	{
		return glGetUniformLocation(mProgram, name);
	}

	//!����ɫ��
	void useShader() const
	{
		glUseProgram(mProgram);
	}
};
