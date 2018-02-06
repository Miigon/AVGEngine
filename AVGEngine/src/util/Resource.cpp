#include "Resource.h"
#include "Config.h"
#include <map>
#include <string>
#include "Texture.h"
std::map<std::string, std::pair<Resource::ResourceType, std::shared_ptr<void>>> resourceMap;

void Resource::registerResource(const char* key, const std::pair<ResourceType, std::shared_ptr<void>>& value)
{
	resourceMap[key] = value;
}

#ifdef _WIN32
#include <filesystem>

void Resource::init()
{
	using namespace std::experimental::filesystem;

	for (const auto& item : recursive_directory_iterator(path("res/")))
	{
		if (is_directory(item.path()))
			continue;

		auto resKey = item.path().string();

		for (auto& c : resKey)
			if (c == '\\' || c == '/')
				c = '.';

		if (item.path().extension() == ".cnf")
			registerResource
			(
				resKey.c_str(),
				std::make_pair
				(
					ConfigRes,
					Config::loadConfig(item.path().string().c_str())
				)
			);
		else if (item.path().extension() == ".png")
			registerResource
			(
				resKey.c_str(),
				std::make_pair
				(
					TextureRes,
					Texture::loadTexture(item.path().string().c_str())
				)
			);
	}
}
#else
void Resource::init()
{

}
#endif

Config* Resource::getConfig(const char* name)
{
	const auto result = resourceMap.find(name);

	if (result == resourceMap.end())
		throw(std::invalid_argument(std::string("Resource doesn't exist:") + name));
	if (result->second.first != ConfigRes)
		throw(std::invalid_argument(std::string("Resource type doesn't equal") + name));

	return reinterpret_cast<Config*>(result->second.second.get());
}

Texture* Resource::getTexture(const char* name)
{
	const auto result = resourceMap.find(name);

	if (result == resourceMap.end())
		throw(std::invalid_argument(std::string("Resource doesn't exist:") + name));
	if (result->second.first != TextureRes)
		throw(std::invalid_argument(std::string("Resource type doesn't equal") + name));

	return reinterpret_cast<Texture*>(result->second.second.get());
}