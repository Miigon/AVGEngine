#include "Window.h"

#ifdef WIN32
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

//glfw����
GLFWwindow* glfwWindow;

//�ص�����
Window::MouseMoveCallback mouseMoveCallback;
Window::MouseButtonCallback mouseButtonCallback;
Window::TickCallback tickCallback = {};

//��Ⱦ����
Window::DrawFunc drawFunc;

//��¼���λ��
double mouseX = 0;
double mouseY = 0;

//ע��ص�����
void Window::setMouseMoveCallback(const MouseMoveCallback& function) { mouseMoveCallback = function; }
void Window::setMouseButtonCallback(const MouseButtonCallback& function) { mouseButtonCallback = function; }
void Window::setTickCallback(const TickCallback& function) { tickCallback = function; }

//��Ⱦ����
void Window::setDrawFunc(const DrawFunc& function) { drawFunc = function; }

//�ͷ�
Window::~Window() { glfwTerminate(); }

//��ѭ��
void Window::joinLoop()
{
	if (!drawFunc)
		throw(std::invalid_argument("drawFunc is empty"));

	glfwShowWindow(glfwWindow);

	auto lastTickTime = glfwGetTime();

	while(!glfwWindowShouldClose(glfwWindow))
	{
		const auto nowTime = glfwGetTime();

		glfwPollEvents();

		while (nowTime - lastTickTime >= 0.02)
		{
			tickCallback();
			lastTickTime += 0.02;
		}
		drawFunc();

		glfwSwapBuffers(glfwWindow);
	}
}

//��������
WindowPtr Window::createWindow(const char* title, const int width, const int height)
{
	if (glfwWindow != nullptr)
		throw(std::invalid_argument("An window has already exsited"));

	WindowPtr windowPtr(new Window());

	//��ʼ������������
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!glfwWindow)
		throw(std::runtime_error("Failed to create window"));
	glfwMakeContextCurrent(glfwWindow);
	if (glewInit() != GLEW_OK)
		throw(std::runtime_error("Failed to init glew"));

	if (mouseButtonCallback)
		glfwSetMouseButtonCallback(glfwWindow, [](GLFWwindow*, int button, int action, int)
		{
			//�����ܳ�����Ҽ�������¼�
			if (!(button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT))
				return;

			mouseButtonCallback(mouseX, mouseY, button == GLFW_MOUSE_BUTTON_LEFT, action == GLFW_PRESS);
		});

	if (mouseMoveCallback)
		glfwSetCursorPosCallback(glfwWindow, [](GLFWwindow*, double posX, double posY)
		{
			mouseX = posX;
			mouseY = posY;
			mouseMoveCallback(mouseX, mouseY);
		});

	return windowPtr;
}
#else
	#error ��֧�ֵ�ϵͳ��
#endif