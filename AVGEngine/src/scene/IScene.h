#pragma once

#include "../util/Uncopyable.h"
#include <memory>

class IScene :Uncopyable
{
public:
	//!‰÷»æ
	virtual void draw() = 0;
	
	//!tick
	virtual void tick() = 0;
};

using IScenePtr = std::shared_ptr<IScene>;