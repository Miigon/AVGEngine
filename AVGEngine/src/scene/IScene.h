#pragma once

#include <memory>
#include <boost/noncopyable.hpp>

class IScene :boost::noncopyable
{
public:
	//!��Ⱦ
	virtual void draw() = 0;
	
	//!tick
	virtual void tick() = 0;

	virtual ~IScene() = default;
};

using IScenePtr = std::shared_ptr<IScene>;