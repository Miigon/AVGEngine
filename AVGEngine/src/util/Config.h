#pragma once

#include <map>
#include <string>
#include <memory>

#define CONFIG_TAG(in) [&]()\
	{\
		std::string configName(in);\
		std::string buffer; \
		if (configName[0] != '[') return std::string("");\
		else \
			for (auto& c : configName)\
			{\
				buffer += c;\
				if (c == ']') return buffer;\
			}\
		return std::string("");\
	}()

#define CONFIG_NOTAG(in) [&]()\
	{\
		std::string configName(in);\
		if (configName[0] != '[') return in;\
		else \
			for (auto& c : configName)\
				if (c == ']') return std::string((&c) + 1);\
		return std::string("");\
	}()

class Config;

using ConfigPtr = std::shared_ptr<Config>;

class Config
{
	//key,data
	std::map<std::string, std::string> mValueMap;

	Config() = default;

public:
	~Config() = default;

	Config(const Config&) = delete;
	Config(const Config&&) = delete;
	Config& operator=(const Config&&) = delete;
	Config& operator=(const Config&) = delete;

	//!加载配置文件
	static ConfigPtr loadConfig(const char* fileName, int offset = 0);
	//!加载配置文件
	static ConfigPtr loadConfig(std::stringstream&);

	//!获取配置
	bool has(const std::string& key) const { return mValueMap.find(key) == mValueMap.end(); }
	std::string get(const std::string& key) const
	{
		const auto result = mValueMap.find(key);

		if (result == mValueMap.end())
			throw(std::invalid_argument(std::string("Can't find the key:") + key));

		return result->second;
	}
	std::string getAsString(const std::string& key) const { return get(key); }
	int getAsInt(const std::string& key) const { return std::stoi(get(key)); }
	int getAsLong(const std::string& key) const { return std::stol(get(key)); }
	float getAsFloat(const std::string& key) const { return std::stof(get(key)); }
	double getAsDouble(const std::string& key) const { return std::stod(get(key)); }
	ConfigPtr getAsConfig(const std::string& key) const;
	double getAsBool(const std::string& key) const
	{
		auto value = get(key);

		for (auto& c : value)
		{
			if (c > 96 && c < 123)
				c -= 32;
		}

		return value == "TRUE";
	}

	/*!获取所有配置
	* @note 请不要轻易使用此方法
	*/
	std::map<std::string, std::string>& getConfigs() { return mValueMap; }
	const std::map<std::string, std::string>& getConfigsConst() const { return mValueMap; }
};
