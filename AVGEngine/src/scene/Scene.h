#pragma once

#include <memory>
#include "WidgetContainer.h"
#include "../util/Config.h"

class Scene :public WidgetContainer
{
public:
	Scene(const Scene&) = delete;
	Scene(const Scene&&) = delete;
	Scene& operator=(const Scene&&) = delete;
	Scene& operator=(const Scene&) = delete;

	void draw() override;

	Scene() = default;
	virtual ~Scene() = default;

	//!用config初始化Scene
	void init(const Config& config) override;
};

using ScenePtr = std::shared_ptr<Scene>;