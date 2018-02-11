#include "WidgetContainer.h"
#include "Label.h"
#include "CustomWidget.h"
#include "../util/Resource.h"

void WidgetContainer::init(const Config& containerConfig)
{
	for (auto& config : containerConfig.getConfigsConst())
	{
		const auto tag = CONFIG_TAG(config.first);

		//控件容器无变量
		if (tag.empty())
			continue;

		//初始化控件
		if (tag == "[Widget]")
			Widget::init(*containerConfig.getAsConfig(config.first));
		//内置控件类型
		else if (tag == "[Label]")
		{
			try
			{
				auto label = std::make_shared<Label>();
				label->name = CONFIG_NOTAG(config.first);
				label->init(*containerConfig.getAsConfig(config.first));
				widgets.push_back(label);
			}
			catch (std::exception& e)
			{
				throw(std::runtime_error(std::string("Failed to create Custom widget because ") + e.what()));
			}
		}
		//自定义控件类型
		else
		{
			try
			{
				auto widgetTypeName = tag.substr(1, tag.size() - 2);
				auto customWidget = std::make_shared<CustomWidget>(*Resource::getConfig(widgetTypeName.c_str()));
				customWidget->name = CONFIG_NOTAG(config.first);
				customWidget->init(*containerConfig.getAsConfig(config.first));
				widgets.push_back(customWidget);
			}
			catch(std::exception& e)
			{
				throw(std::runtime_error(std::string("Failed to create Custom widget because ") + e.what()));
			}
		}
	}
}

void WidgetContainer::draw()
{
	for (auto& widget: widgets)
		widget->draw();
}