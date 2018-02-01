#pragma once

#include "util/Resource.h"
#include "util/Window.h"
#include "scene/IScene.h"
#include <GL/glew.h>

class Application
{
	//窗体
	WindowPtr mWindow;

	//场景
	IScenePtr mScene;

public:
	void draw()
	{
		mScene->draw();
	}

	void mouseMoveEvent(double mouseX, double mouseY)
	{

	}

	void mouseButtonEvent(double mouseX, double mouseY, bool isLeft, bool isDown)
	{

	}
	
	void tickEvent()
	{
		mScene->tick();
	}

	Application()
	{
		//创建窗体
		mWindow = Window::createWindow("AVGEngine", 256, 256);
		
		//设置回调
		mWindow->setDrawFunc([&]() { draw(); });
		mWindow->setMouseMoveCallback([&](double mouseX, double mouseY) { mouseMoveEvent(mouseX, mouseY); });
		mWindow->setMouseButtonCallback([&](double mouseX, double mouseY, bool isLeft, bool isDown)
		{
			mouseButtonEvent(mouseX, mouseY, isLeft, isDown);
		});
		mWindow->setTickCallback([&]() { tickEvent(); });

		//初始化与OpenGL相关的内容
		glEnable(GL_TEXTURE_2D);

		//初始化资源
		Resource::init();
	}

	/*!运行程序
	 * @param startScene 开始时显示的场景
	 */
	void run(const IScenePtr& startScene)
	{
		mScene = startScene;
		mWindow->joinLoop();
	}
};
