#pragma once

#include <memory>
#include <functional>

class Window;
using WindowPtr= std::shared_ptr<Window>;

/*!窗体类
 * 负责管理窗体等
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

	//释放资源等
	~Window();

	/*!创建新窗体
	 * @param title 窗体名称
	 * @param height 窗体高度
	 * @param width 窗体宽度
	 * @note 只允许创建一个窗体
	 */
	static WindowPtr createWindow(const char* title, int width, int height);

	/*!进入主循环
	 * @note 如果drawFunc为空，则会抛出异常
	 */
	void joinLoop();

	/*!设置渲染调用
	 * 一切渲染操作都应在此处完成
	 * @param function 函数\n
	 */
	void setDrawFunc(const DrawFunc& function);

	/*!设置键盘事件回调
	 * @param function 回调函数\n
	 * 其中的int为按键属性，bool为是否按下
	 */
	void setKeyboardCallback(const KeyboardCallback& function);

	/*!设置鼠标移动回调
	 * @param function 回调函数\n
	 * 其中的第一个double为x坐标，第二个double为y坐标
	 */
	void setMouseMoveCallback(const MouseMoveCallback& function);

	/*!设置鼠标点击回调
	 * @param function 回调函数\n
	 * 其中的第一个double为x坐标，第二个double为y坐标\n
	 * 第一个bool为是否是左键，第二个bool为是否按下
	 */
	void setMouseButtonCallback(const MouseButtonCallback& function);
};