#pragma once
#include "../util/DynamicObj.h"

class Widget :protected DynamicObj
{
public:
	Widget(const Widget&) = delete;
	Widget(const Widget&&) = delete;
	Widget& operator=(const Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;

	Widget()
	{
		//背景颜色属性
		addField("backgroundColor.r", FieldDouble);
		addField("backgroundColor.g", FieldDouble);
		addField("backgroundColor.b", FieldDouble);

		//控件名称
		addField("name", FieldString);
	}

	virtual ~Widget() = default;

	/*!点击事件
	 * @param mouseX 点击位置相对于控件横坐标
	 * @param mouseY 点击位置相对于控件纵坐标
	 */
	virtual void onClick(double mouseX, double mouseY) = 0;

	/*!渲染事件\n
	 * 每次渲染时调用
	 */
	virtual void draw() = 0;

public:
	/*!tick事件\n
	* 每0.02秒调用一次，由Application类调用
	* @note 可能会因性能问题时间出现问题
	*/
	virtual void tick() = 0;
};