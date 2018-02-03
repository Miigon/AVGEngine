#include "Window.h"

#include <stdexcept>

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
			mMouseMoveCallback(sdlEvent.button.x, sdlEvent.button.y);
			break;
		//鼠标点击
		case SDL_MOUSEBUTTONDOWN:
			mMouseButtonCallback(sdlEvent.button.x, sdlEvent.button.y, sdlEvent.button.button, sdlEvent.button.state);
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
	if (window != nullptr)
		throw(std::invalid_argument("An window has already exsited"));

	WindowPtr windowPtr(new Window());

	windowPtr->windowHeight = height;
	windowPtr->windowWidth = width;

	//初始化并创建窗体
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
		throw(std::runtime_error("Failed to create window"));

	SDL_GL_CreateContext(window);

	//windows下初始化glew
#ifdef _WIN32
	if (glewInit() != GLEW_OK)
		throw(std::runtime_error("Failed to init glew"));
#endif

	return windowPtr;
}