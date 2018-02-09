#ifdef _WIN32
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#include <iostream>
#include "Application.h"
#include "scene/MainMenuScene.h"

int main(int argc, char* argv[])
{
	Application app;

	try
	{
		app.run(std::make_shared<MainMenuScene>());
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		system("pause");
	}

	return 0;
}
