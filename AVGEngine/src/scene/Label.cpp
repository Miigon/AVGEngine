#include "Label.h"
#include "../Application.h"
#include "../util/Shader.h"
#include "../util/Texture.h"

void Label::draw()
{
	const auto simpleShader = Resource::getShader("res.shader.Simple2D.shader");
	const auto textureShader = Resource::getShader("res.shader.Simple2DTexture.shader");
	
	glBindVertexArray(mLabelBackgroundVao);
	simpleShader->useShader();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(mLabelTextVao);
	textureShader->useShader();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Label::init(const Config& labelConfig)
{
	//初始化控件
	if (labelConfig.has("[Widget]"))
		//有Widget标签
		Widget::init(*labelConfig.getAsConfig("[Widget]"));
	else
		//无Widget标签
		Widget::init(labelConfig);

#ifdef _TEST_
	return;
#endif
	const auto windowWidth = static_cast<float>(Application::getInstance()->windowWidth);
	const auto windowHeight = static_cast<float>(Application::getInstance()->windowHeight);

	const auto poxX = static_cast<float>(getDouble("pos.x"));
	const auto poxY = static_cast<float>(getDouble("pos.y"));

	const auto height = static_cast<float>(getDouble("size.height"));
	const auto width = static_cast<float>(getDouble("size.width"));

	const auto baclGroundColorR = static_cast<float>(getDouble("background.r"));
	const auto baclGroundColorG = static_cast<float>(getDouble("background.g"));
	const auto baclGroundColorB = static_cast<float>(getDouble("background.b"));
	const auto baclGroundColorA = static_cast<float>(getDouble("background.a"));

	//顶点数据
	GLfloat vertexDataWithTexture[6][5]
	{
		poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1, 0.0f,0.0f,0.0f,
		poxX / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0f,0.0f,1.0f,
		(poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0f,1.0f,1.0f,
		poxX / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1,0.0f,0.0f,0.0f,
		(poxX + width) / windowWidth * 2 - 1, (poxY + height) / windowHeight * 2 - 1,0.0f,1.0f,1.0f,
		(poxX + width) / windowWidth * 2 - 1, poxY / windowHeight * 2 - 1,0.0f,1.0f,0.0f
	};

	//创建VBO
	glGenBuffers(1, &mLabelVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mLabelVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexDataWithTexture), &vertexDataWithTexture, GL_STATIC_DRAW);

	/***********Label背景***********/
	//创建VAO
	glGenVertexArrays(1, &mLabelBackgroundVao);
	glBindVertexArray(mLabelBackgroundVao);

	//绑定顶点属性(使用simple2dshader)
	const auto simpleShader = Resource::getShader("res.shader.Simple2D.shader");
	const auto simpleShaderAttributeLoc = simpleShader->getAttribLocation("vPosition");

	simpleShader->useShader();
	glVertexAttribPointer(simpleShaderAttributeLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(simpleShaderAttributeLoc);

	//设置颜色
	const auto uniformLoc = simpleShader->getUniformLocation("fColor");
	glUniform4f(uniformLoc, baclGroundColorR, baclGroundColorG, baclGroundColorB, baclGroundColorA);
	
	/***********Label文字***********/
	//创建VAO
	glGenVertexArrays(1, &mLabelTextVao);
	glBindVertexArray(mLabelTextVao);

	//绑定顶点属性(使用simple2dshader)
	const auto textureShader = Resource::getShader("res.shader.Simple2DTexture.shader");
	const auto textureShaderVertexAttributeLoc = textureShader->getAttribLocation("vPosition");
	const auto textureShaderTextureAttributeLoc = textureShader->getAttribLocation("vTextureCoord");

	textureShader->useShader();

	glVertexAttribPointer(textureShaderVertexAttributeLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
	glVertexAttribPointer(textureShaderTextureAttributeLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(textureShaderVertexAttributeLoc);
	glEnableVertexAttribArray(textureShaderTextureAttributeLoc);

	//设置纹理
	const auto textureShaderTextureLoc = textureShader->getUniformLocation("texture");
	const auto textureId = static_cast<GLuint>(*Resource::getTexture("res.image.MainMenuBackground.png"));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glUniform1i(textureShaderTextureLoc, 0);
}