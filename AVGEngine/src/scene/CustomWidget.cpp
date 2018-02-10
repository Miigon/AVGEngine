#include "CustomWidget.h"
#include <sstream>

CustomWidget::CustomWidget(const Config& config)
{
	//ÂàùÂßãÂåñÊéß‰ª∂ÂÆπÂô®
	mWidgetContainerTemplate = config.get("[WidgetContainer]");
}

void CustomWidget::init(const Config& config)
{
	auto widgetContainerConf(mWidgetContainerTemplate);

	for (const auto& value : config.getConfigsConst())
	{
		auto nameInConfig = std::string("$(") + value.first + ")";

		size_t findResult;

		while ((findResult = widgetContainerConf.find(nameInConfig)) != std::string::npos)
			widgetContainerConf = widgetContainerConf.replace(widgetContainerConf.find(nameInConfig), nameInConfig.size(), value.second);
	}

	//µ±«∞Widgetµƒ Ù–‘
	for (const auto& field : getFields())
	{
		auto nameInConfig = std::string("$(") + field.first + ")";

		size_t findResult;

		while ((findResult = widgetContainerConf.find(nameInConfig)) != std::string::npos)
		{
			std::string value;

			switch (field.second.first)
			{
			case FieldString:
				value = *reinterpret_cast<std::string*>(field.second.second);
				break;
			case FieldInt:
				value = std::to_string(*reinterpret_cast<int*>(field.second.second));
				break;
			case FieldDouble:
				value = std::to_string(*reinterpret_cast<double*>(field.second.second));
				break;
			case FieldBool:
				value = *reinterpret_cast<bool*>(field.second.second) ? "TRUE" : "";
				break;
			default:
				break;
			}
			widgetContainerConf = widgetContainerConf.replace(widgetContainerConf.find(nameInConfig), nameInConfig.size(), value);
		}
	}

	std::stringstream stringstream(widgetContainerConf);

	WidgetContainer::init(*Config::loadConfig(stringstream));
}