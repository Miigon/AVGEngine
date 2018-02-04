#pragma once

#include "Widget.h"
#include <vector>

class WidgetContainer :public Widget
{
public:
	std::vector<std::shared_ptr<Widget>> widgets;

	void onClick(double mouseX, double mouseY) override
	{
		
	}

	void init(const Config& containerConfig) override;
};