#pragma once

#include "Widget.h"

class Label :public Widget
{
	GLuint mLabelBackgroundVao = 0;
	GLuint mLabelTextVao = 0;
	GLuint mLabelVbo = 0;

public:
	Label()
	{
		addField("caption", FieldString);
	}

	void init(const Config& labelConfig) override;

	void draw() override;
};