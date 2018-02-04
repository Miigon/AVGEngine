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

		//����������
		if ((buffer == '{' || buffer == '}') && valueName.empty())
			continue;
		//����ע����
		if (buffer == '#' && valueName.empty())
		{
			while(buffer != '\n' && !configStr.eof())
				configStr.read(&buffer, 1);
		}
		//�µ�һ��
		if (buffer == '\n')
		{
			if (valueName.empty())
				continue;
			throw(std::invalid_argument(std::string("Wrong config file") + configStr.getloc().c_str()));
		}
		//��������ֵ�ķָ��
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at line") + std::to_string(configStr.tellg())));

			//��ȡֵ
			std::string value;

			auto braceCount = 0;

			while (!configStr.eof())
			{
				configStr.read(&buffer, 1);

				//������ʼ�Ŀո�
				if (buffer == ' ' && value.empty())
					continue;

				//�������ж�
				if (buffer == '{')
					++braceCount;
				else if (buffer == '}')
					--braceCount;

				//�˳�ѭ���ж�
				if ((!braceCount && buffer == '\n' && !value.empty()) || configStr.eof())
					break;

				//�����Ƿ��ַ�
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