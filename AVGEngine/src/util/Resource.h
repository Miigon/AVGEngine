#pragma once

#include <utility>
#include <memory>

class Config;
class Texture;

class Resource
{
public:
	enum ResourceType
	{
		TextureRes, ConfigRes
	};
private:
	static void registerResource(const char* key, const std::pair<ResourceType, std::shared_ptr<void>>& value);

public:
	static void init();
	static Config* getConfig(const char* name);
	static Texture* getTexture(const char* name);
};
