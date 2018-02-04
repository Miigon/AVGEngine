#pragma once

#include "Widget.h"
#include <vector>

class WidgetContainer :public Widget
{
	std::vector<Widget> mWidgets;

public:
	template <class T> T& addWidget()
	{
		mWidgets.emplace_back(T());
	}

	void onClick(double mouseX, double mouseY) override
	{
		
	}
};