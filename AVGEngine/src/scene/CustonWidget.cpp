#include "CustomWidget.h"
#include <sstream>
#include <iostream>

CustomWidget::CustomWidget(const Config& config)
{
	//初始化控件容器
	mWidgetContainerTemplate = config.get("[WidgetContainer]");
}

void CustomWidget::init(const Config& config)
{
	//修改配置中的变量
	auto widgetContainer(mWidgetContainerTemplate);

	for (const auto& value : config.getConfigsConst())
	{
		auto nameInConfig = std::string("$(") + value.first + ")";

		size_t findResult;

		while ((findResult = widgetContainer.find(nameInConfig)) != std::string::npos)
			widgetContainer = widgetContainer.replace(widgetContainer.find(nameInConfig), nameInConfig.size(), value.second);
	}

	std::stringstream stringstream(widgetContainer);

	WidgetContainer::init(*Config::loadConfig(stringstream));
}