#include "Config.h"
#include <fstream>

ConfigPtr Config::loadConfig(const char* fileName)
{
	ConfigPtr config(new Config());

	std::fstream file(fileName);

	std::string valueName;

	while (!file.eof())
	{
		char buffer;
		file.read(&buffer, 1);

		if (buffer == '\n')
		{
			if (valueName.empty())
				continue;
			throw(std::invalid_argument(std::string("Wrong config file") + fileName));
		}
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at line") + std::to_string(file.tellg())));

			//read value
			std::string value;
			file >> value;

			//add to map
			config->mValueMap[valueName] = value;
			valueName = "";
		}
		else if (buffer != ' ' && buffer != '\t')
			valueName += buffer;
	}

	return config;
}