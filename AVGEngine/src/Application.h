#pragma once

#include "util/Resource.h"
#include "util/Window.h"
#include "scene/IScene.h"
#include <GL/glew.h>

class Application
{
	//����
	WindowPtr mWindow;

	//����
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
		//��������
		mWindow = Window::createWindow("AVGEngine", 256, 256);
		
		//���ûص�
		mWindow->setDrawFunc([&]() { draw(); });
		mWindow->setMouseMoveCallback([&](double mouseX, double mouseY) { mouseMoveEvent(mouseX, mouseY); });
		mWindow->setMouseButtonCallback([&](double mouseX, double mouseY, bool isLeft, bool isDown)
		{
			mouseButtonEvent(mouseX, mouseY, isLeft, isDown);
		});
		mWindow->setTickCallback([&]() { tickEvent(); });

		//��ʼ����OpenGL��ص�����
		glEnable(GL_TEXTURE_2D);

		//��ʼ����Դ
		Resource::init();
	}

	/*!���г���
	 * @param startScene ��ʼʱ��ʾ�ĳ���
	 */
	void run(const IScenePtr& startScene)
	{
		mScene = startScene;
		mWindow->joinLoop();
	}
};
