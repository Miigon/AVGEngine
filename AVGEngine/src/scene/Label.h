#pragma once

#include "Widget.h"

class Label :public Widget
{
public:
	Label()
	{
		addField("caption", FieldString);
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