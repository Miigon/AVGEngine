#pragma once
#include "../util/Config.h"
#include "../util/DynamicObj.h"

class Widget :public DynamicObj
{
public:
	Widget(const Widget&) = delete;
	Widget(const Widget&&) = delete;
	Widget& operator=(const Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;

	Widget();

	virtual ~Widget() = default;

	/*!初始化控件
	 * 通过配置文件来初始化控件的属性
	 * @note config 配置文件
	 */
	virtual void init(const Config& config);

	/*!点击事件
	 * @param mouseX 点击位置相对于控件横坐标
	 * @param mouseY 点击位置相对于控件纵坐标
	 */
	virtual void onClick(double mouseX, double mouseY) {}

	/*!渲染事件\n
	 * 每次渲染时调用
	 */
	virtual void draw() {}

	/*!tick事件\n
	* 每0.02秒调用一次，由Application类调用
	* @note 可能会因性能问题时间出现问题
	*/
	virtual void tick() {}

	//!控件名称
	std::string name;
};
