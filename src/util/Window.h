#pragma once

#include <memory>
#include <functional>

class Window;
using WindowPtr= std::shared_ptr<Window>;

/*!������
 * ����������
 */
class Window
{
	Window() = default;
public:
	using KeyboardCallback = std::function<void(int, bool)>;
	using MouseMoveCallback = std::function<void(double, double)>;
	using MouseButtonCallback = std::function<void(double, double, bool, bool)>;

	using DrawFunc = std::function<void()>;

	Window(const Window&) = delete;
	Window(const Window&&) = delete;
	Window operator =(const Window&) = delete;
	Window operator =(const Window&&) = delete;

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

	/*!���ü����¼��ص�
	 * @param function �ص�����\n
	 * ���е�intΪ�������ԣ�boolΪ�Ƿ���
	 */
	void setKeyboardCallback(const KeyboardCallback& function);

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
};