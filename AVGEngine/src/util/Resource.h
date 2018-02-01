#pragma once

#include "Uncopyable.h"
#include <utility>

class Resource :Uncopyable
{
public:
	enum ResourceType
	{
		Texture, Config
	};
private:
	void registerResource(const char* key, std::pair<ResourceType, void*>);
};
