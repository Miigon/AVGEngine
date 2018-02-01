#include "Application.h"
#include "scene/MainMenuScene.h"

int main()
{
	Application app;
	app.run(std::make_shared<MainMenuScene>());
}
