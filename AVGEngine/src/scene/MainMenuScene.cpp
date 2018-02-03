#include "MainMenuScene.h"
#include "../util/Resource.h"

MainMenuScene::MainMenuScene()
{
	mSceneConfig = Resource::getConfig("res.scene.MainMenuScene.cnf");
	mBackGroundTexture = Resource::getTexture(mSceneConfig->get("background").c_str());

	glClearColor(0.0f, 0.2f, 0.3f, 1.0f);
}

void MainMenuScene::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(*mBackGroundTexture));
}

void MainMenuScene::tick()
{
	
}
