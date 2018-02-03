#pragma once

#include "OpenGL.h"
#include <memory>
#include <functional>
#include <boost/noncopyable.hpp>
#include <SDL2/SDL.h>

#define TICK_PER_SECOND 50

class Window;
using WindowPtr= std::shared_ptr<Window>;

/*!������
 * ����������
 * @note Ϊ��֧���ƶ��˲�֧�ֲ�������¼�
 */
class Window :boost::noncopyable
{
public:
	using MouseMoveCallback = std::function<void(double, double)>;
	using MouseButtonCallback = std::function<void(double, double, bool, bool)>;
	using TickCallback = std::function<void()>;
	using DrawFunc = std::function<void()>;

private:
	//�¼�
	//����ƶ�
	Window::MouseMoveCallback mMouseMoveCallback = {};
	//�����
	Window::MouseButtonCallback mMouseButtonCallback = {};
	//tickˢ��
	Window::TickCallback mTickCallback = {};

	//���ƺ���
	Window::DrawFunc mDrawFunc;
	
	//�Ƿ�Ӧ���رմ���
	bool mShouldClose = false;

	//�����С
	int windowHeight, windowWidth;

	//ˢ���¼�
	void poolEvents();

	//�ͷ���Դ
	Window() = default;

public:
	//�ͷ���Դ��
	~Window();

	/*!�����´���
	 * @param title ��������
	 * @param height ����߶�
	 * @param width ������
	 * @note ֻ������һ������
	 */
	static WindowPtr createWindow(const char* title, int width, int height);

	/*!������ѭ��
	 * @note ���drawFuncΪ�գ�����׳��쳣
	 */
	void joinLoop();

	/*!������Ⱦ����
	 * һ����Ⱦ������Ӧ�ڴ˴����
	 * @param function ����\n
	 */
	void setDrawFunc(const DrawFunc& function);

	/*!��������ƶ��ص�
	 * @param function �ص�����\n
	 * ���еĵ�һ��doubleΪx���꣬�ڶ���doubleΪy����
	 */
	void setMouseMoveCallback(const MouseMoveCallback& function);

	/*!����������ص�
	 * @param function �ص�����\n
	 * ���еĵ�һ��doubleΪx���꣬�ڶ���doubleΪy����\n
	 * ��һ��boolΪ�Ƿ���������ڶ���boolΪ�Ƿ���
	 */
	void setMouseButtonCallback(const MouseButtonCallback& function);

	/*!����tick�ص�
	* @param function �ص�����\n
	* �˺���ÿ��0.02������һ��
	*/
	void setTickCallback(const TickCallback& function);
};