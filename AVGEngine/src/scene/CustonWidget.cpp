#include "CustomWidget.h"
#include <sstream>
#include <iostream>

CustomWidget::CustomWidget(const Config& config)
{
	//��ʼ���ؼ�����
	mWidgetContainerTemplate = config.get("[WidgetContainer]");
}

void CustomWidget::init(const Config& config)
{
	//�޸������еı���
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