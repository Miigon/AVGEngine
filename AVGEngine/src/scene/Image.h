#pragma once

#include "Widget.h"

class Image :public Widget
{
public:
	Image()
	{
		addField("image", FieldString);
	}

	void init(const Config& labelConfig) override
	{
		//初始化控件
		if (labelConfig.has("[Widget]"))
			//有Widget标签
			Widget::init(*labelConfig.getAsConfig("[Widget]"));
		else
			//无Widget标签
			Widget::init(labelConfig);
	}
};