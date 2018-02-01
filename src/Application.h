#pragma once

#include "util/Window.h"
#include <GL/glew.h>

class Application
{
	WindowPtr mWindow;
public:
	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void keyEvent(int key, bool isDown)
	{

	}

	void mouseMoveEvent(double mouseX, double mouseY)
	{

	}

	void mouseButtonEvent(double mouseX, double mouseY, bool isLeft, bool isDown)
	{

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
		mWindow->setKeyboardCallback([&](int key, bool isDown) { keyEvent(key, isDown); });
	}

	void run()
	{
		mWindow->joinLoop();
	}
};
