#include "Config.h"
#include <fstream>
#include <sstream>

ConfigPtr Config::getAsConfig(const std::string& key) const
{
	std::stringstream stream(get(key));

	return loadConfig(stream);
}

ConfigPtr Config::loadConfig(std::stringstream& configStr)
{
	ConfigPtr config(new Config());
	std::string valueName;

	while (!configStr.eof())
	{
		char buffer;
		configStr.read(&buffer, 1);

		//抛弃大括号
		if ((buffer == '{' || buffer == '}') && valueName.empty())
			continue;
		
		//抛弃注释行
		if (buffer == '#')
		{
			if (!valueName.empty())
				throw(std::invalid_argument(std::string("Wrong note at ") + std::to_string(configStr.tellg())));

			while(buffer != '\n' && !configStr.eof())
				configStr.read(&buffer, 1);

			continue;
		}
		
		//警告字符
		if (buffer == ' ' || buffer == '\t' || buffer == '\r' || buffer == '\n')
			continue;

		//变量名和值的分割符
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at ") + std::to_string(configStr.tellg())));

			//读取值
			std::string value;

			auto braceCount = 0;

			while (!configStr.eof())
			{
				configStr.read(&buffer, 1);

				//跳过开始的空格
				if (buffer == ' ' && value.empty())
					continue;

				//大括号判断
				if (buffer == '{')
					++braceCount;
				else if (buffer == '}')
					--braceCount;

				//退出循环判断
				if ((!braceCount && buffer == '\n' && !value.empty()) || configStr.eof())
					break;

				//丢弃非法字符
				if (buffer != ' ' && buffer != '\t' && buffer != '\r')
					value += buffer;
			}

			//add to map
			config->mValueMap[valueName] = value;
			valueName = "";

			continue;
		}

		//非法字符(a-z A-Z 0-9 [ ] .)
		if (!((buffer < 123 && buffer > 96) || //a-z
			(buffer < 91 && buffer > 64) || //A-Z
			(buffer < 58 && buffer > 47) || //0-9
			(buffer == '[' || buffer == ']') || //[ and ]
			(buffer == '.')				   //.
			))
			throw(std::invalid_argument(std::string("Wrong data at ") + std::to_string(configStr.tellg())));

		//更改变量名
		valueName += buffer;
	}

	return config;
}

ConfigPtr Config::loadConfig(const char* fileName, const int offset)
{
	auto file = std::ifstream(fileName, std::ios::binary);
	std::stringstream stream;
	stream << file.rdbuf();
	return loadConfig(stream);
}