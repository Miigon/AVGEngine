#pragma once

#include "../util/Config.h"
#include "WidgetContainer.h"

class CustomWidget :public WidgetContainer
{
	std::string mWidgetContainerTemplate;

public:
	/*!通过配置来创建自定义控件
	 * 自动设置变量、组件等等
	 */
	explicit CustomWidget(const Config& config);

	void init(const Config& config) override;
};
