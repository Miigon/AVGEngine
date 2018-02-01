#pragma once

#include "IScene.h"

class MainMenuScene :public IScene
{
public:
	void draw() override;
	void tick() override;
};