#pragma once

#include "Widget.h"
#include <vector>

class WidgetContainer :public Widget
{
	std::vector<std::shared_ptr<Widget>> mWidgets;

public:
	void onClick(double mouseX, double mouseY) override
	{
		
	}

	void init(const Config& containerConfig) override;
};