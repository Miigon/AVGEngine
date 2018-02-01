#pragma once

#include "IScene.h"
#include "../util/Config.h"
#include "../util/Texture.h"

class MainMenuScene :public IScene
{
	Config* mSceneConfig;
	Texture* mBackGroundTexture;

public:
	MainMenuScene();

	void draw() override;
	void tick() override;
};
