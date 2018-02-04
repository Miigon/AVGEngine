
#include "Window.h"
#include "OpenGL.h"
#include <SDL2/SDL.h>
#include <stdexcept>

//SDL����
SDL_Window* window = nullptr;

//ע��ص�����
void Window::setMouseMoveCallback(const MouseMoveCallback& function) { mMouseMoveCallback = function; }
void Window::setMouseButtonCallback(const MouseButtonCallback& function) { mMouseButtonCallback = function; }
void Window::setTickCallback(const TickCallback& function) { mTickCallback = function; }

//��Ⱦ����
void Window::setDrawFunc(const DrawFunc& function) { mDrawFunc = function; }

//�ͷ�
Window::~Window()
{
	SDL_DestroyWindow(window);
}

//�¼�����
void Window::poolEvents()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		//�˳�
		case SDL_QUIT:
			mShouldClose = true;
			break;
		//����ƶ�
		case SDL_MOUSEMOTION:
			mMouseMoveCallback(sdlEvent.button.x, sdlEvent.button.y);
			break;
		//�����
		case SDL_MOUSEBUTTONDOWN:
			mMouseButtonCallback(sdlEvent.button.x, sdlEvent.button.y, sdlEvent.button.button, sdlEvent.button.state);
			break;
		default:
			break;
		}
	}
}

//��ѭ��
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

//��������
WindowPtr Window::createWindow(const char* title, const int width, const int height)
{
	if (window != nullptr)
		throw(std::invalid_argument("An window has already exsited"));

	WindowPtr windowPtr(new Window());

	windowPtr->mWindowHeight = height;
	windowPtr->mWindowWidth = width;

	//��ʼ������������
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
		throw(std::runtime_error("Failed to create window"));

	SDL_GL_CreateContext(window);

	//windows�³�ʼ��glew
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
		throw(std::runtime_error("Failed to init glew"));
#endif

	return windowPtr;
}