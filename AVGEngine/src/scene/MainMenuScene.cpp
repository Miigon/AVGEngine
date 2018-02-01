#include "MainMenuScene.h"
#include "../util/Resource.h"

MainMenuScene::MainMenuScene()
{
	mSceneConfig = Resource::getConfig("res.scene.MainMenuScene.cnf");
	mBackGroundTexture = Resource::getTexture(mSceneConfig->get("background").c_str());
}

void MainMenuScene::draw()
{
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(*mBackGroundTexture));
}

void MainMenuScene::tick()
{
	
}
