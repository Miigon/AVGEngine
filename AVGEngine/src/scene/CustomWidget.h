#pragma once

#include "../util/Config.h"
#include "WidgetContainer.h"

class CustomWidget :public WidgetContainer
{
	std::string mWidgetContainerTemplate;

public:
	/*!ͨ�������������Զ���ؼ�
	 * �Զ����ñ���������ȵ�
	 */
	explicit CustomWidget(const Config& config);

	void init(const Config& config) override;
};
