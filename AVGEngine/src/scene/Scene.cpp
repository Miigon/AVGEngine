#include <sstream>
#include "Scene.h"
#include "../util/OpenGL.h"

void Scene::draw()
{
	glClearColor(0.0f, 
				 0.5f,
				 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::init(const Config& config)
{
	//��ʼ���ؼ�����
	const auto sceneConfig = config.getAsConfig("[Scene]");

	//��ʼ���ؼ�
	if (sceneConfig->has("[Widget]"))
		WidgetContainer::init(*sceneConfig->getAsConfig("[Widget]"));

	setField("size.height", 1.0);
	setField("size.width", 1.0);

	//���������е�����
	auto widgetsConfig = sceneConfig->getAsString("[WidgetContainer]");

	for (const auto& field : getFields())
	{
		auto nameInConfig = std::string("$(") + field.first + ")";

		size_t findResult;

		while ((findResult = widgetsConfig.find(nameInConfig)) != std::string::npos)
		{
			std::string value;

			switch (field.second.first)
			{
			case FieldString:
				value = *reinterpret_cast<std::string*>(field.second.second);
				break;
			case FieldInt:
				value = std::to_string(*reinterpret_cast<int*>(field.second.second));
				break;
			case FieldDouble:
				value = std::to_string(*reinterpret_cast<double*>(field.second.second));
				break;
			case FieldBool:
				value = *reinterpret_cast<bool*>(field.second.second) ? "TRUE" : "";
				break;
			default:
				break;
			}
			widgetsConfig = widgetsConfig.replace(widgetsConfig.find(nameInConfig), nameInConfig.size(), value);
		}
	}

	std::stringstream stringstream(widgetsConfig);

	//��ʼ���ؼ�����
	WidgetContainer::init(*Config::loadConfig(stringstream));
}