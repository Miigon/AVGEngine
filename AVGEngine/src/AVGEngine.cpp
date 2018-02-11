#include "util/Platform.h"
#ifdef AVG_DESKTOP
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <iostream>
#include "Application.h"
#include "scene/MainMenuScene.h"

int main(int argc, char* argv[])
{
	Application app(768, 512);

#ifdef _DEBUG
	app.run(std::make_shared<MainMenuScene>());
#else
	try
	{
		app.run(std::make_shared<MainMenuScene>());
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		system("pause");
	}
#endif
	return 0;
}
