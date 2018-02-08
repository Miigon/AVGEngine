#include "Resource.h"
#include "Config.h"
#include <map>
#include <string>
#include "Texture.h"
#include <dirent.h>
#include <vector>
#include <SDL2/SDL_rwops.h>

#ifdef _WIN32
#define RESOURCE_ROOT_PATH
#elif __ANDROID__
#define RESOURCE_ROOT_PATH std::string(SDL_AndroidGetInternalStoragePath())
#endif
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
//#ifdef __ANDROID__
void unpackage()
{
	const auto resPackage = SDL_RWFromFile("res.pk", "rb");

	//检查包头
	char head[2];
	resPackage->read(resPackage, head, 2, 2);

	if (head[0] != 'P' || head[1] != 'K')
		throw std::runtime_error("Failed to read res package");

	//获取包版本
	char guid[35];
	resPackage->read(resPackage, guid, 34, 34);
	guid[34] = 0;
}
//#endif

void Resource::init()
{
//#ifdef __ANDROID__
	const auto packVersionFile = SDL_RWFromFile("PackageVersion", "rb");

	if (!packVersionFile)
		unpackage();
	else
	{
		char nowGuid[35];
		packVersionFile->read(packVersionFile, nowGuid, 36, 36);
		const auto resPackage = SDL_RWFromFile("res.pk", "rb");
		nowGuid[34] = 0;

		char packageGuid[35];
		resPackage->read(resPackage, packageGuid, 34, 34);
		packageGuid[34] = 0;

		if (!strcmp(nowGuid, packageGuid))
			unpackage();

		resPackage->close(resPackage);
		packVersionFile->close(packVersionFile);
	}
//#endif
	std::vector<std::string> files;
	
	enumFile(RESOURCE_ROOT_PATH + "res", files);

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