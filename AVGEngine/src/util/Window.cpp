
#include "Window.h"
#include "OpenGL.h"
#ifdef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL_egl.h>
#include <SDL.h>
#endif
#include <stdexcept>

#ifndef _WIN32
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOES;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOES;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOES;
PFNGLISVERTEXARRAYOESPROC glIsVertexArrayOES;
#endif

//SDL窗体
SDL_Window* window = nullptr;

//注册回调函数
void Window::setMouseMoveCallback(const MouseMoveCallback& function) { mMouseMoveCallback = function; }
void Window::setMouseButtonCallback(const MouseButtonCallback& function) { mMouseButtonCallback = function; }
void Window::setTickCallback(const TickCallback& function) { mTickCallback = function; }

//渲染调用
void Window::setDrawFunc(const DrawFunc& function) { mDrawFunc = function; }

//释放
Window::~Window()
{
	SDL_DestroyWindow(window);
}

//事件处理
void Window::poolEvents()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		//退出
		case SDL_QUIT:
			mShouldClose = true;
			break;
		//鼠标移动
		case SDL_MOUSEMOTION:
			mMouseMoveCallback(static_cast<double>(sdlEvent.button.x) / mWindowWidth,
			                   1 - static_cast<double>(sdlEvent.button.y) / mWindowHeight);
			break;
		//鼠标点击
		case SDL_MOUSEBUTTONDOWN:
			mMouseButtonCallback(static_cast<double>(sdlEvent.button.x) / mWindowWidth,
			                     1 - static_cast<double>(sdlEvent.button.y) / mWindowHeight, 
								 sdlEvent.button.button,
			                     sdlEvent.button.state);
			break;
		case SDL_MOUSEBUTTONUP:
			mMouseButtonCallback(static_cast<double>(sdlEvent.button.x) / mWindowWidth,
			                     1 - static_cast<double>(sdlEvent.button.y) / mWindowHeight, 
								 sdlEvent.button.button,
			                     sdlEvent.button.state);
			break;
		default:
			break;
		}
	}
}

//主循环
void Window::joinLoop()
{
	if (!mDrawFunc)
		throw(std::invalid_argument("drawFunc is empty"));

	auto lastTickTime = SDL_GetTicks();

	while(!mShouldClose)
	{
		const auto nowTime = SDL_GetTicks();

		poolEvents();

		while (nowTime - lastTickTime >= 20)
		{
			mTickCallback();
			lastTickTime += 20;
		}
		mDrawFunc();

		SDL_GL_SwapWindow(window);
	}
}

//创建窗体
WindowPtr Window::createWindow(const char* title, const int width, const int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if (window != nullptr)
		throw(std::invalid_argument("An window has already exsited"));

	WindowPtr windowPtr(new Window());

	windowPtr->mWindowHeight = height;
	windowPtr->mWindowWidth = width;

	//初始化并创建窗体
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
		throw(std::runtime_error("Failed to create window"));

	SDL_GL_CreateContext(window);

	//windows下初始化glew
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
		throw(std::runtime_error("Failed to init glew"));
#else
	//其他平台下获取扩展
	glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
	glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
	glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
	glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC)eglGetProcAddress("glIsVertexArrayOES");
#endif

	//启用OpenGL功能
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return windowPtr;
}