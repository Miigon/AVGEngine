#include "Label.h"
#include "../Application.h"
#include "../util/Shader.h"

GLuint vao = 0;
GLuint buffer = 0;

void Label::draw()
{
	const auto windowWidth = static_cast<float>(Application::getInstance()->windowWidth);
	const auto windowHeight = static_cast<float>(Application::getInstance()->windowHeight);

	const auto poxX = static_cast<float>(getDouble("pos.x"));
	const auto poxY = static_cast<float>(getDouble("pos.y"));

	const auto height = static_cast<float>(getDouble("size.height"));
	const auto width = static_cast<float>(getDouble("size.width"));

	const auto shader = Resource::getShader("res.shader.Simple2DShader.shader");

	const auto attributeLoc = shader->getAttribLocation("vPosition");

	GLfloat data[6][3]
	{
		poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1, 0.0,
		poxX / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0,
		(poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0,
		poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1,0.0,
		(poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0,
		(poxX + width) / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1,0.0
	};

	if (!vao)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}
	if (!buffer)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(attributeLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(attributeLoc);

	shader->useShader();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	/*
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d(poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d(poxX / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1);
	
	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d((poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d(poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d((poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1);

	glColor3f(1.0f, 0.0f, 0.3f);
	glVertex2d((poxX + width) / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1);

	glEnd();*/
}
