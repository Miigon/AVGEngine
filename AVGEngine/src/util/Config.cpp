#include "Config.h"
#include <fstream>
#include <sstream>

ConfigPtr Config::getAsConfig(const std::string& key) const
{
	std::stringstream stream(get(key));

	return loadConfig(stream);
}

std::string Config::readValue(std::stringstream& stream)
{
	//读取值
	std::string value;

	auto braceCount = 0;
	while (true)
	{
		char buffer;

		stream.read(&buffer, 1);

		//判断是否读完变量的值
		if ((!braceCount && buffer == '\n' && !value.empty()) || stream.eof())
			break;

		//跳过开始的空行和空格
		if ((buffer == ' ' || buffer == '\n') && value.empty())
			continue;

		//由引号括起来时单独处理
		if (value.empty() && buffer == '\"')
		{
			//直接读到结尾并跳出读取变量值的循环
			while (true)
			{
				stream.read(&buffer, 1);

				if (stream.eof())
					break;

				//是否读取到引号
				if (buffer == '\"')
				{
					//不包含转义符
					if ((value.empty() || value.back() != '\\'))
						break;

					//就是转义符
					value.pop_back();
				}
				value += buffer;
			}
			//跳出读值循环
			break;
		}

		//数据为空（第一个字符为大括号）或者使用大括号时处理有关大括号的东西
		if (value.empty() || braceCount != 0)
		{
			if (buffer == '{')
			{
				//丢掉第一个大括号
				if (++braceCount == 1)
					continue;
			}
			if (buffer == '}')
				//是否没有大括号了
				if (--braceCount == 0)
					break;
		}

		//丢弃非法字符（\r为windows下换行符）
		if (buffer != '\t' && buffer != '\r' && (braceCount || buffer != '\n'))
			value += buffer;
	}

	return value;
}

ConfigPtr Config::loadConfig(std::stringstream& configStr)
{
	ConfigPtr config(new Config());
	std::string valueName;

	while (true)
	{
		char buffer;
		configStr.read(&buffer, 1);

		if (configStr.eof())
			break;

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

			//add to map
			config->mValueMap[valueName] = readValue(configStr);
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