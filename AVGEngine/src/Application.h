#pragma once

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
		mWindow = Window::createWindow("AVGEngine", 256, 256);
		mWindow->setDrawFunc([&]() { draw(); });
		mWindow->setMouseMoveCallback([&](double mouseX, double mouseY) { mouseMoveEvent(mouseX, mouseY); });
		mWindow->setMouseButtonCallback([&](double mouseX, double mouseY, bool isLeft, bool isDown)
		{
			mouseButtonEvent(mouseX, mouseY, isLeft, isDown);
		});
		mWindow->setTickCallback([&]() { tickEvent(); });
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
