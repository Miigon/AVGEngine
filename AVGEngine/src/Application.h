#pragma once

#include <iostream>
#include "util/OpenGL.h"
#include "util/Resource.h"
#include "util/Window.h"
#include "scene/Scene.h"

class Application
{
	//!窗体
	WindowPtr mWindow;
	//!场景
	ScenePtr mScene;
	//!实例
	static Application* mApplication;

public:
	const int windowHeight;
	const int windowWidth;

	void draw()
	{
		mScene->draw();
	}

	void mouseMoveEvent(double mouseX, double mouseY)
	{
		std::cout << mouseX << ";" << mouseY << std::endl;
	}

	void mouseButtonEvent(double mouseX, double mouseY, int buttom, int stage)
	{
		std::cout << buttom << ";" << stage << ";" << mouseX << ";" << mouseY << std::endl;
	}
	
	void tickEvent()
	{
		mScene->tick();
	}

	Application(const int width, const int height) :windowHeight(height), windowWidth(width)
	{
		//实例
		mApplication = this;

		//创建窗体
		mWindow = Window::createWindow("AVGEngine", windowWidth, windowHeight);
		
		//设置回调
		mWindow->setDrawFunc([&]() { draw(); });
		mWindow->setMouseMoveCallback([&](double mouseX, double mouseY) { mouseMoveEvent(mouseX, mouseY); });
		mWindow->setMouseButtonCallback([&](double mouseX, double mouseY, int buttom, int stage)
		{
			mouseButtonEvent(mouseX, mouseY, buttom, stage);
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
	void run(const ScenePtr& startScene)
	{
		mScene = startScene;
		mWindow->joinLoop();
	}

	//!获取程序实例
	static Application* getInstance()
	{
		return mApplication;
	}
};
