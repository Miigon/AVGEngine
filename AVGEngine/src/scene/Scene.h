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

	//”√config≥ı ºªØScene
	void init(const Config& sceneConfig);
};

using ScenePtr = std::shared_ptr<Scene>;