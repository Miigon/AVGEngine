#pragma once

#include <memory>

class IScene
{
protected:
	IScene() = default;

public:
	IScene(const IScene&) = delete;
	IScene(const IScene&&) = delete;
	IScene& operator=(const IScene&&) = delete;
	IScene& operator=(const IScene&) = delete;

	//!‰÷»æ
	virtual void draw() = 0;
	
	//!tick
	virtual void tick() = 0;

	virtual ~IScene() = default;
};

using IScenePtr = std::shared_ptr<IScene>;