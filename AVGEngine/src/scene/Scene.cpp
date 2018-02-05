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
	//初始化控件容器
	const auto sceneConfig = config.getAsConfig("[Scene]");

	for (const auto& conf : sceneConfig->getConfigsConst())
	{
		const auto tag = CONFIG_TAG(conf.first);

		if (tag.empty())
			continue;

		//初始化控件容器
		if (tag == "[WidgetContainer]")
			WidgetContainer::init(*sceneConfig->getAsConfig(conf.first));

		//初始化控件
		if (tag == "[Widget]")
			WidgetContainer::init(*sceneConfig->getAsConfig(conf.first));
	}
}