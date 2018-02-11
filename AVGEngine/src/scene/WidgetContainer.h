#pragma once

#include "Widget.h"
#include <vector>

class WidgetContainer :public Widget
{
public:
	std::vector<std::shared_ptr<Widget>> widgets;

	//!获取指定名称的控件@note 如果未找到则返回nullptr
	template <class t> std::shared_ptr<t> findWidget(const std::string& name) const
	{
		for (const auto& w : widgets)
		{
			if (w->name == name)
				return std::static_pointer_cast<t>(w);
		}
		return nullptr;
	}

	void draw() override;

	void onClick(double mouseX, double mouseY) override
	{
		
	}

	void init(const Config& containerConfig) override;
};
