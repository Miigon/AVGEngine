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
			auto label = std::make_shared<Label>();
			label->init(*containerConfig.getAsConfig(config.first));
			mWidgets.push_back(label);
		}
		//自定义控件类型
		else
		{
			try
			{
				auto widgetTypeName = tag.substr(1, tag.size() - 2);
				auto customWidget = std::make_shared<CustomWidget>(*Resource::getConfig(widgetTypeName.c_str()));
				customWidget->init(*containerConfig.getAsConfig(config.first));
				mWidgets.push_back(customWidget);
			}
			catch(std::exception& e)
			{
				throw(std::runtime_error(std::string("Failed to create custon widget besause ") + e.what()));
			}
		}
	}
}
