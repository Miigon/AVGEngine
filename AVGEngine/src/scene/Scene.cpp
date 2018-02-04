#include "Scene.h"
#include "../util/OpenGL.h"

void Scene::draw()
{
	glClearColor(static_cast<float>(getDouble("backgroundColor.r")), 
				 static_cast<float>(getDouble("backgroundColor.g")),
				 static_cast<float>(getDouble("backgroundColor.b")), 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::init(const Config& sceneConfig)
{
	//初始化控件容器
	auto testConfig = sceneConfig.getAsConfig("widgetContainer");

	//初始化动态变量
	for (auto& field : getFields())
	{
		switch (field.second.first)
		{
		case FieldInt:
			
			try
			{
				auto* old = reinterpret_cast<int*>(field.second.second);
				field.second.second = new int(sceneConfig.getAsInt(field.first));
				delete old;
			}
			catch(std::exception&){}
			break;
		case FieldBool:
			try
			{
				auto* old = reinterpret_cast<int*>(field.second.second);
				field.second.second = new bool(sceneConfig.getAsBool(field.first));
				delete old;
			}
			catch (std::exception&) {}
			break;
		case FieldDouble:
			try
			{
				auto* old = reinterpret_cast<int*>(field.second.second);
				field.second.second = new double(sceneConfig.getAsDouble(field.first));
				delete old;
			}
			catch (std::exception&) {}
			break;
		case FieldString:
			try
			{
				auto* old = reinterpret_cast<int*>(field.second.second);
				field.second.second = new std::string(sceneConfig.getAsString(field.first));
				delete old;
			}
			catch (std::exception&) {}
			break;
		default:
			break;
		}
	}
}