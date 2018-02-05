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
	//��ȡֵ
	std::string value;

	auto braceCount = 0;
	while (true)
	{
		char buffer;

		stream.read(&buffer, 1);

		//�ж��Ƿ���������ֵ
		if ((!braceCount && buffer == '\n' && !value.empty()) || stream.eof())
			break;

		//������ʼ�Ŀ��кͿո�
		if ((buffer == ' ' || buffer == '\n') && value.empty())
			continue;

		//������������ʱ��������
		if (value.empty() && buffer == '\"')
		{
			//ֱ�Ӷ�����β��������ȡ����ֵ��ѭ��
			while (true)
			{
				stream.read(&buffer, 1);

				if (stream.eof())
					break;

				//�Ƿ��ȡ������
				if (buffer == '\"')
				{
					//������ת���
					if ((value.empty() || value.back() != '\\'))
						break;

					//����ת���
					value.pop_back();
				}
				value += buffer;
			}
			//������ֵѭ��
			break;
		}

		//����Ϊ�գ���һ���ַ�Ϊ�����ţ�����ʹ�ô�����ʱ�����йش����ŵĶ���
		if (value.empty() || braceCount != 0)
		{
			if (buffer == '{')
			{
				//������һ��������
				if (++braceCount == 1)
					continue;
			}
			if (buffer == '}')
				//�Ƿ�û�д�������
				if (--braceCount == 0)
					break;
		}

		//�����Ƿ��ַ���\rΪwindows�»��з���
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

		//����������
		if ((buffer == '{' || buffer == '}') && valueName.empty())
			continue;

		//����ע����
		if (buffer == '#')
		{
			if (!valueName.empty())
				throw(std::invalid_argument(std::string("Wrong note at ") + std::to_string(configStr.tellg())));

			while(buffer != '\n' && !configStr.eof())
				configStr.read(&buffer, 1);

			continue;
		}
		
		//�����ַ�
		if (buffer == ' ' || buffer == '\t' || buffer == '\r' || buffer == '\n')
			continue;

		//��������ֵ�ķָ��
		if (buffer == '=')
		{
			if (valueName.empty())
				throw(std::invalid_argument(std::string("Failed to read file at ") + std::to_string(configStr.tellg())));

			//add to map
			config->mValueMap[valueName] = readValue(configStr);
			valueName = "";

			continue;
		}

		//�Ƿ��ַ�(a-z A-Z 0-9 [ ] .)
		if (!((buffer < 123 && buffer > 96) || //a-z
			(buffer < 91 && buffer > 64) || //A-Z
			(buffer < 58 && buffer > 47) || //0-9
			(buffer == '[' || buffer == ']') || //[ and ]
			(buffer == '.')				   //.
			))
			throw(std::invalid_argument(std::string("Wrong data at ") + std::to_string(configStr.tellg())));

		//���ı�����
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