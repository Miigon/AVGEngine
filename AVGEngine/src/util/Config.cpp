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
		if (buffer == '#'&& valueName.empty())
			configStr.getline(nullptr, 0);
		//新的一行
		if (buffer == '\n')
		{
			if (valueName.empty())
				continue;
			throw(std::invalid_argument(std::string("Wrong config file") + configStr.getloc().c_str()));
		}
		//变量名和值的分割符
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at line") + std::to_string(configStr.tellg())));

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
		}
		else if (buffer != ' ' && buffer != '\t' && buffer != '\r')
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