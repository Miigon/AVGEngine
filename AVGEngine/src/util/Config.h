#pragma once

#include <map>
#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

class Config;

using ConfigPtr = std::shared_ptr<Config>;

class Config :boost::noncopyable
{
	std::map<std::string, std::string> mValueMap;

	Config() = default;
public:
	//!加载配置文件
	static ConfigPtr loadConfig(const char* fileName);

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
};
