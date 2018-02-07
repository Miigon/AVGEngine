#include "Resource.h"
#include "Config.h"
#include <map>
#include <string>
#include "Texture.h"
#include <dirent.h>
#include <vector>

std::map<std::string, std::pair<Resource::ResourceType, std::shared_ptr<void>>> resourceMap;

void Resource::registerResource(const char* key, const std::pair<ResourceType, std::shared_ptr<void>>& value)
{
	resourceMap[key] = value;
}

void enumFile(const std::string& basePath, std::vector<std::string>& files)
{
	const auto dir = opendir(basePath.c_str());
	struct dirent *direntPtr;

	while ((direntPtr = readdir(dir)) != nullptr)
	{
		if (strcmp(direntPtr->d_name, ".") == 0 || strcmp(direntPtr->d_name, "..") == 0)
			continue;
		if (direntPtr->d_type == DT_REG)
			files.push_back(basePath + "/" + direntPtr->d_name);
		else if (direntPtr->d_type == DT_DIR)
			enumFile(basePath + "/" + direntPtr->d_name, files);
	}
}
void Resource::init()
{
	std::vector<std::string> files;
	enumFile("res", files);

	for (const auto& file : files)
	{
		auto resKey = file;

		for (auto& c : resKey)
			if (c == '\\' || c == '/')
				c = '.';

		const auto extension = file.substr(file.find_last_of('.'));

		if (extension == ".cnf")
			registerResource
			(
				resKey.c_str(),
				std::make_pair
				(
					ConfigRes,
					Config::loadConfig(file.c_str())
				)
			);
		else if (extension == ".png")
			registerResource
			(
				resKey.c_str(),
				std::make_pair
				(
					TextureRes,
					Texture::loadTexture(file.c_str())
				)
			);
	}
}

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