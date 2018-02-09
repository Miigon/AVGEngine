#include "Resource.h"
#include "Config.h"
#include <map>
#include <string>
#include "Texture.h"
#include <dirent.h>
#include <vector>
#include <sstream>
#include <fstream>

#ifdef WIN32
#include <io.h>
#define avg_mkdir(dir) _mkdir(dir)
#define avg_access(dir,mode) _access(dir, mode)
#else
#include <unistd.h>
#include <sys/stat.h>
#define avg_mkdir(dir) mkdir(dir, 0777)
#define avg_access(dir,mode) access(dir, mode)
#endif

#ifdef AVG_DESKTOP
#include <SDL2/SDL.h>
//#include <direct.h>
#define RESOURCE_ROOT_PATH std::string("")
#else
#include <SDL.h>
#ifdef __ANDROID__
#define RESOURCE_ROOT_PATH (std::string(SDL_AndroidGetInternalStoragePath()) + "/")
#endif
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

//! 自动创建目录@param path 目录
void createDir(const std::string& path)
{
	const auto findResult = path.find_last_of('/');
	if (findResult == std::string::npos)
	{
		if (avg_access(path.c_str(), 0) == -1)
			avg_mkdir(path.c_str());
		return;
	}
	const auto newFolderName = path.substr(0, findResult);
	if (avg_access(newFolderName.c_str(), 0) == -1)
		createDir(newFolderName);
	avg_mkdir(path.c_str());
}

//! 解压资源到指定位置@param path 目标路径，需要带"/"
void unpackage(const std::string& path)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "注意", "资源包未释放，即将自动解压资源包", nullptr);

	const auto resPackage = SDL_RWFromFile("res.pk", "rb");

	if(resPackage == nullptr)
	{
		std::stringstream ss;
		ss << "打开资源包失败！错误信息：" << SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "错误", ss.str().c_str(), nullptr);
		exit(1);
	}

	//检查包头
	char head[2];
	resPackage->read(resPackage, head, 2, 1);

	if (head[0] != 'P' || head[1] != 'K')
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", "Wrong resource package");
		throw std::runtime_error("Wrong resource package");
	}

	//获取包版本
	char guid[37] = { 0 };
	resPackage->read(resPackage, guid, 36, 1);
	guid[36] = 0;

	//遍历
	while (true)
	{
		char buffer;

		//获取文件名
		auto fileName = path;
		while (SDL_RWread(resPackage, &buffer, 1, 1))
		{
			if (buffer == 0)
				break;
			fileName += buffer;
		}

		//无文件，则跳出循环
		if (fileName.length() == path.length())
			break;

		//获取文件大小
		std::string fileSize;
		while (true)
		{
			if (!SDL_RWread(resPackage, &buffer, 1, 1))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", "Wrong resource package");
				throw std::runtime_error("Wrong resource package");
			}
			if (buffer == 0)
				break;
			fileSize += buffer;
		}

		//创建文件
		createDir(fileName.substr(0, fileName.find_last_of('/')));

		auto file = std::ofstream(fileName, std::ios::binary);

		for (auto i = 0; i < std::stol(fileSize); i++)
		{
			if (!SDL_RWread(resPackage, &buffer, 1, 1))
			{
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", "Wrong resource package");
				throw std::runtime_error("Wrong resource package");
			}
			file << buffer;
		}

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", fileName.c_str());
	}

	//写入包GUID
	auto packVersionFile = std::ofstream(path + "res/PackageVersion", std::ios::binary);
	packVersionFile << guid;

	//关闭
	SDL_RWclose(resPackage);
}

void Resource::init()
{
	auto packVersionFile = std::ifstream(RESOURCE_ROOT_PATH + "res/PackageVersion", std::ios::binary);

	if (!packVersionFile)
		unpackage(RESOURCE_ROOT_PATH);
	else
	{
		//获取当前资源GUID
		std::string nowGuid;
		packVersionFile >> nowGuid;
		const auto resPackage = SDL_RWFromFile("res.pk", "rb");

		//获取内置资源包GUID
		char packageGuid[37] = { 0 };

		if (resPackage)
		{
			//跳过包头
			SDL_RWseek(resPackage, 2, 0);
			SDL_RWread(resPackage, packageGuid, 36, 1);
			SDL_RWclose(resPackage);
		}

		if (nowGuid != packageGuid && nowGuid != "00000000-0000-0000-0000-000000000000")
			unpackage(RESOURCE_ROOT_PATH);
	}
	std::vector<std::string> files;
	
	enumFile(RESOURCE_ROOT_PATH + "res", files);

	for (const auto& file : files)
	{
		auto resKey = file.substr(RESOURCE_ROOT_PATH.length());

		for (auto& c : resKey)
			if (c == '\\' || c == '/')
				c = '.';

		const auto findResult = file.find_last_of('.');

		//是否有扩展名
		if (findResult == std::string::npos)
			continue;

		const auto extension = file.substr(findResult);

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