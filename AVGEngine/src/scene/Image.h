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
		//��ʼ���ؼ�
		if (labelConfig.has("[Widget]"))
			//��Widget��ǩ
			Widget::init(*labelConfig.getAsConfig("[Widget]"));
		else
			//��Widget��ǩ
			Widget::init(labelConfig);
	}
};