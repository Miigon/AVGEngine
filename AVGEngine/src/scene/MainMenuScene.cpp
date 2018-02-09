#include "MainMenuScene.h"
#include "../util/Resource.h"

MainMenuScene::MainMenuScene()
{
	//初始化配置
	Scene::init(*Resource::getConfig("scene.MainMenuScene.cnf"));
}

void MainMenuScene::tick()
{
	
}
