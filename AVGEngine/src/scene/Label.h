#pragma once

#include "Widget.h"

class Label : public Widget
{
public:
	std::string caption;

	void init(const Config& config) override
	{
		try
		{
			caption = config.getAsString("caption");
		}
		catch (std::exception&) { caption = ""; }
	}
};